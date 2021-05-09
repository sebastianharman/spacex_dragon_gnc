#include <iostream>

#include "sim_data.h"
#include "virtual_key_press.h"
#include "key_codes.h"

/*** flight profile config ***/
// orientation
const double FAST_ORIENTATION_VELOCITY =         5.0; // rate > threshold
const double SLOW_ORIENTATION_VELOCITY =         1.0; // rate < threshold
const double ORIENTATION_VELOCITY_THRESHOLD =    5.0; // degrees before it slows down
const double ORIENTATION_PRECISON =              0.1;

// rate
const double FAST_RATE =                         -1.0; // rate > threshold
const double SLOW_RATE =                         -0.1; // rate < threshold
const double RATE_PRECISON =                     0.05;
const double RANGE_THRESHOLD =                   10.0; // how far away dragon must be before it slows down

// position
double POSITION_TARGET_VELOCITY =                4;

// general
const double ITERATION_RESET =                   4; // how many iterations of i before reset

void orientation_check(double orientation_value, int orientation_velocity, int keycode_negative, int keycode_positive, sim_data& data);
void rate_check(int keycode_negative, int keycode_positive, sim_data& data);
void position_check(double position_value, double position_velocity, int keycode_negative, int keycode_positive, sim_data& data);

void gnc_loop(sim_data& data, int& i, bool is_stable_orientation)
{
    /*** orientation gnc ***/
    orientation_check(data.roll_val, data.roll_velocity, COMMA_KEY, FULLSTOP_KEY, data); // roll
    orientation_check(data.pitch_val, data.pitch_velocity, UP_ARROW, DOWN_ARROW, data); // pitch
    orientation_check(data.yaw_val, data.yaw_velocity, LEFT_ARROW, RIGHT_ARROW, data); // yaw

    /*** position gnc ***/
    if (i != 0 && i % 4 == 0) // every 4 iterations of the main gnc loop
    {
        i = 0;
        rate_check(Q_KEY, E_KEY, data); // controls the rate
        if (is_stable_orientation)
        {
            position_check(data.y_val, data.y_velocity, A_KEY, D_KEY, data); // Y position
            position_check(data.z_val, data.z_velocity, S_KEY, W_KEY, data); // Z position
        }
    }
}

void orientation_check(double orientation_value, int orientation_velocity, int keycode_negative, int keycode_positive, sim_data& data)
{
    if (orientation_value < ORIENTATION_PRECISON && orientation_value > (ORIENTATION_PRECISON * -1))
    {
        if (orientation_velocity > 0)
        {
            for (int i = 0; i < abs(orientation_velocity); i++)
                press_key(keycode_negative, data, true);
            return;
        }
        else if (orientation_velocity < 0)
        {
            for (int i = 0; i < abs(orientation_velocity); i++)
                press_key(keycode_positive, data, true);
            return;
        }
    }
    if (orientation_value >= ORIENTATION_PRECISON) // positive
    {
        if (orientation_value > ORIENTATION_VELOCITY_THRESHOLD) // fast
        {
            if (orientation_velocity > FAST_ORIENTATION_VELOCITY)
                press_key(keycode_negative, data, true);
            else if (orientation_velocity < FAST_ORIENTATION_VELOCITY)
                press_key(keycode_positive, data, true);
        }
        else // slow
        {
            if (orientation_velocity > SLOW_ORIENTATION_VELOCITY)
                press_key(keycode_negative, data, true);
            else if (orientation_velocity < SLOW_ORIENTATION_VELOCITY)
                press_key(keycode_positive, data, true);
        }
    }
    else if (orientation_value <= (ORIENTATION_PRECISON * -1)) // negative
    {
        if (orientation_value < (ORIENTATION_VELOCITY_THRESHOLD * -1)) // fast
        {
            if (orientation_velocity < (FAST_ORIENTATION_VELOCITY * -1))
                press_key(keycode_positive, data, true);
            else if (orientation_velocity > (FAST_ORIENTATION_VELOCITY * -1))
                press_key(keycode_negative, data, true);
        }
        else // slow
        {
            if (orientation_velocity > (SLOW_ORIENTATION_VELOCITY * -1))
                press_key(keycode_negative, data, true);
            else if (orientation_velocity < (SLOW_ORIENTATION_VELOCITY * -1))
                press_key(keycode_positive, data, true);
        }
    }
}

void rate_check(int keycode_negative, int keycode_positive, sim_data& data)
{
    if (data.x_val > RANGE_THRESHOLD) // far away from dock - faster
    {
        if (data.rate < (FAST_RATE - RATE_PRECISON))
            press_key(keycode_negative, data, true);
        else if (data.rate > (FAST_RATE + RATE_PRECISON))
            press_key(keycode_positive, data, true);
    }
    else if (data.x_val < RANGE_THRESHOLD) // close to dock, fly slow
    {
        if (data.rate < (SLOW_RATE - RATE_PRECISON))
            press_key(keycode_negative, data, true);
        else if (data.rate > (SLOW_RATE + RATE_PRECISON))
            press_key(keycode_positive, data, true);
    }
}

void position_check(double position_value, double position_velocity, int keycode_negative, int keycode_positive, sim_data& data)
{
    if (position_value > 0) // positive
    {
        if (position_velocity > (POSITION_TARGET_VELOCITY * -1))
            press_key(keycode_negative, data, true);
        else if (position_value < (POSITION_TARGET_VELOCITY * -1))
            press_key(keycode_positive, data, true);
    }
    else if (position_value < 0) // negative
    {
        if (position_velocity > POSITION_TARGET_VELOCITY)
            press_key(keycode_negative, data, true);
        else if (position_value < POSITION_TARGET_VELOCITY)
            press_key(keycode_positive, data, true);
    }
    
    if (data.x_val < RANGE_THRESHOLD && data.y_val == 0.0 && data.x_val == 0.0)
        POSITION_TARGET_VELOCITY = 1; // closer to docking
}