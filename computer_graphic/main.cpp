#include <iostream>

class NewtonLaws {
public:
    // Variables
    float force;
    float mass;
    float acceleration;
    float velocity;
    float distance;
    float time;
    float gravity = 9.8;  // Gravity constant (m/s^2)

    // Constructor
    NewtonLaws() : force(0), mass(0), acceleration(0), velocity(0), distance(0), time(0) {}

    // Newton's First Law (Inertia)
    void firstLaw() {
        // An object will remain at rest or in uniform motion unless acted upon by an external force.
        // This law is demonstrated when no external force acts on the object.
        if (force == 0) {
            std::cout << "Object is either at rest or moving with constant velocity." << std::endl;
        } else {
            std::cout << "An external force is acting on the object." << std::endl;
        }
    }

    // Newton's Second Law (F = ma)
    void secondLaw() {
        // F = m * a
        if (mass != 0) {
            force = mass * acceleration;  // Calculate force based on mass and acceleration
            std::cout << "Force (F) is: " << force << " N (Newton)" << std::endl;
        } else {
            std::cout << "Mass cannot be zero." << std::endl;
        }
    }

    // Newton's Third Law (Action and Reaction)
    void thirdLaw() {
        // For every action, there is an equal and opposite reaction.
        std::cout << "Action and Reaction forces are equal in magnitude and opposite in direction." << std::endl;
    }

    // Method to calculate distance under constant acceleration (from rest)
    void calculateDistance() {
        // d = 0.5 * a * t^2 (assuming initial velocity is 0)
        distance = 0.5 * acceleration * time * time;
        std::cout << "The distance traveled is: " << distance << " meters" << std::endl;
    }

    // Method to calculate velocity after a given time under constant acceleration
    void calculateVelocity() {
        // v = u + at (assuming initial velocity u = 0)
        velocity = acceleration * time;
        std::cout << "The velocity after " << time << " seconds is: " << velocity << " m/s" << std::endl;
    }
    
};

int main() {
    NewtonLaws nl;

    // Set the mass and acceleration values
    nl.mass = 10.0f; // mass in kilograms
    nl.acceleration = 2.0f; // acceleration in m/s^2
    nl.time = 6.0f; // time in seconds

    // // Call Newton's laws methods
    // nl.firstLaw();  // First Law (Inertia)
    // nl.secondLaw(); // Second Law (F = ma)
    // nl.thirdLaw();  // Third Law (Action and Reaction)

    // Calculate distance and velocity
    nl.calculateDistance();
    nl.calculateVelocity();

    return 0;
}
