#include <GL/glut.h>
#include <cmath>
#include <array>
#include <vector>
#include <iostream>
#include <unistd.h>

// Global variables for mouse interaction
float angleX = 0.0f;         // Rotation around the X-axis
float angleY = 0.0f;         // Rotation around the Y-axis
int prevX, prevY;            // Previous mouse coordinates
bool isMousePressed = false; // Flag to track whether the mouse button is pressed
float size_node = 0.035f;
std::array<float, 3> newRgb = {0.0f, 1.0f, 0.0f};
int node_limit = 100;
// std::vector<Sphere> tree;

// Sphere nearestNeighbor(const Sphere& sample) {
//         Sphere nearest = tree[0];
//         double min_distance = nearest.distance(sample);

//         for (const auto& node : tree) {
//             double dist = node.distance(sample);
//             if (dist < min_distance) {
//                 nearest = node;
//                 min_distance = dist;
//             }
//         }
//         return nearest;
//     }

// Define a structure to represent a sphere
struct Sphere
{
    float x, y, z;
    float radius;
    std::array<float, 3> rgb;

    Sphere() : x(0.0f), y(0.0f), z(0.0f), radius(0.0f), rgb{1.0f, 1.0f, 1.0f} {}
    Sphere(float posX, float posY, float posZ, float radius, std::array<float, 3> color)
        : x(posX), y(posY), z(posZ), radius(radius), rgb(color) {}

    void draw()
    {
        glPushMatrix();
        glTranslatef(x, y, z);             // Move sphere to its position
        glColor3f(rgb[0], rgb[1], rgb[2]); // Set the color for the sphere
        glutSolidSphere(radius, 20, 20);   // Draw the filled sphere
        glPopMatrix();
    }
};

// Define a structure to represent a line
struct Line
{
    Sphere *sphere1;
    Sphere *sphere2;
    std::array<float, 3> color;

    Line(Sphere *s1, Sphere *s2, std::array<float, 3> lineColor)
        : sphere1(s1), sphere2(s2), color(lineColor) {}

    void draw()
    {
        glColor3f(color[0], color[1], color[2]); // Set the color for the line
        glBegin(GL_LINES);
        glVertex3f(sphere1->x, sphere1->y, sphere1->z); // Start at sphere1
        glVertex3f(sphere2->x, sphere2->y, sphere2->z); // End at sphere2
        glEnd();
    }
};

// Define a structure to represent a node
struct Node
{
    Sphere curr_node;                // The current node (sphere)
    Sphere parent_node;              // The parent node (sphere)
    std::vector<Sphere> child_nodes; // A vector of child nodes (spheres)

    // Constructor to initialize the node with a sphere
    Node(Sphere curr_node) : curr_node(curr_node) {}

    // Function to connect the node to its parent and child nodes
    void connect_node()
    {
        // Connect the line between curr_node and parent_node (if parent_node exists)
        if (parent_node.radius > 0.0f) // Assuming non-null parent node has a positive radius
        {
            glColor3f(1.0f, 1.0f, 0.0f); // Set line color to yellow
            glBegin(GL_LINES);
            glVertex3f(curr_node.x, curr_node.y, curr_node.z);       // Start at curr_node
            glVertex3f(parent_node.x, parent_node.y, parent_node.z); // End at parent_node
            glEnd();
        }

        // Loop through child nodes and connect a line to each one (if child nodes exist)
        for (const Sphere &child : child_nodes)
        {
            glColor3f(0.0f, 1.0f, 0.0f); // Set line color to green
            glBegin(GL_LINES);
            glVertex3f(curr_node.x, curr_node.y, curr_node.z); // Start at curr_node
            glVertex3f(child.x, child.y, child.z);             // End at child node
            glEnd();
        }
    }

    double distance(const Sphere &otherSphere) const
    {
        // Sphere movedSphere = sphere1.moveTowards(sphere2, 0.1);
        return sqrt(pow(curr_node.x - otherSphere.x, 2) +
                    pow(curr_node.y - otherSphere.y, 2) +
                    pow(curr_node.z - otherSphere.z, 2));
    }

    Sphere moveTowards(const Sphere &target, double step_size)
    {
        double dist = distance(target); // Calculate the distance to the target sphere

        // Avoid division by zero if the spheres are already at the same position
        if (dist == 0.0f)
        {
            return curr_node; // No movement needed if the spheres are already at the same position
        }

        double ratio = step_size / dist;                              // Determine the ratio to move the correct step size
        double xNew = curr_node.x + (target.x - curr_node.x) * ratio; // Calculate the new x position
        double yNew = curr_node.y + (target.y - curr_node.y) * ratio; // Calculate the new y position
        double zNew = curr_node.z + (target.z - curr_node.z) * ratio; // Calculate the new z position
        // Create a new sphere with the new position and return it
        Sphere newSphere(xNew, yNew, zNew, size_node, newRgb);
        return newSphere;
    }
};
std::vector<Node> tree;
Node nearestNeighbor(const Sphere &sample)
{
    Node nearest = tree[0];
    double min_distance = nearest.distance(sample);

    for (const auto &node : tree)
    {
        double dist = node.distance(sample);
        if (dist < min_distance)
        {
            nearest = node;
            min_distance = dist;
        }
    }
    return nearest;
}

float randomFloatInRange(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));
}

Node randomSampleNode()
{
    // Generate random coordinates between -1 and 1 for x, y, and z
    float xNew = randomFloatInRange(-2.0f, 2.0f);
    float yNew = randomFloatInRange(-2.0f, 2.0f);
    float zNew = randomFloatInRange(-2.0f, 2.0f);

    // Random RGB values between 0.0 and 1.0 for the sphere's color
    std::array<float, 3> newRgb = {randomFloatInRange(0.0f, 1.0f), randomFloatInRange(0.0f, 1.0f), randomFloatInRange(0.0f, 1.0f)};

    // Create a sphere with the generated values
    Sphere randomSampleSphere(xNew, yNew, zNew, size_node, newRgb);

    // Create a Node using the random sphere
    Node randomSampleNode(randomSampleSphere);

    return randomSampleNode;
}

// Create example spheres and nodes
Sphere sphere1(-1.0f, -1.0f, -1.0f, 1.0f, {1.0f, 0.0f, 0.0f}); // Red sphere
Sphere sphere2(1.0f, 1.0f, 1.0f, 1.0f, {0.0f, 0.0f, 1.0f});    // Blue sphere
Sphere sphere3(1.0f, -1.0f, 1.0f, 0.5f, {0.0f, 1.0f, 0.0f});   // Green sphere
Sphere sphere4(-1.0f, 1.0f, 1.0f, 0.5f, {1.0f, 1.0f, 0.0f});   // Yellow sphere

// Create nodes (instantiating nodes after creating spheres)
Sphere sphere1(-1.0f, -1.0f, -1.0f, 1.0f, {1.0f, 0.0f, 0.0f});
Node node1(sphere1); // node1 corresponds to sphere1
Node node2(sphere2); // node2 corresponds to sphere2
Node node3(sphere3); // node3 corresponds to sphere3
Node node4(sphere4); // node4 corresponds to sphere4

// Set up parent-child relationships AFTER node creation
// node2.parent_node = sphere1; // node2's parent is node1
// node2.child_nodes.push_back(sphere3); // node2's child is node3
// node2.child_nodes.push_back(sphere4); // node2's child is node4

// Function to initialize OpenGL settings
void initOpenGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glEnable(GL_DEPTH_TEST);          // Enable depth testing for proper 3D rendering
}

// float angleX = 0.0f;         // Rotation around the X-axis
// float angleY = 0.0f;         // Rotation around the Y-axis
// int prevX, prevY;            // Previous mouse coordinates
// bool isMousePressed = false; // Flag to track whether the mouse button is pressed
float lastMouseMoveTime = 0.0f; // Track last mouse move time
float autoRotateSpeed = 0.5f;  // Speed of automatic rotation

// Time interval for detecting inactivity (in seconds)
float mouseInactivityThreshold = 1.0f; 

// Function to update the automatic rotation based on time
void updateAutoRotation(float deltaTime) {
    // If there's no recent mouse movement, rotate the scene automatically around the Y-axis
    if (glutGet(GLUT_ELAPSED_TIME) - lastMouseMoveTime > mouseInactivityThreshold * 1000) {
        angleY += autoRotateSpeed * deltaTime;
    }
}

// Mouse motion handler (to update angles based on mouse movement)
// void mouseMotion(int x, int y)
// {
//     if (isMousePressed)
//     {
//         // Calculate the change in mouse position
//         int deltaX = x - prevX;
//         int deltaY = y - prevY;

//         // Update the camera angles based on mouse movement
//         angleX += deltaY * 0.1f; // Rotate around X-axis
//         angleY += deltaX * 0.1f; // Rotate around Y-axis

//         // Update the previous mouse position
//         prevX = x;
//         prevY = y;

//         // Reset last mouse move time
//         lastMouseMoveTime = glutGet(GLUT_ELAPSED_TIME);

//         glutPostRedisplay(); // Redraw the scene with the updated rotation
//     }
// }

// // Mouse click handler (to start/stop rotation)
// void mouseClick(int button, int state, int x, int y)
// {
//     if (button == GLUT_LEFT_BUTTON)
//     {
//         if (state == GLUT_DOWN)
//         {
//             isMousePressed = true;
//             prevX = x;
//             prevY = y;
//         }
//         else if (state == GLUT_UP)
//         {
//             isMousePressed = false;
//         }
//     }
// }
// Function to move the space (rotate automatically when no mouse event)
void move_space(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer
    glLoadIdentity();                                   // Reset the transformation matrix
    // Apply rotation based on the mouse movement or auto-rotation
    glTranslatef(0.0f, 0.0f, -5.0f);     // Move the scene back to view it
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

    // Update auto-rotation if no mouse events occurred
    updateAutoRotation(0.1f);  // Call with a small delta time (e.g., 0.1 seconds)
}

// Function to render the 3D scene

// int number_of_ilteration = 10;
// void display_loop()
// {
//     move_space();

//     while(number_of_ilteration--){
//         // make the random node
//     }
//     // Draw the spheres themselves
//     node1.curr_node.draw();
//     node2.curr_node.draw();
//     node3.curr_node.draw();
//     node4.curr_node.draw();

//     // Connect nodes by drawing lines
//     node1.connect_node();  // Connect node1 to its parent/children
//     node2.connect_node();  // Connect node2 to its parent/children
//     node3.connect_node();  // Connect node3 to its parent/children
//     node4.connect_node();  // Connect node4 to its parent/children

//     node2.parent_node = sphere1;
//     node2.child_nodes.push_back(sphere3); // node2's child is node3
//     node2.child_nodes.push_back(sphere4); // node2's child is node4

//     glutSwapBuffers(); // Swap buffers to display the rendered scene
// }

int number_of_iterations = 10; // Number of iterations to create random nodes

void display_loop()
{
    move_space();

    // Loop to create random nodes and add them to the tree

    // Create a random node and add it to the tree
    // Node randomNode = randomSampleNode();
    // tree.push_back(randomNode);

    // // Draw the existing spheres
    // node1.curr_node.draw();
    // node2.curr_node.draw();
    // node3.curr_node.draw();
    // node4.curr_node.draw();

    // // Connect nodes by drawing lines
    // node1.connect_node();  // Connect node1 to its parent/children
    // node2.connect_node();  // Connect node2 to its parent/children
    // node3.connect_node();  // Connect node3 to its parent/children
    // node4.connect_node();  // Connect node4 to its parent/children

    // tree.push_back(node1);
    // std::cout<<tree.size();
    // After adding random nodes, draw them and connect them to their neighbors
    // for (Node& randomNode : tree)
    // {
    //     randomNode.curr_node.draw();
    //     randomNode.connect_node();
    // }
    glutSwapBuffers(); // Swap buffers to display the rendered scene
}

// Function to handle window resizing and set the perspective
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);                                       // Set the viewport to cover the new window dimensions
    glMatrixMode(GL_PROJECTION);                                  // Switch to the projection matrix
    glLoadIdentity();                                             // Reset the projection matrix
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 200.0f); // Set up the perspective
    glMatrixMode(GL_MODELVIEW);                                   // Switch back to the model-view matrix
}

// Function to set up a basic lighting setup (optional, for better 3D effects)
void setupLighting()
{
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light source 0

    // Set the light's position
    GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f}; // Position in homogeneous coordinates
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Set light color
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // White diffuse light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_COLOR_MATERIAL); // Enable color material to affect lighting
}

// Mouse motion handler
void mouseMotion(int x, int y)
{
    if (isMousePressed)
    {
        // Calculate the change in mouse position
        int deltaX = x - prevX;
        int deltaY = y - prevY;

        // Update the camera angles based on mouse movement
        angleX += deltaY * 0.1f; // Rotate around X-axis
        angleY += deltaX * 0.1f; // Rotate around Y-axis

        // Update the previous mouse position
        prevX = x;
        prevY = y;

        glutPostRedisplay(); // Redraw the scene with the updated rotation
    }
}

// Mouse click handler (to start/stop rotation)
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isMousePressed = true;
            prevX = x;
            prevY = y;
        }
        else if (state == GLUT_UP)
        {
            isMousePressed = false;
        }
    }
}
int node_count = 0;
int max_nodes = 100;      // Define the max number of nodes to add
int node_interval = 1000; // Time interval between each new node (in milliseconds)


void my_idle_function()
{
     move_space();
     std::cout << node_count << std::endl;
    // if (node_count < max_nodes)
    // {
        Node randomNode = randomSampleNode();
        tree.push_back(randomNode);

        node_count++;
    // }

    for (Node &randomNode : tree)
    {
        // std::cout << randomNode.curr_node.x << std::endl;
        randomNode.curr_node.draw();
        randomNode.connect_node();
    }

    glutSwapBuffers();
    // sleep(1);
    // Call this function again after the specified interval
    // glutTimerFunc(node_interval, my_idle_function, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(2000, 1000);
    glutCreateWindow("OpenGL Camera Rotation with Mouse");

    initOpenGL();    // Initialize OpenGL settings
    setupLighting(); // Set up basic lighting

    // Register the GLUT functions
    glutDisplayFunc(display_loop); // Register the display function
    glutReshapeFunc(reshape);      // Register the reshape function
    glutMotionFunc(mouseMotion);   // Register the mouse motion function
    glutMouseFunc(mouseClick);     // Register the mouse click function

    glutIdleFunc(my_idle_function);

    glutMainLoop(); // Enter the GLUT event loop
    return 0;
}
