# spacex_dragon_gnc

A program to automatically fly the SpaceX Crew Dragon spacecraft in to dock at the ISS in the [SpaceX Dragon Simulator](https://iss-sim.spacex.com/).

### Only supports Windows









This program is used by running the Python script (data_sim.py), and then the .exe from the C++ code once the sim has loaded in. The Python code retrieves sim data from the browser, and the C++ code controls the spacecraft. 

The C++ code can be built by running the "make" command in the src/ directory. Uses G++ as the compiler.

## Requirements:
* Python 3
* Selenium Python library
* Windows
* G++ compiler

### The C++ code interacts with the sim using virtual key presses, it can be stopped instantly by pressing the 'P' key on the keyboard.


The code here uses the chrome browser with chromdriver, however this can be modified to use any browser/browser version.

