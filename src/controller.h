#ifndef CONTROLLER_H
#define CONTROLLER_H


struct Context{
    char* username;
    char* password;
    bool is_doing_signup;
    bool show_error_passlen = false;
    bool show_error_nospecialchar = false;
    bool is_currentview_complete = false;
};


void login_view_controller(Context& ctx);

#endif
