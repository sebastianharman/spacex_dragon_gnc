#include <iostream>

#include "sim_data.h"
#include "virtual_key_press.h"

// windows virtual key codes
#define FULLSTOP_KEY        0xBE    // roll right
#define COMMA_KEY           0xBC    // roll left
#define LEFT_ARROW          0x25    // yaw left
#define UP_ARROW            0x26    // pitch up
#define RIGHT_ARROW         0x27    // yaw right
#define DOWN_ARROW          0x28    // pitch down
#define W_KEY               0x57    // pos up
#define A_KEY               0x41    // pos left
#define S_KEY               0x53    // pos down
#define D_KEY               0x44    // pos right
#define E_KEY               0x45    // pos forwards
#define Q_KEY               0x51    // pos backwards

/*** flight profile config ***/
// orientation
const double FAST_ORIENTATION_VELOCITY =         5.0;
const double SLOW_ORIENTATION_VELOCITY =         1.0;
const double ORIENTATION_VELOCITY_THRESHOLD =    5.0;
const double ORIENTATION_PRECISON =              0.1;

// rate
const double FAST_RATE =                         -1.0;
const double SLOW_RATE =                         -0.1;
const double RATE_PRECISON =                     0.05;
const double RANGE_THRESHOLD =                   40.0;

// position
const double POSITION_TARGET_VELOCITY =          0.4;

void orientation_check(double orientation_value, double orientation_velocity, int keycode_negative, int keycode_positive, sim_data& data);
void rate_check(int keycode_negative, int keycode_positive, sim_data& data);
void position_check(double position_value, double position_velocity, int keycode_negative, int keycode_positive, sim_data& data);

void gnc_loop(sim_data& data)
{
    /*** orientation gnc ***/
    // roll
    orientation_check(data.roll_val, data.roll_velocity, COMMA_KEY, FULLSTOP_KEY, data);
    // pitch
    orientation_check(data.pitch_val, data.pitch_velocity, UP_ARROW, DOWN_ARROW, data);
    // yaw
    orientation_check(data.yaw_val, data.yaw_velocity, LEFT_ARROW, RIGHT_ARROW, data); 

    /*** position gnc ***/
    rate_check(Q_KEY, E_KEY, data);

    /*** position gnc ***/
    position_check(data.y_val, data.y_velocity, A_KEY, D_KEY, data);
}

void orientation_check(double orientation_value, double orientation_velocity, int keycode_negative, int keycode_positive, sim_data& data)
{
    if (orientation_value < ORIENTATION_PRECISON && orientation_value > (ORIENTATION_PRECISON * -1))
    {
        if (orientation_velocity > 0)
        {
            for (int i = 0; i < abs(orientation_velocity); i++)
                press_key(keycode_negative, data);
            return;
        }
        else if (orientation_velocity < 0)
        {
            for (int i = 0; i < abs(orientation_velocity); i++)
                press_key(keycode_positive, data);
            return;
        }
    }
    if (orientation_value >= ORIENTATION_PRECISON) // positive
    {
        if (orientation_value > ORIENTATION_VELOCITY_THRESHOLD) // fast
        {
            if (orientation_velocity > FAST_ORIENTATION_VELOCITY)
                press_key(keycode_negative, data);
            else if (orientation_velocity < FAST_ORIENTATION_VELOCITY)
                press_key(keycode_positive, data);
        }
        else // slow
        {
            if (orientation_velocity > SLOW_ORIENTATION_VELOCITY)
                press_key(keycode_negative, data);
            else if (orientation_velocity < SLOW_ORIENTATION_VELOCITY)
                press_key(keycode_positive, data);
        }
    }
    else if (orientation_value <= (ORIENTATION_PRECISON * -1)) // negative
    {
        if (orientation_value < (ORIENTATION_VELOCITY_THRESHOLD * -1)) // fast
        {
            if (orientation_velocity < (FAST_ORIENTATION_VELOCITY * -1))
                press_key(keycode_positive, data);
            else if (orientation_velocity > (FAST_ORIENTATION_VELOCITY * -1))
                press_key(keycode_negative, data);
        }
        else // slow
        {
            if (orientation_velocity > (SLOW_ORIENTATION_VELOCITY * -1))
                press_key(keycode_negative, data);
            else if (orientation_velocity < (SLOW_ORIENTATION_VELOCITY * -1))
                press_key(keycode_positive, data);
        }
    }
}

void rate_check(int keycode_negative, int keycode_positive, sim_data& data)
{
    if (data.x_val > RANGE_THRESHOLD) // far away from dock - faster
    {
        if (data.rate < (FAST_RATE - RATE_PRECISON))
            press_key(keycode_negative, data);
        else if (data.rate > (FAST_RATE + RATE_PRECISON))
            press_key(keycode_positive, data);
    }
    else if (data.x_val < RANGE_THRESHOLD) // close to dock, fly slow
    {
        if (data.rate < (SLOW_RATE - RATE_PRECISON))
            press_key(keycode_negative, data);
        else if (data.rate > (SLOW_RATE + RATE_PRECISON))
            press_key(keycode_positive, data);
    }
}

void position_check(double position_value, double position_velocity, int keycode_negative, int keycode_positive, sim_data& data)
{
    if (data.x_val > RANGE_THRESHOLD) // far away
    {
        if (position_value > 0) // positive
        {
            if (position_velocity < POSITION_TARGET_VELOCITY)
                press_key(keycode_negative, data);
            else if (position_velocity > POSITION_TARGET_VELOCITY)
                press_key(keycode_positive, data);
        }
        else // negative
        {
            if (position_velocity < (POSITION_TARGET_VELOCITY * -1))
                press_key(keycode_negative, data);
            else if (position_velocity > (POSITION_TARGET_VELOCITY * -1))
                press_key(keycode_positive, data);
        }
    }
    else if (data.x_val < RANGE_THRESHOLD) // close - replicates each movement with slight delay
    {

    }
}