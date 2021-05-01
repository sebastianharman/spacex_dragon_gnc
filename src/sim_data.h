#include <vector>

class sim_data {
    public:
        double roll_val, roll_velocity, pitch_val, pitch_velocity, yaw_val, yaw_velocity, x_val, y_val, z_val, x_velocity, y_velocity, z_velocity, range_val, rate;

        sim_data();
        void set_all_values(std::vector <double> constructor_data);

};