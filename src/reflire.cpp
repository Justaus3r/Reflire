#include "reflire.h"
#include "views.h"


ReFlire::ReFlire(){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WIN_TITLE);
}

void ReFlire::startEventLoop(){
    Login login_view;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
    
        login_view.render();

        EndDrawing();
    }
    // Close the window and OpenGL context
    CloseWindow();
}
