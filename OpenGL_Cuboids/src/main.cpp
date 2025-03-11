#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

// Cuboid class definition (same as before)
class Cuboid {
public:
    float scale;
    float posX, posY, posZ;
    float rColor, gColor, bColor;

    Cuboid() {
        scale = randomFloat(0.1f, 1.0f);  // Random scale
        posX = randomFloat(-5.0f, 5.0f);  // Random X position
        posY = randomFloat(-5.0f, 5.0f);  // Random Y position
        posZ = randomFloat(-5.0f, 50.0f); // Random Z position
        rColor = randomFloat(0.25f, 1.0f);  // Random red color component
        gColor = randomFloat(0.25f, 1.0f);  // Random green color component
        bColor = randomFloat(0.25f, 1.0f);  // Random blue color component
    }

    void draw() const {
        glColor3f(rColor, gColor, bColor);

        glBegin(GL_QUADS);

        // Front face
        glVertex3f(-1.0f * scale, -1.0f * scale, 1.0f * scale);
        glVertex3f( 1.0f * scale, -1.0f * scale, 1.0f * scale);
        glVertex3f( 1.0f * scale,  1.0f * scale, 1.0f * scale);
        glVertex3f(-1.0f * scale,  1.0f * scale, 1.0f * scale);

        // Back face
        glVertex3f(-1.0f * scale, -1.0f * scale, -1.0f * scale);
        glVertex3f(-1.0f * scale,  1.0f * scale, -1.0f * scale);
        glVertex3f( 1.0f * scale,  1.0f * scale, -1.0f * scale);
        glVertex3f( 1.0f * scale, -1.0f * scale, -1.0f * scale);

        // Left face
        glVertex3f(-1.0f * scale, -1.0f * scale, -1.0f * scale);
        glVertex3f(-1.0f * scale, -1.0f * scale,  1.0f * scale);
        glVertex3f(-1.0f * scale,  1.0f * scale,  1.0f * scale);
        glVertex3f(-1.0f * scale,  1.0f * scale, -1.0f * scale);

        // Right face
        glVertex3f( 1.0f * scale, -1.0f * scale, -1.0f * scale);
        glVertex3f( 1.0f * scale,  1.0f * scale, -1.0f * scale);
        glVertex3f( 1.0f * scale,  1.0f * scale,  1.0f * scale);
        glVertex3f( 1.0f * scale, -1.0f * scale,  1.0f * scale);

        // Top face
        glVertex3f(-1.0f * scale, 1.0f * scale, -1.0f * scale);
        glVertex3f(-1.0f * scale, 1.0f * scale,  1.0f * scale);
        glVertex3f( 1.0f * scale, 1.0f * scale,  1.0f * scale);
        glVertex3f( 1.0f * scale, 1.0f * scale, -1.0f * scale);

        // Bottom face
        glVertex3f(-1.0f * scale, -1.0f * scale, -1.0f * scale);
        glVertex3f( 1.0f * scale, -1.0f * scale, -1.0f * scale);
        glVertex3f( 1.0f * scale, -1.0f * scale,  1.0f * scale);
        glVertex3f(-1.0f * scale, -1.0f * scale,  1.0f * scale);

        glEnd();
    }

    void translate() const {
        glTranslatef(posX, posY, posZ);
    }

    static float randomFloat(float min, float max) {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    // Check if the cuboid collides with a point (like the ball)
    bool isColliding(float ballPosX, float ballPosY, float ballPosZ, float ballRadius) const {
        return (ballPosX + ballRadius > posX - scale &&
                ballPosX - ballRadius < posX + scale &&
                ballPosY + ballRadius > posY - scale &&
                ballPosY - ballRadius < posY + scale &&
                ballPosZ + ballRadius > posZ - scale &&
                ballPosZ - ballRadius < posZ + scale);
    }
};

std::vector<Cuboid> cuboids;
float rotateX = 0.0f;
float rotateY = 0.0f;

int lastX = 0, lastY = 0;
bool isDragging = false;

// Ball's properties
float ballPosX = 0.0f, ballPosY = 0.0f, ballPosZ = 0.0f;
float ballRadius = 0.5f;
float ballSpeed = 0.1f;
float ballDirectionX = 0.0f, ballDirectionY = 0.0f, ballDirectionZ = 0.0f;
bool ballMoving = false;  // Flag to check if the ball is moving
bool ballCollided = false;  // Flag to check if the ball collided with a cuboid

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 50; ++i) {
        cuboids.push_back(Cuboid());
    }
}

void updateBallPosition() {
    if (ballMoving && !ballCollided) {
        ballPosX += ballDirectionX * ballSpeed;
        ballPosY += ballDirectionY * ballSpeed;
        ballPosZ += ballDirectionZ * ballSpeed;

        // Check for collisions with cuboids
        for (const auto& cuboid : cuboids) {
            if (cuboid.isColliding(ballPosX, ballPosY, ballPosZ, ballRadius)) {
                ballCollided = true;
                
                // Stop movement in the direction of the collision
                if (ballPosX + ballRadius > cuboid.posX - cuboid.scale && ballPosX - ballRadius < cuboid.posX + cuboid.scale) {
                    ballDirectionX = 0.0f;
                }
                if (ballPosY + ballRadius > cuboid.posY - cuboid.scale && ballPosY - ballRadius < cuboid.posY + cuboid.scale) {
                    ballDirectionY = 0.0f;
                }
                if (ballPosZ + ballRadius > cuboid.posZ - cuboid.scale && ballPosZ - ballRadius < cuboid.posZ + cuboid.scale) {
                    ballDirectionZ = 0.0f;
                }
                break;
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Apply global rotation
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);

    // Draw cuboids
    for (const auto& cuboid : cuboids) {
        glPushMatrix();
        cuboid.translate();
        cuboid.draw();
        glPopMatrix();
    }

    // Draw the ball
    if (!ballCollided) {
        glColor3f(0.0f, 1.0f, 0.0f);  // Green ball
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);  // Red ball
    }

    glPushMatrix();
    glTranslatef(ballPosX, ballPosY, ballPosZ);
    glutSolidSphere(ballRadius, 20, 20);
    glPopMatrix();

    // Update ball position after drawing
    updateBallPosition();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void motion(int x, int y) {
    if (isDragging) {
        int dx = x - lastX;
        int dy = y - lastY;

        rotateX += dy * 0.5f;
        rotateY += dx * 0.5f;

        lastX = x;
        lastY = y;

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastX = x;
            lastY = y;
        } else {
            isDragging = false;
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') {
        ballDirectionY = 1.0f;
        ballMoving = true;
    } else if (key == 's') {
        ballDirectionY = -1.0f;
        ballMoving = true;
    } else if (key == 'a') {
        ballDirectionX = -1.0f;
        ballMoving = true;
    } else if (key == 'd') {
        ballDirectionX = 1.0f;
        ballMoving = true;
    }
}

void specialKeyboard(int key, int x, int y) {
    // Control movement using arrow keys
    if (key == GLUT_KEY_UP) {
        ballDirectionZ = 1.0f;
        ballMoving = true;
    } else if (key == GLUT_KEY_DOWN) {
        ballDirectionZ = -1.0f;
        ballMoving = true;
    }
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Spare Ball with Cuboid Collision");

    init();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutIdleFunc(idle); // Continuously render

    glutMainLoop();

    return 0;
}
