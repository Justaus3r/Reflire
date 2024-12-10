#ifndef VIEWS_H
#define VIEWS_H

#include <iostream>
#include "raylib.h"
#define INCLUDE_WIN_DATA 
#include "misc.h"


class View{
    protected:
        int init_x, init_y, title_x, title_y;
        char* title;
        virtual void render() = 0;
};

class Login: public View{
    private:
        char* signup_text = "Signup";
        char* signin_text = "Signin";
        int signup_button_x = WINDOW_WIDTH / 2 - (MeasureText(signup_text, FONT_SIZE) + 3); 
        int signup_button_y = WINDOW_HEIGHT / 2 - (WINDOW_HEIGHT / 4);
        int signin_button_x = WINDOW_WIDTH / 2 + ( 2 );
        int signin_button_y = signup_button_y;
        int input_size = 128;
        bool editable = true;
        char* username_text = "Username";
        char* password_text = "Password";
        char* reenter_pass_text = "Re-enter Password";
        int textbox_size = 150;
        int signin_textbox_username_x = WINDOW_WIDTH / 2 - (textbox_size + MeasureText(username_text, FONT_SIZE));
        int signin_textbox_username_y = WINDOW_HEIGHT / 2 - ((WINDOW_HEIGHT / 4) * 0.10);
        
        int signin_textbox_password_x = signin_textbox_username_x;
        int signin_textbox_password_y = signin_textbox_username_y + 20;

        int signup_textbox_username_x = signin_textbox_username_x;
        int signup_textbox_username_y = signin_textbox_username_y; 
        
        int signup_textbox_password_x = signup_textbox_username_x;
        int signup_textbox_password_y = signup_textbox_username_y + 20; 

        char signup_textbox[128] = {0};
        char signin_textbox[128] = {0};
    public:
        void render() override;
        
};


#endif //VIEWS_H
