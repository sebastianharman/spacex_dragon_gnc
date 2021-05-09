# spacex_dragon_gnc

A program to automatically fly the SpaceX Crew Dragon spacecraft in to dock at the ISS in the [SpaceX Dragon Simulator](https://iss-sim.spacex.com/).

### Only supports Windows  

This program is used by running the Python script (sim_data.py), and then the .exe built from the C++ code. The Python code launches a new browser windows and retrieves sim data from the it in real time, and the C++ code controls the spacecraft based off that data. 

## Requirements:
* Python 3
* Selenium Python library
* Windows
* G++ compiler
* chromedriver (or other browser equivalent)

### The C++ code interacts with the sim using virtual key presses, the program can be stopped instantly by holding the 'P' key on the keyboard. Do not touch sim while running, as it may break the config.

The C++ code can be built by running the "make" command in the src/ directory. The makefile uses g++ as the compiler.

The code here uses the chrome browser with chromedriver, however this can be modified to use any browser/browser version.

