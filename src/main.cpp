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
    std::vector <double> data_buffer(11, 0.0); // a vector with all of the live data from the file
    std::string line_buffer;

    while (1)
    {
        std::ifstream file (file_path); // the file being written to by the python script
        for (int i = 0; getline (file, line_buffer); ++i) // goes line by line in the file and adds its contents to the vector
        {
            data_buffer[i] = (atof(line_buffer.c_str()));
        }
        file.close();

        sim_data live_data;
        live_data.set_all_vals(data_buffer); // constructs the class to store the live data
        /*************************/



        /*************************/
        Sleep(ms_per_second / refresh_rate_hz);

        sim_data prev_data;
        prev_data.set_all_vals(data_buffer); // constructs class which holds data from last loop
        }

    return 0;
}