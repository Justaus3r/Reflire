#include "views.h"
#include "reflire.h"
#include "misc.h"
#include "raygui.h"
#include <iostream>
#include "controller.h"



ReFlire::ReFlire(){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WIN_TITLE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);  
}

void ReFlire::startEventLoop(){
    Login login_view;
    login_view.registerController(login_view_controller);
    
    Image background = LoadImage("../res/airline-travel-bg.png");
    ImageResize(&background, WINDOW_WIDTH, WINDOW_HEIGHT);
    Texture2D bg_texture = LoadTextureFromImage(background);
    UnloadImage(background);
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(bg_texture, 0, 0, WHITE); 
        if (background.data == NULL) {
            std::cout<<"WARNING: Failed to load background image.";
        } 
        login_view.render();

        EndDrawing();
    }
    // Close the window and OpenGL context
    CloseWindow();
}
