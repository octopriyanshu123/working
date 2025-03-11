#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

class TemperatureController {
private:
    const double setpoint = 5.0; 
    double currentTemp = 23.8; 
    std::atomic<bool> isRunning{true}; // Atomic flag to control the running state of the thread

    void changeTemp(double delta) {
        currentTemp += delta;
    }

    void bangBangControl() {
        if(currentTemp == setpoint) {
            std::cout << "We reached the target point\n";
            isRunning = false; // Stop the control loop
        } else if (currentTemp < setpoint) {
            std::cout << "Heating on\n";
            changeTemp(0.5); 
        } else if (currentTemp > setpoint) {
            std::cout << "Cooling on\n";
            changeTemp(-0.5); 
        } else {
            std::cout << "Temperature at setpoint\n";
        }
    }

public:
    void startControlLoop() {
        while (isRunning) {
            bangBangControl();
            std::cout << "Current temperature: " << currentTemp << "°C\n";
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate periodic check
        }
    }
};

int main() {
    TemperatureController controller;

    // Start the control loop in a separate thread
    std::thread controlThread(&TemperatureController::startControlLoop, &controller);

    // Wait for the control thread to finish
    controlThread.join();

    return 0;
}
