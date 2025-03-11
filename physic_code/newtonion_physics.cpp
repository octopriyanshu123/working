// Clsical physic only work on the low speend opbect
// micro level

// low speed and big object;

/*

Newton's laws of motion are three physical laws that describe the relationship between the motion of an object and the forces acting on it. These laws, which provide the basis for Newtonian mechanics, can be paraphrased as follows:

A body remains at rest, or in motion at a constant speed in a straight line, except insofar as it is acted upon by a force.
At any instant of time, the net force on a body is equal to the body's acceleration multiplied by its mass or, equivalently, the rate at which the body's momentum is changing with time.
If two bodies exert forces on each other, these forces have the same magnitude but opposite directions.

*/

// force = mass * acceleration

#include <bits/stdc++.h>

// acceleration = force/ mass
double get_acceleration(double force, double mass)
{
    return force / mass;
}

// force = acceleration * mass
double get_force(double acceleration, double mass)
{
    return acceleration * mass;
}

// mass = force / acceleration
double get_mass(double acceleration, double force)
{
    return force / acceleration;
}

void fma()
{
    double force = 5.2;
    double mass = 8.1;
    double acceleration = 0.64 ; 
    

    std::cout << "Acceleration is "<<get_acceleration(force,mass)<<std::endl;
    std::cout << "Force is "<< get_force(acceleration, mass)<<std::endl;
    std::cout << "Mass is "<< get_mass(acceleration, force)<<std::endl;
}


int main(){
    fma();
    return 0;
}
