#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

#include "sim_data.h"
#include "virtual_key_press.h"
#include "gnc_loop.h"
#include "key_codes.h"

#define FILE_PATH           "sim_data.csv"
#define REFRESH_RATE_HZ     20
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
    std::vector <double> data_buffer(8, 0.0); // a vector to hold file data 
    std::string line_buffer; // string for each line for vector
    bool is_stable_orientation = false; 

    for (int j = 0; j < 6; j++)
    {
        press_key(W_KEY, live_data, false); // hard codes to stop dragon from sinking
        press_key(A_KEY, live_data, false); // hard coded to push dragon to left
    }

    int i = 0; // iterates each time the loop cycles, resets every four iterations
    while (1)
    {
        std::ifstream file (FILE_PATH);
        for (int i = 0; getline (file, line_buffer); ++i)
        {
            data_buffer[i] = (atof(line_buffer.c_str()));
        }
        file.close();

        live_data.set_live_values(data_buffer);

        /*************************/

        if (GetKeyState(P_KEY) < 0) // checks if the 'P' key is pressed, and if it is, it will exit
        {
            std::cout << "Exit" << std::endl;
            return 0;
        }

        if (!is_stable_orientation && live_data.roll_val == 0.0 && live_data.pitch_val == 0.0 && live_data.yaw_val == 0.0)
        {
            is_stable_orientation = true;
            std::cout << "---\nSTABLE\n---" << std::endl;
        }

        gnc_loop(live_data, i, is_stable_orientation);
        //std::cout << "\nx_velocity: " << live_data.x_velocity << "\ny_velocity: " << live_data.y_velocity << "\nz_velocity: " << live_data.z_velocity << std::endl;
        /*************************/

        Sleep(MS_PER_SECOND / REFRESH_RATE_HZ);
        i++;
    }

    return 0;
}