#include <vector>

class sim_data {
    public:
        double roll_val, roll_velocity, pitch_val, pitch_velocity, yaw_val, yaw_velocity, x_val, y_val, z_val, range_val, rate;

        //sim_data(double roll_val_construct, double roll_velocity_construct, double pitch_val_construct, double pitch_velocity_construct, double yaw_val_construct, double yaw_velocity_construct, double x_val_construct, double y_val_construct, double z_val_construct, double range_val_construct, double rate_construct);

        void set_all_vals(std::vector <double> constructor_data);

};