#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

struct Particle {
    float x, y;
    float weight;  // Particle weight (probability of being the true mouse position)
};

// Number of particles
const int N = 1000;
std::vector<Particle> particles;
float true_mouse_x = 0.0f, true_mouse_y = 0.0f;  // True mouse position for simulation

// Function to initialize particles
void initParticles() {
    particles.clear();
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);  // Random position range

    // Initialize particles with random positions
    for (int i = 0; i < N; ++i) {
        Particle p;
        p.x = dis(gen);  // Random x position
        p.y = dis(gen);  // Random y position
        p.weight = 1.0f / N;  // Initially uniform weight
        particles.push_back(p);
    }
}

// Function to update particles (prediction step)
void updateParticles() {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::normal_distribution<float> dis(0.0f, 0.05f);  // Process noise

    for (auto& p : particles) {
        // Move particles with some noise (simulating motion)
        p.x += dis(gen);
        p.y += dis(gen);
    }
}

// Function to update particle weights based on mouse position (measurement step)
void updateParticleWeights(float mouse_x, float mouse_y) {
    for (auto& p : particles) {
        // Calculate distance between the particle and the mouse position
        float distance = std::sqrt((p.x - mouse_x) * (p.x - mouse_x) + (p.y - mouse_y) * (p.y - mouse_y));
        // Update the weight using a Gaussian function (smaller distance = higher weight)
        p.weight = std::exp(-distance * distance / 0.02f);  // This is a simple Gaussian likelihood model
    }
}

// Function to resample particles based on their weights
void resampleParticles() {
    // Normalize weights
    float total_weight = 0.0f;
    for (const auto& p : particles) {
        total_weight += p.weight;
    }

    // Resample particles
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, total_weight);
    std::vector<Particle> resampledParticles;

    for (int i = 0; i < N; ++i) {
        float random_weight = dis(gen);
        float cumulative_weight = 0.0f;

        for (const auto& p : particles) {
            cumulative_weight += p.weight;
            if (cumulative_weight >= random_weight) {
                resampledParticles.push_back(p);
                break;
            }
        }
    }

    particles = std::move(resampledParticles);  // Replace with resampled particles
}

// OpenGL display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Render particles as small points
    glPointSize(5.0f);
    glBegin(GL_POINTS);

    for (const auto& p : particles) {
        // Particle color is based on its weight (probability)
        float color = p.weight;
        glColor3f(color, 0.0f, 1.0f - color);  // Gradually from blue to red
        glVertex2f(p.x, p.y);  // Draw particle
    }

    glEnd();

    // Swap the front and back buffers
    glutSwapBuffers();
}

// OpenGL motion callback (to track the mouse position)
void mouseMotion(int x, int y) {
    // Normalize the mouse coordinates to the range [-1, 1] for OpenGL
    true_mouse_x = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
    true_mouse_y = -(2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT) + 1.0f;

    // Update particles based on the new mouse position
    updateParticleWeights(true_mouse_x, true_mouse_y);
    resampleParticles();
    
    glutPostRedisplay();  // Redraw the window
}

// Idle function
void idle() {
    updateParticles();  // Update particles by moving them
    glutPostRedisplay();  // Trigger display refresh
}

int main(int argc, char** argv) {
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Particle Filter for Mouse Tracking");

    // Set up OpenGL view
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // 2D orthographic projection

    // Initialize particles
    initParticles();

    // Register GLUT callbacks
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMotion);  // Use passive motion to track mouse movements
    glutIdleFunc(idle);

    // Enter the GLUT main loop
    glutMainLoop();
    
    return 0;
}
