#include "reflire.h"

#include "views.h"


ReFlire::ReFlire(){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WIN_TITLE);
}

void ReFlire::startEventLoop(){
    Login login_view;

     Image background = LoadImage("..\\res\\airline-travel-bg.png");
     ImageResize(&background, WINDOW_WIDTH, WINDOW_HEIGHT);
     Texture2D bg_texture = LoadTextureFromImage(background);
     UnloadImage(background);
     
     SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(bg_texture, 0, 0, WHITE); 
        if (background.data == NULL) {
            DrawText("ASD", 0, 0, 18, BLACK);
        } 
        login_view.render();

        EndDrawing();
    }
    // Close the window and OpenGL context
    CloseWindow();
}
