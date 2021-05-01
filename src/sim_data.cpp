#include <string>
#include <vector>
#include <fstream>

#include "sim_data.h"

void sim_data::set_all_vals(std::vector <double> constructor_data)
{
    roll_val = constructor_data[0];
    roll_velocity = constructor_data[1];

    pitch_val = constructor_data[2];
    pitch_velocity = constructor_data[3];

    yaw_val = constructor_data[4];
    yaw_velocity = constructor_data[5];

    x_val = constructor_data[6];
    y_val = constructor_data[7];
    z_val = constructor_data[8];

    range_val = constructor_data[9];
    rate = constructor_data[10];
}
