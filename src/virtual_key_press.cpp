#include <iostream>
#include <Windows.h>

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

void press_key(int key_code)
{
    INPUT inputs[2] = {};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key_code;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key_code;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(sizeof(inputs)/sizeof(inputs[0]), inputs, sizeof(INPUT));

    switch (key_code)
    {
        case FULLSTOP_KEY:
            std::cout << "-> - Roll Right" << std::endl;
            break; 
        case COMMA_KEY:
            std::cout << "<- - Roll Left" << std::endl;
            break; 
        case LEFT_ARROW:
            std::cout << "<- - Yaw left" << std::endl;
            break;
        case UP_ARROW:
            std::cout << "^  - Pitch up" << std::endl;
            break;
        case RIGHT_ARROW:
            std::cout << "-> - Yaw Right" << std::endl;
            break;
        case DOWN_ARROW:
            std::cout << "\\/ - Pitch down" << std::endl;
            break;
        case W_KEY:
            std::cout << "^  - Pos up" << std::endl;
            break;
        case A_KEY:
            std::cout << "<- - Pos left" << std::endl;
            break;
        case S_KEY:
            std::cout << "\\/ - Pos down" << std::endl;
            break;
        case E_KEY:
            std::cout << "^  - Pos forwards" << std::endl;
            break;
        case Q_KEY:
            std::cout << "\\/ - Pos backwards" << std::endl;
            break;
    }
}