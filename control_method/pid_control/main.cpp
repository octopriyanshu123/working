#include <iostream>
#include <vector>
#include <thread>  // Include this for sleep functionality
#include <chrono>  // For time duration specification

#include <iostream>
#include <PID.h>  // Include the header for your PID class

// Function to simulate controlling the AC temperature using PID
void ControlTemperature(PID& pid, double target_temp, double initial_temp) {
    double current_temp = initial_temp;
    double temperature_change;

    // Run the PID controller until we reach the target temperature
    while (std::abs(current_temp - target_temp) > 0.1) {  // Loop until the temperature is close to the target
        double cte = target_temp - current_temp;  // Cross-track error (temperature error)
        pid.UpdateError(cte);  // Update the errors

        // Calculate the total PID error (this is the adjustment needed)
        temperature_change = pid.TotalError();  // This value should adjust the system

        // Apply the change to the current temperature (simplified simulation)
        current_temp += temperature_change;

        // Output the current state
        std::cout << "Current Temperature: " << current_temp << " (Target: " << target_temp << ")\n";

        // Sleep for 1 second (simulate real-time control)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Reached target temperature: " << target_temp << "!" << std::endl;
}

int main() {
    PID pid;  // Create PID controller object

    // Initialize PID controller with arbitrary values for Kp, Ki, Kd
    pid.Init(0.1, 0.01, 0.01);  // Set appropriate tuning constants

    double target_temp = 22.0;  // Target temperature (desired temperature)
    double initial_temp = 30.0;  // Initial temperature (actual temperature)

    // Control the temperature
    ControlTemperature(pid, target_temp, initial_temp);

    return 0;
}



// #include <PID.h> 

// PID pid;
// pid.Init(0.1, 0.01, 0.01);
// pid.UpdateError(cte);
// pid.TotalError();