#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

#include "sim_data.h"
#include "virtual_key_press.h"
#include "gnc_loop.h"

#define FILE_PATH           "sim_data.csv"
#define REFRESH_RATE_HZ     5
#define MS_PER_SECOND       1000
#define P_KEY               0x50
#define START_TIMER_SLEEP   500

int main()
{
    for (int i = 3; i > 0; i--)
    {
        std::cout << "Until start: " << i << std::endl;
        Sleep(START_TIMER_SLEEP);
    }
    std::cout << "Started" << std::endl;

    sim_data live_data = sim_data(); // current flight data
    sim_data prev_data = sim_data(); // last state recorded
    std::vector <double> data_buffer(8, 0.0); // a vector to hold file data 
    std::string line_buffer; // string for each line for vector

    while (1)
    {
        std::ifstream file (FILE_PATH);
        for (int i = 0; getline (file, line_buffer); ++i)
        {
            data_buffer[i] = (atof(line_buffer.c_str()));
        }
        file.close();

        live_data.set_live_values(data_buffer);

        // position velocity calculations
        live_data.x_velocity = (prev_data.x_val - live_data.x_val) * REFRESH_RATE_HZ;
        live_data.y_velocity = (prev_data.y_val - live_data.y_val) * REFRESH_RATE_HZ;
        live_data.z_velocity = (prev_data.z_val - live_data.z_val) * REFRESH_RATE_HZ;

        /*************************/

        if (GetKeyState(P_KEY) < 0)
        {
            std::cout << "Exit" << std::endl;
            return 0;
        }

        gnc_loop(live_data);
        // std::cout << "\nRoll: " << live_data.roll_velocity << "\nPitch: " << live_data.pitch_velocity << "\nYaw: " << live_data.yaw_velocity << std::endl;

        /*************************/

        Sleep(MS_PER_SECOND / REFRESH_RATE_HZ);

        prev_data.set_live_values(data_buffer); // constructs class which holds data from last loop
    }

    return 0;
}