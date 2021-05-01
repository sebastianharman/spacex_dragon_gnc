#include <vector>

class sim_data {
    public:
        double roll_val, roll_velocity, pitch_val, pitch_velocity, yaw_val, yaw_velocity, x_val, y_val, z_val, range_val, rate;

        void set_all_vals(std::vector <double> constructor_data);

};