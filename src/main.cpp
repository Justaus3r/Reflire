#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void) {
    // Initialize the window and GUI
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Simple Text Input");

    // Variable to store the input text
    char inputText[128] = {0};

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        // You can add custom update logic here

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the text box for input
        bool isActive = GuiTextBox((Rectangle){200, 200, 150, 30}, inputText, 128, true);

        // Display the text box state
        if (isActive) {
            DrawText("Type something:", 200, 170, 20, DARKGRAY);
        } else {
            DrawText("Click to type:", 200, 170, 20, DARKGRAY);
        }

        // Optionally, you can display the entered text below the box
        DrawText(inputText, 200, 240, 20, DARKGREEN);

        EndDrawing();
    }

    // Close the window and OpenGL context
    CloseWindow();

    return 0;
}

