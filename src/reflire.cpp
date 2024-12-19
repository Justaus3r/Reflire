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
    Dashboard dashboard_view;
    CharterRequest charter_req_view; 
    MakingReservationOverlay makereservation_overlay_view;
    Ticket ticket_view;

    login_view.registerController(login_view_controller);
    charter_req_view.registerController(make_reservations_view_controller);     

    login_view.next_view = &dashboard_view;
    dashboard_view.next_view = &charter_req_view; 
    charter_req_view.next_view = &makereservation_overlay_view;
    makereservation_overlay_view.next_view = &ticket_view;
    ticket_view.next_view = &dashboard_view;

    Image background = LoadImage("../res/airline-travel-bg.png");
    ImageResize(&background, WINDOW_WIDTH, WINDOW_HEIGHT);
    Texture2D bg_texture = LoadTextureFromImage(background);
    UnloadImage(background);
    SetTargetFPS(60);
    
    View* current_view = &login_view;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(bg_texture, 0, 0, WHITE); 
        if (background.data == NULL) {
            std::cout<<"WARNING: Failed to load background image.";
        } 
        current_view = current_view->render(); // will return the next view if, current view is complete

        EndDrawing();
    }
    // Close the window and OpenGL context
    CloseWindow();
}
