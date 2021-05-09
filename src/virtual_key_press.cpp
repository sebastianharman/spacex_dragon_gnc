#include <iostream>
#include <Windows.h>

#include "sim_data.h"
#include "key_codes.h"

void press_key(int key_code, sim_data& data, bool perform_switch)
{
    INPUT inputs[2] = {};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key_code;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key_code;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(sizeof(inputs)/sizeof(inputs[0]), inputs, sizeof(INPUT));

    if (perform_switch)
    {
        switch (key_code)
        {
            case FULLSTOP_KEY:
                std::cout << "-> - Roll Right" << std::endl;
                data.roll_velocity++;
                break; 
            case COMMA_KEY:
                std::cout << "<- - Roll Left" << std::endl;
                data.roll_velocity--;
                break; 
            case LEFT_ARROW:
                std::cout << "<- - Yaw left" << std::endl;
                data.yaw_velocity--;
                break;
            case UP_ARROW:
                std::cout << "^  - Pitch up" << std::endl;
                data.pitch_velocity--;
                break;
            case RIGHT_ARROW:
                std::cout << "-> - Yaw Right" << std::endl;
                data.yaw_velocity++;
                break;
            case DOWN_ARROW:
                std::cout << "\\/ - Pitch down" << std::endl;
                data.pitch_velocity++;
                break;
            case W_KEY:
                std::cout << "^  - Pos up" << std::endl;
                data.z_velocity++;
                break;
            case A_KEY:
                std::cout << "<- - Pos left" << std::endl;
                data.y_velocity--;
                break;
            case S_KEY:
                std::cout << "\\/ - Pos down" << std::endl;
                data.z_velocity--;
                break;
            case D_KEY:
                std::cout << "-> - Pos right" << std::endl;
                data.y_velocity++;
                break;
            case E_KEY:
                std::cout << "^  - Pos forwards" << std::endl;
                break;
            case Q_KEY:
                std::cout << "\\/ - Pos backwards" << std::endl;
                break;
        }
    }
}