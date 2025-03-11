// #include <GL/glut.h>
// #include <iostream>
// #include <cmath>

// // Global variables for window dimensions
// int windowWidth = 800;
// int windowHeight = 600;

// float length_line = 0.5f;   // Length of the pendulum
// float radius = 0.03f;       // Radius of the circle (pendulum bob)
// float pi = 3.1415926f;
// float origin[] = {0.0f, 0.0f};

// float bob_position[] = {0.5f, 0.0f};
// float cursor_position[] = {0.0f, 0.0f};

// float angle = pi / 2;       // Starting angle (vertical)
// float angular_velocity = 0.0f;  // Initial angular velocity
// float angular_acc = 0.0f;  // Initial angular acceleration
// float gravity = -0.00010193679918451; // Gravity value

// // Variables to store cursor position
// float cursorX = 0.0f;
// float cursorY = 0.0f;


// // Function to calculate the angle with respect to the moving Y-axis (cursor)
// float calculateAngleWithRespectToMovingYAxis(float bob_position[], float cursor_position[]) {
//     // Calculate the angle of the cursor with respect to the origin
//     float cursor_angle = atan2(cursor_position[1], cursor_position[0]);

//     // Calculate the angle of the bob's line with respect to the origin
//     float bob_angle = atan2(bob_position[1], bob_position[0]);

//     // Calculate the angle between the cursor line and the bob line
//     float angle = bob_angle - cursor_angle;

//     // Normalize the angle to the range -PI to PI (optional)
//     if (angle > M_PI) {
//         angle -= 2 * M_PI;
//     } else if (angle < -M_PI) {
//         angle += 2 * M_PI;
//     }

//     return angle;
// }

// // Function to handle mouse motion (cursor movement)
// void mouseMotion(int x, int y) {
//     // Convert window coordinates to OpenGL coordinates
//     cursorX = (2.0f * x) / windowWidth - 1.0f;
//     cursorY = -(2.0f * y) / windowHeight + 1.0f;

//     // Update cursor_position array
//     cursor_position[0] = cursorX;
//     cursor_position[1] = cursorY;

//     // Calculate the angle based on the cursor position
//     angle = calculateAngleWithRespectToMovingYAxis(bob_position, cursor_position);

//     // Redraw the window
//     glutPostRedisplay();
// }

// void drawLine(float x1, float y1, float x2, float y2) {
//     glBegin(GL_LINES);
//     glVertex2f(x1, y1);
//     glVertex2f(x2, y2);
//     glEnd();
// }

// struct Circle {
//     float x, y, radius;
//     Circle(float x_val, float y_val, float r) : x(x_val), y(y_val), radius(r) {}

//     void drawFilledCircle(int num_segments) const {
//         glBegin(GL_TRIANGLE_FAN);
//         glVertex2f(x, y);
//         for (int ii = 0; ii <= num_segments; ii++) {
//             float theta = 2.0f * pi * float(ii) / float(num_segments);
//             float dx = radius * cosf(theta);
//             float dy = radius * sinf(theta);
//             glVertex2f(dx + x, dy + y);
//         }
//         glEnd();
//     }
// };

// // Update the physics of the pendulum
// std::pair<float, float> update_frame() {
//     // Calculate the force due to gravity
//     float force = gravity * sin(angle); // Simplified force
//     angular_acc = force / length_line; // Angular acceleration (τ = r * F)

//     // Update the angular velocity and angle
//     angular_velocity += angular_acc;
//     angle += angular_velocity;

//     // Simple damping (optional for realistic motion)
//     angular_velocity *= 0.99f;

//     // Calculate the new position of the pendulum bob
//     float newx = sin(angle) * length_line;
//     float newy = -cos(angle) * length_line;

//     // Update the bob position
//     bob_position[0] = newx;
//     bob_position[1] = newy;

//     return std::make_pair(newx, newy);
// }

// // Display function to render the point
// void display() {
//     // Clear the screen
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Create the circle object for the pendulum bob
//     Circle c1(0.0f, 0.0f, radius);

//     // Update the pendulum position
//     std::pair<float, float> new_position = update_frame();
//     c1.x = new_position.first;
//     c1.y = new_position.second;

//     // Draw the pendulum bob as a filled circle
//     c1.drawFilledCircle(100);  // Adjust the number of segments for smoothness

//     // Draw the line from the origin (fixed point) to the pendulum bob
//     drawLine(cursorX, cursorY, c1.x, c1.y);

//     // Draw the point at the cursor position (optional)
//     glPointSize(5.0f);
//     glBegin(GL_POINTS);
//     glVertex2f(cursorX, cursorY); // Position the point at the cursor
//     glEnd();

//     // Swap buffers to display the result
//     glutSwapBuffers();
// }

// // Function to initialize OpenGL settings
// void initOpenGL() {
//     glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set up orthogonal 2D projection
// }

// int main(int argc, char** argv) {
//     // Initialize GLUT
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffering, RGB mode
//     glutInitWindowSize(windowWidth, windowHeight); // Window size
//     glutCreateWindow("Pendulum Simulation");

//     // Initialize OpenGL
//     initOpenGL();

//     // Register the mouse motion function
//     glutMotionFunc(mouseMotion);
//     glutPassiveMotionFunc(mouseMotion); // Also track the cursor when not clicking

//     // Register the display function to redraw
//     glutIdleFunc(display);

//     // Start the main GLUT loop
//     glutMainLoop();

//     return 0;
// }



//------------------------------dispaly point on the window

// #include <GL/glut.h>
// #include <cmath>
// #include <utility>

// #define window_width  800
// #define window_height 800

// // Pendulum parameters
// float length_line = 0.5f;  // Length of the pendulum
// float radius = 0.03f;      // Radius of the point at the end
// float origin[] = {0.0f, 0.0f};  // The origin of the pendulum (fixed point)
// float pi = 3.1415926f;
// float angle = pi / 2;          // Initial angle (90 degrees)
// float angular_velocity = 0.0f; // Initial angular velocity
// float angular_acc = 0.0f;      // Angular acceleration
// float gravity = 0.00010193679918451f; // Gravity force (scaled for simulation)
// // // Variables to store cursor position
// float cursorX = 0.0f;
// float cursorY = 0.0f;

// // Function to set up the OpenGL environment
// void GL_Setup(int width, int height) {
//     glViewport(0, 0, width, height);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-1, 1, -1, 1, -1, 1);  // Set the coordinate system to 2D
//     glMatrixMode(GL_MODELVIEW);
// }

// // Function to draw a filled circle (used for the point at the end of the pendulum)
// struct Circle {
//     float x, y, radius;
//     Circle(float x_val, float y_val, float r) : x(x_val), y(y_val), radius(r) {}

//     void drawFilledCircle(int num_segments) const {
//         glBegin(GL_TRIANGLE_FAN);
//         glVertex2f(x, y);
//         for (int ii = 0; ii <= num_segments; ii++) {
//             float theta = 2.0f * pi * float(ii) / float(num_segments);
//             float dx = radius * cosf(theta);
//             float dy = radius * sinf(theta);
//             glVertex2f(dx + x, dy + y);
//         }
//         glEnd();
//     }
// };

// // Function to draw a line from (x1, y1) to (x2, y2)
// void drawLine(float x1, float y1, float x2, float y2) {
//     glBegin(GL_LINES);
//     glVertex2f(x1, y1);
//     glVertex2f(x2, y2);
//     glEnd();
// }


// // // Function to handle mouse motion (cursor movement)
// void mouseMotion(int x, int y) {
//     // Convert window coordinates to OpenGL coordinates
//     cursorX = (2.0f * x) / window_width - 1.0f;
//     cursorY = -(2.0f * y) / window_height + 1.0f;

//     // Redraw the window
//     glutPostRedisplay();
// }

// // Update the pendulum's motion by calculating the new angle and position
// std::pair<float, float> update_frame() {
//     float force = gravity * sin(angle);  // Simple gravity calculation for pendulum
//     angular_acc = force;  // Angular acceleration due to gravity
//     angular_velocity += angular_acc;  // Update angular velocity
//     angle += angular_velocity;  // Update angle
    //     glBegin(GL_POINTS);
//     glVertex2f(cursorX, cursorY); // Position the point at the cursor
//     glEnd();

//     // Swap buffers to display the result
//     glutSwapBuffers();
// }

// // Function to initialize OpenGL settings
// void initOpenGL() {
//     glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set up orthogonal 2D projection
// }

// int main(int argc, char** argv) {
//     // Initialize GLUT
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffering, RGB mode
//     glutInitWindowSize(windowWidth, windowHeight); // Window size
//     glutCreateWindow("Pendulum Simulation");

//     // Initialize OpenGL
//     initOpenGL();

//     // Register the mouse motion function
//     glutMotionFunc(mouseMotion);
//     glutPassiveMotionFunc(mouseMotion); // Also track the cursor when not clicking

//     // Register the display function to redraw
//     glutIdleFunc(display);

//     // Start the main GLUT loop
//     glutMainLoop();

//     return 0;
// }



//------------------------------dispaly point on the window

// #include <GL/glut.h>
// #include <cmath>
// #include <utility>

// #define window_width  800
// #define window_height 800

// // Pendulum parameters
// float length_line = 0.5f;  // Length of the pendulum
// float radius = 0.03f;      // Radius of the point at the end
// float origin[] = {0.0f, 0.0f};  // The origin of the pendulum (fixed point)
// float pi = 3.1415926f;
// float angle = pi / 2;          // Initial angle (90 degrees)
// float angular_velocity = 0.0f; // Initial angular velocity
// float angular_acc = 0.0f;      // Angular acceleration
// float gravity = 0.00010193679918451f; // Gravity force (scaled for simulation)
// // // Variables to store cursor position
// float cursorX = 0.0f;
// float cursorY = 0.0f;

// // Function to set up the OpenGL environment
// void GL_Setup(int width, int height) {
//     glViewport(0, 0, width, height);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-1, 1, -1, 1, -1, 1);  // Set the coordinate system to 2D
//     glMatrixMode(GL_MODELVIEW);
// }

// // Function to draw a filled circle (used for the point at the end of the pendulum)
// struct Circle {
//     float x, y, radius;
//     Circle(float x_val, float y_val, float r) : x(x_val), y(y_val), radius(r) {}

//     void drawFilledCircle(int num_segments) const {
//         glBegin(GL_TRIANGLE_FAN);
//         glVertex2f(x, y);
//         for (int ii = 0; ii <= num_segments; ii++) {
//             float theta = 2.0f * pi * float(ii) / float(num_segments);
//             float dx = radius * cosf(theta);
//             float dy = radius * sinf(theta);
//             glVertex2f(dx + x, dy + y);
//         }
//         glEnd();
//     }
// };

// // Function to draw a line from (x1, y1) to (x2, y2)
// void drawLine(float x1, float y1, float x2, float y2) {
//     glBegin(GL_LINES);
//     glVertex2f(x1, y1);
//     glVertex2f(x2, y2);
//     glEnd();
// }


// // // Function to handle mouse motion (cursor movement)
// void mouseMotion(int x, int y) {
//     // Convert window coordinates to OpenGL coordinates
//     cursorX = (2.0f * x) / window_width - 1.0f;
//     cursorY = -(2.0f * y) / window_height + 1.0f;

//     // Redraw the window
//     glutPostRedisplay();
// }

// // Update the pendulum's motion by calculating the new angle and position
// std::pair<float, float> update_frame() {
//     float force = gravity * sin(angle);  // Simple gravity calculation for pendulum
//     angular_acc = force;  // Angular acceleration due to gravity
//     angular_velocity += angular_acc;  // Update angular velocity
//     angle += angular_velocity;  // Update angle
    
//     // Calculate the new x, y position of the point based on the angle
//     float newx = sin(angle) * length_line;
//     float newy = -cos(angle) * length_line;  // Negate y for proper downward direction
//     return std::make_pair(newx, newy);
// }

// // The main loop function that is called repeatedly by GLUT
// void main_loop_function() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Set color for the pendulum point (red)
//     glColor3f(1.0f, 0.0f, 0.0f);

//     // Create circles at the positions of the pendulum ends
//     Circle c1(0.0f, 0.0f, radius);  // Circle at the origin (fixed point)
//     Circle c2(0.0f, 0.0f, radius);  // Circle at the pendulum bob (moving point)

//     // Get the new position of the pendulum bob using physics calculations
//     std::pair<float, float> new_position = update_frame();
//     c2.x = new_position.first;
//     c2.y = new_position.second;

//     // Set point size
//     glPointSize(1.0f);

//     // Draw the point at the cursor position
//     glBegin(GL_POINTS);
//     glVertex2f(cursorX, cursorY); // Position the point at the cursor
//     glEnd();

//     // Draw the pendulum bob (moving point)
//     c2.drawFilledCircle(1000);

//     // Set color for the pendulum line (green)
//     glColor3f(0.0f, 1.0f, 0.0f);

//     // Draw the pendulum line
//     drawLine(cursorX, cursorY, c1.x, c1.y);  // From origin to bob

//     // Swap buffers to display the result
//     glutSwapBuffers();
// }

// int main(int argc, char** argv) {
//     // Initialize GLUT
//     glutInit(&argc, argv);
//     glutInitWindowSize(window_width, window_height);
//     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Double buffering for smooth animation
//     glutCreateWindow("Pendulum Simulation");

//     // Register the main loop function
//     glutIdleFunc(main_loop_function);
    
//     // Set up OpenGL
//     GL_Setup(window_width, window_height);

//     // Start the GLUT main loop
//     glutMainLoop();

//     return 0;
// }


// #include <GL/glut.h>
// #include <cmath>
// #include <utility>

// #define window_width  800
// #define window_height 800
// float length_line = 0.5f;
// float radius = 0.03f;
// float origin[] = {0.0f, 0.0f};
// float pi = 3.1415926f;
// float angle = 4;
// float angular_velocity = 0.00;
// float angular_acc  = 0.00;
// float gravity  = 0.00010193679918451;
// float bob_position [] = {0.0f,0.0f};
// // float air_drag = 0.99999;
// void GL_Setup(int width, int height) {
//     glViewport(0, 0, width, height);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-1, 1, -1, 1, -1, 1);
//     glMatrixMode(GL_MODELVIEW);
// }

// struct Circle {
//     float x, y, radius;
//     Circle(float x_val, float y_val, float r) : x(x_val), y(y_val), radius(r) {}

//     void drawFilledCircle(int num_segments) const {
//         glBegin(GL_TRIANGLE_FAN);
//         glVertex2f(x, y);
//         for (int ii = 0; ii <= num_segments; ii++) {
//             float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
//             float dx = radius * cosf(theta);
//             float dy = radius * sinf(theta);
//             glVertex2f(dx + x, dy + y);
//         }
//         glEnd();
//     }
// };

// void drawLine(float x1, float y1, float x2, float y2) {
//     glBegin(GL_LINES);
//     glVertex2f(x1, y1);
//     glVertex2f(x2, y2);
//     glEnd();
// }

// float bob_position []  update_frame() {
//     float florce = gravity*sin(angle);
//     angular_acc = florce;
//     angular_velocity += angular_acc;
//     // angular_velocity -= air_drag;
//     angle += angular_velocity;
//     float newx = sin(angle) * length_line;
//     float newy = cos(angle) * length_line;
//     // return std::make_pair(newx, newy);
//     return bob_position;
// }

// void main_loop_function() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     glColor3f(1.0f, 0.0f, 0.0f);

//     Circle c1(0.0f, 0.0f, radius);

//     bob_position []  new_position = update_frame();
//     c1.x = bob_position[0];
//     c1.y = bob_position[0];



//     c1.drawFilledCircle(1000);

//     glColor3f(0.0f, 1.0f, 0.0f);

//     drawLine(origin[0], origin[1], c1.x, c1.y);

//     glutSwapBuffers();
// }

// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitWindowSize(window_width, window_height);
//     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//     glutCreateWindow("Filled Circle and Line Rendering");
//     glutIdleFunc(main_loop_function);
//     GL_Setup(window_width, window_height);
//     glutMainLoop();
// }

//     // Calculate the new x, y position of the point based on the angle
//     float newx = sin(angle) * length_line;
//     float newy = -cos(angle) * length_line;  // Negate y for proper downward direction
//     return std::make_pair(newx, newy);
// }

// // The main loop function that is called repeatedly by GLUT
// void main_loop_function() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Set color for the pendulum point (red)
//     glColor3f(1.0f, 0.0f, 0.0f);

//     // Create circles at the positions of the pendulum ends
//     Circle c1(0.0f, 0.0f, radius);  // Circle at the origin (fixed point)
//     Circle c2(0.0f, 0.0f, radius);  // Circle at the pendulum bob (moving point)

//     // Get the new position of the pendulum bob using physics calculations
//     std::pair<float, float> new_position = update_frame();
//     c2.x = new_position.first;
//     c2.y = new_position.second;

//     // Set point size
//     glPointSize(1.0f);

//     // Draw the point at the cursor position
//     glBegin(GL_POINTS);
//     glVertex2f(cursorX, cursorY); // Position the point at the cursor
//     glEnd();

//     // Draw the pendulum bob (moving point)
//     c2.drawFilledCircle(1000);

//     // Set color for the pendulum line (green)
//     glColor3f(0.0f, 1.0f, 0.0f);

//     // Draw the pendulum line
//     drawLine(cursorX, cursorY, c1.x, c1.y);  // From origin to bob

//     // Swap buffers to display the result
//     glutSwapBuffers();
// }

// int main(int argc, char** argv) {
//     // Initialize GLUT
//     glutInit(&argc, argv);
//     glutInitWindowSize(window_width, window_height);
//     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Double buffering for smooth animation
//     glutCreateWindow("Pendulum Simulation");

//     // Register the main loop function
//     glutIdleFunc(main_loop_function);
    
//     // Set up OpenGL
//     GL_Setup(window_width, window_height);

//     // Start the GLUT main loop
//     glutMainLoop();

//     return 0;
// }


// #include <GL/glut.h>
// #include <cmath>
// #include <utility>

// #define window_width  800
// #define window_height 800
// float length_line = 0.5f;
// float radius = 0.03f;
// float origin[] = {0.0f, 0.0f};
// float pi = 3.1415926f;
// float angle = 3.14;
// float angular_velocity = 0.00;
// float angular_acc  = 0.00;
// float gravity  = 0;//0.00010193679918451;
// void GL_Setup(int width, int height) {
//     glViewport(0, 0, width, height);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-1, 1, -1, 1, -1, 1);
//     glMatrixMode(GL_MODELVIEW);
// }

// struct Circle {
//     float x, y, radius;
//     float bob_position [] = {0.0f, 0.0f}; 
//     Circle(float x_val, float y_val, float r) : x(x_val), y(y_val), radius(r) {}

//     void drawFilledCircle(int num_segments) const {
//         glBegin(GL_TRIANGLE_FAN);
//         glVertex2f(x, y);
//         for (int ii = 0; ii <= num_segments; ii++) {
//             float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
//             float dx = radius * cosf(theta);
//             float dy = radius * sinf(theta);
//             glVertex2f(dx + x, dy + y);
//         }
//         glEnd();
//     }

//     void update_bob_position() {
//     float force = gravity * sin(angle);
//     angular_acc = force;
//     angular_velocity += angular_acc;
//     angle += angular_velocity;

//     bob_position[0] = sin(angle) * length_line;
//     bob_position[1] = cos(angle) * length_line; 
    
//     }
// };

// void drawLine(float x1, float y1, float x2, float y2) {
//     glBegin(GL_LINES);
//     glVertex2f(x1, y1);
//     glVertex2f(x2, y2);
//     glEnd();
// }

// void update_bob_position() {
//     float force = gravity * sin(angle);
//     angular_acc = force;
//     angular_velocity += angular_acc;
//     angle += angular_velocity;

//    bob_position[0] = sin(angle) * length_line;
//     bob_position[1] = cos(angle) * length_line; 
//     // // Update bob's position based on the angle
//     // bob_position[0] = sin(angle) * length_line;
//     // bob_position[1] = -cos(angle) * length_line;  // Negative y to make the pendulum move correctly
// }

// void main_loop_function() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     glColor3f(1.0f, 0.0f, 0.0f);

//     Circle c1(0.0f, 0.0f, radius);

//     c1.update_frame();  // Update bob's position
//     c1.x = bob_position[0];
//     c1.y = bob_position[1];  // Corrected to use bob_position[1] for the y-coordinate

//     c1.drawFilledCircle(1000);

// Circle c2(0.0f, 0.0f, radius);

//     c2.update_frame();  // Update bob's position
//     c2.x = bob_position[0];
//     c2.y = bob_position[1];  // Corrected to use bob_position[1] for the y-coordinate
//     c2.drawFilledCircle(1000);
//     glColor3f(0.0f, 1.0f, 0.0f);

//     drawLine(origin[0], origin[1], c1.x, c1.y);  // Draw the line from the origin to the bob

//     glutSwapBuffers();
// }

// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitWindowSize(window_width, window_height);
//     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//     glutCreateWindow("Pendulum Simulation");
//     glutIdleFunc(main_loop_function);
//     GL_Setup(window_width, window_height);
//     glutMainLoop();
// }


#include <GL/glut.h>
#include <cmath>

#define window_width  800
#define window_height 800

float length_line1 = 0.5f; // Length of the first pendulum
float length_line2 = 0.2f; // Length of the second pendulum
float length_line3 = 0.1f;
float radius = 0.03f;      // Radius of the bob
float pi = 3.1415926f;

float angle1 = 1.14f;           // Angle of the first pendulum (in radians)
float angle2 = 0.14f;           // Angle of the second pendulum (in radians)
float angle3 = 3.14f;  
float angular_velocity1 = 0.0f; // Angular velocity of the first pendulum
float angular_velocity2 = 0.0f; // Angular velocity of the second pendulum

float angular_acc1 = 0.0f;      // Angular acceleration of the first pendulum
float angular_acc2 = 0.0f;      // Angular acceleration of the second pendulum

float gravity = -0.00010193679918451f;  // Gravitational constant

float origin[] = {0.0f, 0.0f}; // Origin of the first pendulum

void GL_Setup(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

struct Circle {
    float x, y, radius;
    Circle(float x_val, float y_val, float r) : x(x_val), y(y_val), radius(r) {}

    void drawFilledCircle(int num_segments) const {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int ii = 0; ii <= num_segments; ii++) {
            float theta = 2.0f * pi * float(ii) / float(num_segments);
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(dx + x, dy + y);
        }
        glEnd();
    }
};

// inverse Pendulam implemnt

// // Update the position of both pendulums 
// void update_frame() {
//     // Equations of motion for the double pendulum
//     float num1 = -gravity * (2.0f * cos(angle1 - angle2) * sin(angle1) + sin(angle1 - angle2) * cos(angle2));
//     float den1 = (length_line1 * (2.0f - cos(angle1 - angle2) * cos(angle1 - angle2)));

//     float num2 = gravity * (2.0f * sin(angle2) + sin(angle1 - angle2) * cos(angle1 - angle2));
//     float den2 = length_line2 * (2.0f - cos(angle1 - angle2) * cos(angle1 - angle2));

//     angular_acc1 = num1 / den1;
//     angular_acc2 = num2 / den2;

//     // Update angular velocities
//     angular_velocity1 += angular_acc1;
//     angular_velocity2 += angular_acc2;

//     // Update angles
//     angle1 += angular_velocity1;
//     angle2 += angular_velocity2;
// }


// Function to update the positions of both pendulums (for normal pendulum with 2 bobs)
void update_frame() {
    // For the first pendulum, use the simple equation of motion for a pendulum
    angular_acc1 = (-gravity / length_line1) * sin(angle1);
    angular_velocity1 += angular_acc1;
    angle1 += angular_velocity1;
    // angular_velocity1 = angular_velocity1 * 0.009f;


    // For the second pendulum, it depends on the first bob's motion
    angular_acc2 = (-gravity / length_line2) * sin(angle2);
    angular_velocity2 += angular_acc2;
    angle2 += angular_velocity2;
    // angular_velocity2 = angular_velocity2 * 0.009f;
}

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void main_loop_function() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Update pendulum positions
    update_frame();

    // Position of the first bob
    float x1 = sin(angle1) * length_line1;
    float y1 = cos(angle1) * length_line1;

    // Position of the second bob
    float x2 = x1 + sin(angle2) * length_line2;
    float y2 = y1 + cos(angle2) * length_line2;


    float x3 = x2 + sin(angle3) * length_line3;
    float y3 = y2 + cos(angle3) * length_line3;

    // Create and draw the first bob (red)
    Circle c1(x1, y1, radius);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the first bob
    c1.drawFilledCircle(1000);

    // Create and draw the second bob (blue)
    Circle c2(x2, y2, radius);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for the second bob
    c2.drawFilledCircle(1000);


    // Create and draw the second bob (blue)
    Circle c3(x3, y3, radius);
    glColor3f(0.0f, 1.0f, 1.0f); // Blue color for the second bob
    c3.drawFilledCircle(1000);



    // Draw the lines connecting the bobs to the origin and to each other
    glColor3f(0.0f, 1.0f, 0.0f); // Green for the lines
    drawLine(origin[0], origin[1], x1, y1);  // Line from origin to the first bob
    drawLine(x1, y1, x2, y2);  // Line from the first bob to the second bob
     drawLine(x3, y3, x2, y2);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Double Pendulum Simulation");
    glutIdleFunc(main_loop_function);
    GL_Setup(window_width, window_height);
    glutMainLoop();
}
