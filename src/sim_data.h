#ifndef SIM_DATA_H
#define SIM_DATA_H

#include <vector>

class sim_data {
    public:
        double roll_val, pitch_val, yaw_val, x_val, y_val, z_val, range_val, rate;
        int roll_velocity, pitch_velocity, yaw_velocity, x_velocity, y_velocity, z_velocity;

        sim_data();
        void set_live_values(std::vector <double> constructor_data);
};

#endif