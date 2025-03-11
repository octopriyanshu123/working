#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_RED 0xff0000ff  // Red color
#define COLOR_BLACK 0x000000ff // Black color for background
#define RAYS_NUMBER = 100
#define PI = 3.14
// Circle struct
struct Circle {
    double x;  // Center X
    double y;  // Center Y
    double r;  // Radius
    double tolerance = 3.0;  // Small tolerance for boundary


    // Function to fill a circle
    void FillCircle(SDL_Surface *surface, Uint32 color) {
        // Loop through the bounding box of the circle
        for (int cx = x - r; cx <= x + r; cx++) {
            for (int cy = y - r; cy <= y + r; cy++) {
                // Check if the point is inside the circle
                double distance_squared = std::pow(cx - x, 2) + std::pow(cy - y, 2);
                if (distance_squared <= r * r) {
                    SDL_Rect pixel = {cx, cy, 1, 1};
                    SDL_FillRect(surface, &pixel, color);  // Draw the pixel
                }
            }
        }
    }

    // Function to draw the circle's outer boundary
    void DrawCircleBoundary(SDL_Surface *surface, Uint32 color) {
        // Loop through the bounding box of the circle
        for (int cx = x - r; cx <= x + r; cx++) {
            for (int cy = y - r; cy <= y + r; cy++) {
                // Calculate the squared distance from the center to the point (cx, cy)
                double distance_squared = std::pow(cx - x, 2) + std::pow(cy - y, 2);

                // If the distance is approximately equal to the radius, draw the point
                if (std::fabs(distance_squared - r * r) <= tolerance) {
                    SDL_Rect pixel = {cx, cy, 1, 1};  // 1x1 pixel at (cx, cy)
                    SDL_FillRect(surface, &pixel, color);  // Draw the pixel
                }
            }
        }
    }
};


// struct Ray
// {
//     double x_start, y_start;
//     double angle;
//     double x_end, y_end;
// };


// void rgenerate_rays(struct Circle circle , struct Ray rays[RAYS_NUMBER]){
//     double x_start_point = circle.x;
//     double y_srart_point = circle.y;
//     double diff_bw_rays = (2*PI)/RAYS_NUMBER;
//     double ray_curent_angle = 0;
//     for(int i=0; i<RAYS_NUMBER ; i++) {
//         // y = mx + C;
//         // in each ilteration increase the current angle of the ray
//     }
// } 
// Function to handle drawing the circle
void looping(SDL_Window* window, SDL_Surface* surface, Circle& circle , SDL_Rect& erase_rect ,Circle & circleShadow) {
    // Clear the surface with black color before drawing
    SDL_FillRect(surface, &erase_rect, COLOR_BLACK);  // Fill it with black color (clear the screen)

    // Fill the circle with white color (optional)
    circle.FillCircle(surface, COLOR_WHITE);
    circleShadow.FillCircle(surface, COLOR_WHITE);

    // Draw the outer boundary of the circle with red color
    // circle.DrawCircleBoundary(surface, COLOR_RED);

    // Update the window surface using the window, not the surface
    SDL_UpdateWindowSurface(window);
}

int main(int argc, char** argv) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1; // Exit if SDL failed to initialize
    }

    // Create SDL Window
    SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1; // Exit if window creation failed
    }

    // Get the window surface to draw on
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};

    // Create and initialize the circle
    Circle circle = {200, 300, 30};  // Circle at (450, 300) with radius 80
    Circle circleShadow = {600, 300, 100};  // Circle at (450, 300) with radius 80

    // Event loop to keep the window open
    SDL_Event event;
    bool isRunning = true;
    while (isRunning) {
        // Call looping to draw the circle and update the window
        looping(window, surface, circle , erase_rect , circleShadow);

        // Check for events (e.g., window close)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false; // Exit loop if the window is closed
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                // Move the circle with the mouse
                circle.x = event.motion.x;
                circle.y = event.motion.y;
            }
        }
    }

    // Clean up and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


// #include <iostream>
// #include <SDL2/SDL.h>
// #include <cmath>

// #define WIDTH 900
// #define HEIGHT 600
// #define COLOR_WHITE 0xffffffff
// #define COLOR_RED 0xff0000ff  // Red color
// #define COLOR_BLACK 0x000000ff // Black color for background
// #define RAYS_NUMBER 500
// #define PI 3.14159265359

// double infinite_ray_length = WIDTH*HEIGHT;
// // Circle struct
// struct Circle {
//     double x;  // Center X
//     double y;  // Center Y
//     double r;  // Radius
//     double tolerance = 3.0;  // Small tolerance for boundary

//     // Function to fill a circle
//     void FillCircle(SDL_Surface* surface, Uint32 color) {
//         // Loop through the bounding box of the circle
//         for (int cx = x - r; cx <= x + r; cx++) {
//             for (int cy = y - r; cy <= y + r; cy++) {
//                 // Check if the point is inside the circle
//                 double distance_squared = std::pow(cx - x, 2) + std::pow(cy - y, 2);
//                 if (distance_squared <= r * r) {
//                     SDL_Rect pixel = {cx, cy, 1, 1};
//                     SDL_FillRect(surface, &pixel, color);  // Draw the pixel
//                 }
//             }
//         }
//     }

//     // Function to draw the circle's outer boundary
//     void DrawCircleBoundary(SDL_Surface* surface, Uint32 color) {
//         // Loop through the bounding box of the circle
//         for (int cx = x - r; cx <= x + r; cx++) {
//             for (int cy = y - r; cy <= y + r; cy++) {
//                 // Calculate the squared distance from the center to the point (cx, cy)
//                 double distance_squared = std::pow(cx - x, 2) + std::pow(cy - y, 2);

//                 // If the distance is approximately equal to the radius, draw the point
//                 if (std::fabs(distance_squared - r * r) <= tolerance) {
//                     SDL_Rect pixel = {cx, cy, 1, 1};  // 1x1 pixel at (cx, cy)
//                     SDL_FillRect(surface, &pixel, color);  // Draw the pixel
//                 }
//             }
//         }
//     }
// };

// // Ray struct
// struct Ray {
//     double x_start, y_start;
//     double angle;
//     double x_end, y_end;
// };

// // Function to generate rays from the circle
// void generate_rays(Circle& circle, Ray rays[RAYS_NUMBER]) {
//     double diff_bw_rays = (2 * PI) / RAYS_NUMBER;  // Angle difference between rays
//     double ray_curent_angle = 0;

//     for (int i = 0; i < RAYS_NUMBER; i++) {
//         // Calculate the end point for each ray based on its angle
//         rays[i].x_start = circle.x;
//         rays[i].y_start = circle.y;
//         rays[i].angle = ray_curent_angle;

//         // Use trigonometry to calculate the x_end and y_end based on the ray's angle
//         rays[i].x_end = circle.x + infinite_ray_length * cos(ray_curent_angle);  // Calculate x endpoint
//         rays[i].y_end = circle.y + infinite_ray_length * sin(ray_curent_angle);  // Calculate y endpoint

//         // Increase the angle for the next ray
//         ray_curent_angle += diff_bw_rays;
//     }
// }

// // Function to handle drawing the circle and rays
// void looping(SDL_Window* window, SDL_Renderer* renderer, Circle& circle, SDL_Rect& erase_rect, Ray rays[RAYS_NUMBER]) {
//     // Clear the surface with black color before drawing
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set drawing color to black
//     SDL_RenderClear(renderer);  // Fill it with black color (clear the screen)

//     // Set draw color to white and draw the circle (optional)
//     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color for the circle
//     circle.FillCircle(SDL_GetWindowSurface(window), COLOR_WHITE); // We will not use the surface to draw the rays

//     // Draw the rays
//     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color for rays
//     for (int i = 0; i < RAYS_NUMBER; i++) {
//         // Draw each ray from its start to its end point
//         SDL_RenderDrawLine(renderer, rays[i].x_start, rays[i].y_start, rays[i].x_end, rays[i].y_end);
//     }

//     // Present the renderer (update the window with the rendered content)
//     SDL_RenderPresent(renderer);
// }

// int main(int argc, char** argv) {
//     // Initialize SDL
//     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
//         std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
//         return 1; // Exit if SDL failed to initialize
//     }

//     // Create SDL Window
//     SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
//     if (!window) {
//         std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//         SDL_Quit();
//         return 1; // Exit if window creation failed
//     }

//     // Create SDL Renderer for drawing lines
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (!renderer) {
//         std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
//         SDL_Quit();
//         return 1;
//     }

//     // Get the window surface to draw on
//     SDL_Surface* surface = SDL_GetWindowSurface(window);
//     SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};

//     // Create and initialize the circle
//     Circle circle = {200, 300, 100};  // Circle at (200, 300) with radius 30

//     // Create an array for the rays
//     Ray rays[RAYS_NUMBER];
//     generate_rays(circle, rays);  // Generate 100 rays

//     // Event loop to keep the window open
//     SDL_Event event;
//     bool isRunning = true;
//     while (isRunning) {
//         // Call looping to draw the circle and rays, and update the window
//         looping(window, renderer, circle, erase_rect, rays);

//         // Check for events (e.g., window close)
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 isRunning = false; // Exit loop if the window is closed
//             }
//             if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
//                 // Move the circle with the mouse
//                 circle.x = event.motion.x;
//                 circle.y = event.motion.y;

//                 // Regenerate the rays whenever the circle moves
//                 generate_rays(circle, rays);
//             }
//         }
//     }

//     // Clean up and quit SDL
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }
