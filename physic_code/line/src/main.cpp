#include <GL/glut.h>
#include <cmath>
#include <utility>

#define window_width  800
#define window_height 800
float length_line = 0.5f;
float radius = 0.03f;
float origin[] = {0.0f, 0.0f};
float pi = 3.1415926f;
float angle = pi / 2;
float angular_velocity = 0.00;
float angular_acc  = 0.00;
float gravity  = 0.00010193679918451;
// float air_drag = 0.99999;
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
            float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(dx + x, dy + y);
        }
        glEnd();
    }
};

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

std::pair<float, float> update_frame() {
    float florce = gravity*sin(angle);
    angular_acc = florce;
    angular_velocity += angular_acc;
    // angular_velocity -= air_drag;
    angle += angular_velocity;
    float newx = sin(angle) * length_line;
    float newy = cos(angle) * length_line;
    return std::make_pair(newx, newy);
}

void main_loop_function() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    Circle c1(0.0f, 0.0f, radius);
    Circle c2(0.0f, 0.0f, radius);

    std::pair<float, float> new_position = update_frame();
    c1.x = new_position.first;
    c1.y = new_position.second;

    std::pair<float, float> new_position2 = update_frame();
    c2.x = new_position2.first;
    c2.y = new_position2.second;

    c1.drawFilledCircle(1000);
    c2.drawFilledCircle(1000);

    glColor3f(0.0f, 1.0f, 0.0f);

    drawLine(origin[0], origin[1], c1.x, c1.y);
    drawLine(c1.x, c1.y, c2.x, c2.y);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Filled Circle and Line Rendering");
    glutIdleFunc(main_loop_function);
    GL_Setup(window_width, window_height);
    glutMainLoop();
}
