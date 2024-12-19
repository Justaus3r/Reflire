#ifndef CONTROLLER_H
#define CONTROLLER_H


struct Context{
    char username[128];
    char password[128];
    char name[128];
    char from[128];
    char to_[128];
    char date[128];
    char phone[128];
    char email[128];
    char num_people[128];
    bool is_doing_signup;
    bool show_error_passlen = false;
    bool show_error_nospecialchar = false;
    bool show_error_nouser = false;
    bool has_completed_signup = false;
    bool is_currentview_complete = false;
    bool login_failed = false;
};


void login_view_controller(Context& ctx);

void make_reservations_view_controller(Context& ctx);

#endif
