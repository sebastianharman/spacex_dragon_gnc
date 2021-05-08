#include <string>
#include <vector>
#include <fstream>

#include "sim_data.h"

sim_data::sim_data()
{
    roll_val = roll_velocity = pitch_val = pitch_velocity = yaw_val = yaw_velocity = x_val = y_val = z_val = range_val = rate = x_velocity = y_velocity = z_velocity = 0.0;
}

void sim_data::set_all_values(std::vector <double> constructor_data)
{
    roll_val = constructor_data[0];
    pitch_val = constructor_data[1];
    yaw_val = constructor_data[2];

    x_val = constructor_data[3];
    y_val = constructor_data[4];
    z_val = constructor_data[5];

    range_val = constructor_data[6];
    rate = constructor_data[7];
}
