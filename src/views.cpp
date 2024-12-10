#include "views.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


void Login::render(){
    this->title = "Reflire Airline Reservation System";
    this->title_x = WINDOW_WIDTH / 2 -  (MeasureText(this->title, FONT_SIZE_HEAD) / 2);
    this->title_y = WINDOW_HEIGHT * 0.10; //10% of total window height
    DrawText((const char*)title, title_x, title_y, FONT_SIZE_HEAD, BLACK);
}

