---

# PID Library Documentation

## Overview

The **PID Library** provides a simple and effective way to implement the **Proportional-Integral-Derivative (PID)** control algorithm in C++. This library helps you calculate a control output based on the difference between the desired value (setpoint) and the actual value (measured value). It is commonly used in systems like robotics, temperature control, or any other system that requires adjusting variables to reach a desired target.

With this library, users can control a system by adjusting its error response based on three components:
1. **Proportional (P)**: Adjusts based on the current error.
2. **Integral (I)**: Adjusts based on the accumulated past error.
3. **Derivative (D)**: Adjusts based on the rate of change of the error.

## Features

- **Adjustable Gains**: You can set the proportional, integral, and derivative gains (`Kp`, `Ki`, `Kd`) to tune the controller.
- **Real-time Control**: Update errors dynamically and compute control signals on the fly.
- **Easy Integration**: Integrates seamlessly into any C++ project.
  
## Installation

To install the PID library, follow these steps:

1. Clone the repository to your local machine:
   
   ```sh
   git clone <repository-url>
   ```

2. Navigate to the library directory:
   
   ```sh
   cd pid
   ```

3. Build the library using CMake:

   ```sh
   mkdir build
   cd build
   cmake ..
   make
   sudo make install
   sudo ldconfig
   ```

4. Optionally, create a symlink for the library:

   ```sh
   sudo ln -s /usr/lib/libpid.so /usr/lib64/libpid.so
   ```

## API Documentation

The PID library is designed to be simple to use. Below are the available functions and their detailed explanations.

### `class PID`

The `PID` class encapsulates the PID control logic. This class exposes functions to set up the PID controller, update errors, and calculate the control output.

---

### **Public Functions**

#### 1. **`PID()`** - Constructor
This is the default constructor for the `PID` class. It initializes all the error values and gains to zero.

- **Usage**:
  
  ```cpp
  PID pid;
  ```

---

#### 2. **`virtual ~PID()`** - Destructor
This is the destructor for the `PID` class. It cleans up the class when it is no longer needed.

- **Usage**:
  
  ```cpp
  // No need to explicitly call, will be called automatically when the object is destroyed.
  ```

---

#### 3. **`void Init(double Kp, double Ki, double Kd)`** - Initialize the PID Controller
This function initializes the PID controller with the specified gains for the Proportional, Integral, and Derivative terms. The controller must be initialized before using it to update errors or calculate the total error.

- **Parameters**:
  - `Kp` (double): Proportional gain constant.
  - `Ki` (double): Integral gain constant.
  - `Kd` (double): Derivative gain constant.
  
- **Usage**:
  
  ```cpp
  PID pid;
  pid.Init(0.1, 0.01, 0.01);  // Initialize with custom gains for P, I, and D
  ```

---

#### 4. **`void UpdateError(double cte)`** - Update the PID Errors
This function updates the three error terms (Proportional, Integral, Derivative) based on the current **cross-track error** (`cte`), which represents the difference between the target (desired) value and the actual value. You should call this function in each time step or iteration.

- **Parameters**:
  - `cte` (double): The current error (e.g., the difference between the desired and actual temperature).
  
- **Usage**:
  
  ```cpp
  double current_error = target - current_value;  // Calculate error
  pid.UpdateError(current_error);  // Update PID errors
  ```

---

#### 5. **`double TotalError()`** - Calculate the Total PID Error
This function calculates the total control signal that should be applied to the system based on the current PID errors. The total error is calculated as the weighted sum of the proportional, integral, and derivative errors, using the initialized gains (`Kp`, `Ki`, `Kd`).

- **Returns**:
  - **double**: The total PID error (control output), which is the sum of all the individual errors weighted by their respective gains.

- **Usage**:
  
  ```cpp
  double control_signal = pid.TotalError();  // Calculate the control signal to apply
  ```

---

## Additional Notes

- **Real-time Control**: The PID controller works in real-time and can be called repeatedly with updated error values in systems that require continuous adjustment.
- **Fine-Tuning**: The performance of the PID controller highly depends on the tuning of `Kp`, `Ki`, and `Kd`. These values can be adjusted to optimize the system response.
  
---

## Summary of Available Functions

- **`PID()`**: Constructor for creating a `PID` object.
- **`virtual ~PID()`**: Destructor to clean up resources.
- **`void Init(double Kp, double Ki, double Kd)`**: Initializes the PID controller with the given gains.
- **`void UpdateError(double cte)`**: Updates the PID errors with the current error value.
- **`double TotalError()`**: Returns the total control signal calculated from the PID errors.

---

## License

This library is licensed under the [MIT License](LICENSE).

---

### Questions?

If you have any questions or need further assistance, feel free to open an issue on the repository or contact the maintainer directly.

---

This documentation provides a clear, easy-to-understand breakdown of the library's functionality, along with example code to help users quickly get started. By focusing on the available functions and their purpose, users will find it comfortable to integrate the PID library into their own projects.