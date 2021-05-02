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

int main()
{
    sim_data live_data = sim_data(); // current flight data
    sim_data prev_data = sim_data(); // last state recorded
    std::vector <double> data_buffer(11, 0.0); // a vector to hold file data 
    std::string line_buffer;
    bool sleep_on_end = true;

    while (1)
    {
        std::ifstream file (FILE_PATH);
        for (int i = 0; getline (file, line_buffer); ++i)
        {
            data_buffer[i] = (atof(line_buffer.c_str()));
        }
        file.close();

        live_data.set_all_values(data_buffer);

        // position velocity calculations
        live_data.x_velocity = (prev_data.x_val - live_data.x_val) * REFRESH_RATE_HZ;
        live_data.y_velocity = (prev_data.y_val - live_data.y_val) * REFRESH_RATE_HZ;
        live_data.z_velocity = (prev_data.z_val - live_data.z_val) * REFRESH_RATE_HZ;

        /*************************/

        if (GetKeyState(P_KEY) < 0)
        {
            return 0;
        }

        gnc_loop(live_data);

        /*************************/

        if (sleep_on_end)
            Sleep(MS_PER_SECOND / REFRESH_RATE_HZ);
        else
            sleep_on_end= true;

        prev_data.set_all_values(data_buffer); // constructs class which holds data from last loop
    }

    return 0;
}