#include "views.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

const int LOGIN_BUTTONS_STATUS =  1;
const int TEXTBOX_STATUS  = 2;

Context ctx;

void View::executeController(Context& controller_ctx){
    this->view_controller(controller_ctx);
}


void Login::validate_internal_states(bool signup_new, bool signin_new, bool username_editable, bool password_editable, const int internal_state){
    switch(internal_state){
        case(LOGIN_BUTTONS_STATUS): {
            // signup/signin buttons
            if(signup_new) {
                signup_button_active = true;
                signin_button_active = false;
            }
            else if(signin_new) {
                signin_button_active = true;
                signup_button_active = false;
            }
            break;
            }
        case(TEXTBOX_STATUS): {
            if(username_editable){ 
                username_textbox_active = !username_textbox_active;
            }
            else if(password_editable){ 
                password_textbox_active = !password_textbox_active;
            }
            break;
        }

    }
}

void Login::render(){
    
    this->title = "Reflire Airline Reservation System";
    this->title_x = WINDOW_WIDTH / 2 -  (MeasureText(this->title, FONT_SIZE_HEAD) / 2);
    this->title_y = WINDOW_HEIGHT * 0.10; //10% of total window height 
    
    DrawText((const char*)title, title_x, title_y, FONT_SIZE_HEAD, BLACK);
    
    DrawRectangleRec(login_page_rect, SKYBLUE); 
    DrawRectangleLinesEx(login_page_rect, 2.0, BLACK);

    bool isactive_signup = GuiButton((Rectangle){signup_button_x, signup_button_y, MeasureText(signup_text, FONT_SIZE) + 20, 20}, signup_text);
    
    bool isactive_signin = GuiButton((Rectangle){signin_button_x, signin_button_y, MeasureText(signin_text, FONT_SIZE) + 20, 20}, signin_text);
        
    validate_internal_states(isactive_signup, isactive_signin, false, false, LOGIN_BUTTONS_STATUS);

    if(signup_button_active) {
        DrawText(signup_text, (signin_button_x - MeasureText(signup_text, FONT_SIZE) / 2), signup_button_y + 30, FONT_SIZE, BLACK);

        DrawText((const char*)username_text, (WINDOW_WIDTH*0.25 + 5), signup_textbox_username_y, FONT_SIZE, BLACK);

        bool username_box_active = GuiTextBox((Rectangle){signup_textbox_username_x, signup_textbox_username_y, textbox_size, 20}, signup_textbox_username, input_size, username_textbox_active);

        DrawText((const char*)password_text, (WINDOW_WIDTH*0.25 + 5), signup_textbox_password_y, FONT_SIZE, BLACK);

        bool password_box_active = GuiTextBox((Rectangle){signup_textbox_password_x, signup_textbox_password_y, textbox_size, 20}, signup_textbox_password, input_size, password_textbox_active);

        validate_internal_states(false, false, username_box_active, password_box_active, TEXTBOX_STATUS);

        DrawText("Note: ", (WINDOW_WIDTH*0.25 + 5), (WINDOW_HEIGHT * 0.50) , 14, BLACK);
    
        DrawText(note1, (WINDOW_WIDTH*0.25 + 5), (WINDOW_HEIGHT * 0.53) , 14, BLACK);
        DrawText(note2, (WINDOW_WIDTH*0.25 + 5), (WINDOW_HEIGHT * 0.60) , 14, BLACK);
        DrawText(note3, (WINDOW_WIDTH*0.25 + 5), (WINDOW_HEIGHT * 0.65) , 14, BLACK);

        bool do_signup_button_status = GuiButton((Rectangle){(WINDOW_WIDTH * 0.55), (WINDOW_HEIGHT * 0.70), MeasureText("Create Account", FONT_SIZE) + 20, 20}, "Create Account"); 
        
        ctx.is_doing_signup = true;
        ctx.username = signup_textbox_username;
        ctx.password = signup_textbox_password;
        
        bool any_error = ctx.show_error_passlen || ctx.show_error_nospecialchar;

        if(do_signup_button_status || any_error){
            this->executeController(ctx);
        }
    
    }
    

    else if (signin_button_active) {
        DrawText(signin_text, (signin_button_x - MeasureText(signin_text, FONT_SIZE) / 2), signin_button_y + 30, FONT_SIZE, BLACK);

        DrawText((const char*)username_text, (WINDOW_WIDTH*0.25 + 5), signin_textbox_username_y, FONT_SIZE, BLACK);

        bool username_box_active = GuiTextBox((Rectangle){signin_textbox_username_x, signin_textbox_username_y, textbox_size, 20}, signin_textbox_username, input_size, username_textbox_active);

        DrawText((const char*)password_text, (WINDOW_WIDTH*0.25 + 5), signin_textbox_password_y, FONT_SIZE, BLACK);

        bool password_box_active = GuiTextBox((Rectangle){signin_textbox_password_x, signin_textbox_password_y, textbox_size, 20}, signin_textbox_password, input_size, password_textbox_active);

        validate_internal_states(false, false, username_box_active, password_box_active, TEXTBOX_STATUS);

    bool do_signin_button_status = GuiButton((Rectangle){(WINDOW_WIDTH * 0.60), (WINDOW_HEIGHT * 0.60), MeasureText("  Login  ", FONT_SIZE) + 20, 20}, "Login"); 
    
    if(do_signin_button_status){     
        this->executeController(ctx);
    }

    }
}


void Login::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}
