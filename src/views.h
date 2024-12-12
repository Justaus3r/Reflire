#ifndef VIEWS_H
#define VIEWS_H

#include <iostream>
#include "raylib.h"
#include "misc.h"
#include "controller.h"


class View{
    protected:
        int init_x, init_y, title_x, title_y;
        char* title;
        void (*view_controller)(Context& ctx);
        virtual void render() = 0;
        virtual void registerController(void(*view_controller)(Context& ctx)) = 0;
        void executeController(Context& ctx);
};


class Login: public View{
    private:
        bool signup_button_active = true, signin_button_active = false;
        bool username_textbox_active = true, password_textbox_active = false;
        const char* signup_text = "Signup";
        const char* signin_text = "Signin";
        int signup_button_x = WINDOW_WIDTH / 2   - (MeasureText(signup_text, FONT_SIZE) + 20); 
        int signup_button_y = WINDOW_HEIGHT / 2 - (WINDOW_HEIGHT / 4);
        int signin_button_x = WINDOW_WIDTH / 2 + ( 2 );
        int signin_button_y = signup_button_y;
        int input_size = 128;
        bool input_editable = true;
        char* username_text = "Username:";
        char* password_text = "PIN Number:";
        int textbox_size = 150;
        int signin_textbox_username_x = WINDOW_WIDTH / 2 - (MeasureText(username_text, FONT_SIZE));
        int signin_textbox_username_y = WINDOW_HEIGHT / 2 - ((WINDOW_HEIGHT / 4) * 0.60);
        
        int signin_textbox_password_x = signin_textbox_username_x;
        int signin_textbox_password_y = signin_textbox_username_y + 50;

        int signup_textbox_username_x = signin_textbox_username_x;
        int signup_textbox_username_y = signin_textbox_username_y; 
        
        int signup_textbox_password_x = signup_textbox_username_x;
        int signup_textbox_password_y = signup_textbox_username_y + 50; 

        char signup_textbox_username[128] = {0};
        char signup_textbox_password[128] = {0};
        char signin_textbox_username[128] = {0};
        char signin_textbox_password[128] = {0};

        Rectangle login_page_rect = {WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.25, WINDOW_WIDTH * 0.50, WINDOW_HEIGHT * 0.50};
        char* note1 = "1: Your Password must be atleast 8-letters long and\n must contain special characters";
        char* note2 = "2: By Signingup, you agree to our terms and policies";
        char* note3 = "3: We may share telementry data with out partners";
    public:
        void render() override;
        void registerController(void(*view_controller)(Context& ctx)) override;
        void validate_internal_states(bool signup_new, bool signin_new, bool username_box_new, bool password_box_new, const int state);
        
};


#endif //VIEWS_H
