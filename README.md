# ESP32 and FRDM-K64F I2C Communication

## Task 1: Control LED State via Serial Terminal and I2C

### Overview
In this project, the **ESP32** and the **FRDM-K64F** communicate using the **I2C protocol**. The ESP32 acts as the **I2C Master**, and the FRDM-K64F functions as the **I2C Slave**. The goal is to send a user-defined LED state (`red`, `green`, `blue`, or `off`) from the ESP32 to the FRDM-K64F, which will control its built-in LED based on the received command. Once the LED state is changed, the FRDM-K64F sends a confirmation message (`done`) back to the ESP32.

### Components Used
- **ESP32** (I2C Master): This board handles user input from the serial terminal, sends the LED state to the FRDM-K64F via I2C, and receives confirmation from the FRDM-K64F.
- **FRDM-K64F** (I2C Slave): This board receives the LED state from the ESP32, controls its on-board LED accordingly, and sends a confirmation message back to the ESP32.

### Communication Flow
1. **User Input via Serial**: The user enters the desired LED state (`red`, `green`, `blue`, or `off`) into the serial terminal of the ESP32.
2. **ESP32 Sends Data**: The ESP32 sends the LED state to the FRDM-K64F using I2C communication.
3. **FRDM-K64F Changes LED State**: Upon receiving the LED state, the FRDM-K64F controls its on-board LED:
   - **Red** LED is turned on for the `red` command.
   - **Green** LED is turned on for the `green` command.
   - **Blue** LED is turned on for the `blue` command.
   - All LEDs are turned off for the `off` command.
4. **Confirmation**: The FRDM-K64F sends a `done` message back to the ESP32 to confirm that the LED state has been changed.
5. **ESP32 Displays Confirmation**: The ESP32 receives the confirmation message and displays it in the serial monitor.

### How it Works:
- The ESP32 continuously listens for user input from the serial terminal. Upon receiving a valid LED state command, it sends the command over I2C to the FRDM-K64F.
- The FRDM-K64F, acting as the I2C slave, processes the command, controls the on-board LED according to the received state, and then sends a confirmation back to the ESP32.
- This process repeats as the user continues to input different LED states.

### Key Technologies:
- **I2C Communication**: Used for data exchange between the ESP32 (Master) and FRDM-K64F (Slave).
- **Serial Communication**: Used to interact with the user via the serial monitor on the ESP32.
- **GPIO Control**: Used on the FRDM-K64F to control the built-in LEDs based on the received state.

---

## Challenge Solved: Board Entering Bootloader Mode

While working on this project, I encountered an issue where the **FRDM-K64F** board kept entering **bootloader mode** repeatedly, which prevented normal operation. After some investigation, I found a solution:

1. **Problem**: The FRDM-K64F board would go into bootloader mode every time I tried to program it, preventing it from properly running the code.
2. **Solution**: I solved the issue by copying the `0254_k20dx_frdmk64f_0x5000.bin` file, which I obtained from the [DAPLink website](https://daplink.io/?board=FRDM-K64F), and then restarting the board.
3. **Result**: After copying the `.bin` file and restarting, the board successfully stopped entering bootloader mode and functioned as expected, allowing me to proceed with the I2C communication project.

---

## ESP32 PlatformIO USB Connection Issue

While working on the **ESP32** platform using **PlatformIO**, I encountered an issue where the USB port used for uploading or monitoring sometimes became **busy** and the ESP32 could not connect. In such cases, you may need to manually release the port to allow the upload or monitoring to resume.

### Problem:
Sometimes, the **ESP32** fails to connect to the USB port because the port is reported as "busy." This can prevent uploading or serial monitoring from working properly.

### Solution:
1. Identify the process that is using the **USB port** by running the following command:

    ```bash
    sudo lsof /dev/ttyUSB0
    ```

2. This will show you the **process ID (PID)** of the program using the USB port. Once you have the PID, you can kill the process by running:

    ```bash
    sudo kill <process_number>
    ```

    Replace `<process_number>` with the actual process ID (PID) from the previous command.

3. After killing the process, you should be able to resume the upload and monitoring process by running the normal **PlatformIO** upload or monitor command:

    ```bash
    pio run --target upload
    pio device monitor
    ```

4. The ESP32 should now be able to connect to the USB port, and you can continue with your work.

---

### Example Flow
Here’s how the interaction would look like during normal operation:

- **User Input**: "red"
  - **ESP32** sends the command "red" via I2C to the FRDM-K64F.
  - **FRDM-K64F** turns on the **red** LED.
  - **FRDM-K64F** sends the confirmation message "done".
  - **ESP32** prints "Received: done" to the serial monitor.

- **User Input**: "green"
  - **ESP32** sends the command "green" via I2C to the FRDM-K64F.
  - **FRDM-K64F** turns on the **green** LED.
  - **FRDM-K64F** sends the confirmation message "done".
  - **ESP32** prints "Received: done" to the serial monitor.

---

### Conclusion
This project demonstrates the use of I2C communication between two microcontrollers (ESP32 and FRDM-K64F), where one (ESP32) acts as the master, sending commands to the slave (FRDM-K64F). The slave processes the commands, controls hardware (LEDs), and responds with a confirmation. This system can be extended to control more hardware components or handle more complex commands in future implementations.

Additionally, the challenge of the **FRDM-K64F** repeatedly entering bootloader mode was resolved by copying a firmware file and restarting the board, ensuring that the communication could proceed without further issues.

Finally, the **ESP32 USB connection issue** was resolved by killing the process that was using the USB port, allowing the upload and monitoring to continue smoothly.
