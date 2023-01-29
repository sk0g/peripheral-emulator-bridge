# peripheral-emulator-bridge
Pico C++ "Bridge" for microcontroller-web app communication

# What Is It?
This program acts as a bridge between the physical pins of a microprocessor, and the web app. 

* Input pins notify of pin value changes (`n25` turns on GPIO# 25, `f02` turns off GPIO# 2)
* Output pins are driven by serial communication (`22|0` for GPIO#22 being set to off, `12|1` for GPIO# 12 being set to on)
* Pulse pins send a timed, microsecond-precision pulse on the selected pin (`07,500` will pulse GPIO# 7 for 500 microseconds)

# How Does It Work?
1. The accompanying web app opens a serial connection to the device
2. Output and pulse pins are controlled by the app
3. Input pins are for interfacing with other devices, or with simulated devices
4. The first core processes interrupts and carries out any changes required on the task queue
5. Second core performs all serial communication, and manages the task queue
