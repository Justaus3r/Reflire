#include "views.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


void Login::validate_button_states(bool signup_new, bool signin_new){
   if(signup_new) {
       signup_button_active = true;
       signin_button_active = false;
    }
   else if(signin_new) {
       signin_button_active = true;
       signup_button_active = false;
    }
}

void Login::render(){

    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);  
    this->title = "Reflire Airline Reservation System";
    this->title_x = WINDOW_WIDTH / 2 -  (MeasureText(this->title, FONT_SIZE_HEAD) / 2);
    this->title_y = WINDOW_HEIGHT * 0.10; //10% of total window height
    DrawText((const char*)title, title_x, title_y, FONT_SIZE_HEAD, BLACK);
    
    DrawRectangleRec(login_page_rect, LIGHTGRAY); 
    DrawRectangleLinesEx(login_page_rect, 2.0, BLACK);

    bool isactive_signup = GuiButton((Rectangle){signup_button_x, signup_button_y, MeasureText(signup_text, FONT_SIZE) + 20, 20}, signup_text);
    
    bool isactive_signin = GuiButton((Rectangle){signin_button_x, signin_button_y, MeasureText(signin_text, FONT_SIZE) + 20, 20}, signin_text);
        
    validate_button_states(isactive_signup, isactive_signin);

    if(signup_button_active) { 
        DrawText("SignUp....", signup_button_x, signin_button_y + 20, FONT_SIZE, BLACK);
}
    else if (signin_button_active) {
        DrawText("SignIn....", signup_button_x, signin_button_y + 20, FONT_SIZE, BLACK);
    }
}


void Login::registerController(){

}
