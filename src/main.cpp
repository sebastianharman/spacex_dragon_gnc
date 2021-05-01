#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

#include "sim_data.h"
#include "virtual_key_press.h"

#define file_path           "sim_data.csv"
#define refresh_rate_hz     10
#define ms_per_second       1000

int main()
{
    sim_data live_data = sim_data();
    sim_data prev_data = sim_data();
    std::vector <double> data_buffer(11, 0.0); // a vector to hold file data 
    std::string line_buffer;

    while (1)
    {
        std::ifstream file (file_path);
        for (int i = 0; getline (file, line_buffer); ++i)
        {
            data_buffer[i] = (atof(line_buffer.c_str()));
        }
        file.close();

        live_data.set_all_values(data_buffer);

        // position velocity calculations
        live_data.x_velocity = (prev_data.x_val - live_data.x_val) * refresh_rate_hz;
        live_data.y_velocity = (prev_data.y_val - live_data.y_val) * refresh_rate_hz;
        live_data.z_velocity = (prev_data.z_val - live_data.z_val) * refresh_rate_hz;

        /*************************/



        /*************************/

        Sleep(ms_per_second / refresh_rate_hz);

        prev_data.set_all_values(data_buffer); // constructs class which holds data from last loop

    }

    return 0;
}