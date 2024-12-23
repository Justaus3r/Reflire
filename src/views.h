#ifndef VIEWS_H
#define VIEWS_H

#include <iostream>
#include <chrono>
#include <ctime>
#include "raylib.h"
#include "misc.h"
#include "controller.h"


class View{
    protected:
        int init_x, init_y, title_x, title_y;
        char* title;
        bool current_view_complete = false;
        void (*view_controller)(Context& ctx);
        void executeController(Context& ctx);
    public:
        View* next_view;
        virtual void registerController(void(*view_controller)(Context& ctx)){};
        virtual View* render(){};

    // both render() and registerController() were initially pure virtual functions
    // but then we can't instantiate the object using the superclass View
    // so now they are normal virtual methods
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
        char* note1 = "1: Your PIN Number must be atleast 8-letters long and\n must contain atleast 1 special character";
        char* note2 = "2: By Signingup, you agree to our terms and policies";
        char* note3 = "3: We may share telementry data with out partners";
    public:
        Login(){};
        View* render();
        void registerController(void(*view_controller)(Context& ctx));
        void validate_internal_states(bool signup_new, bool signin_new, bool username_box_new, bool password_box_new, const int state);
        
};


class Dashboard: public View{
    private:
        bool is_subview_active = false;
        bool query_services_subview_active = false;
        bool contactus_subview_active = false;
        bool pastreservations_subview_active = false;

    public:
        Dashboard(){};
        View* render();
        void validate_internal_states(bool new_click_queryservices, bool new_click_contactus, bool new_click_pastres);
        void registerController(void(*view_controller)(Context& ctx));
};


class CharterRequest : public View {
private:
    bool input_editable = true;
    const int textbox_size = 200;
    const int input_size = 128;

    
    int name_textbox_x =  WINDOW_WIDTH / 2 - textbox_size / 2;
    int name_textbox_y = WINDOW_HEIGHT / 2 - 200;
    int from_textbox_y = name_textbox_y + 80;
    int to_textbox_y = from_textbox_y + 100;
    int date_textbox_y = from_textbox_y + 105;
    int phone_textbox_y = date_textbox_y + 80;

   
    char name_text[128] = {0};
    char from_text[128] = {0};
    char to_text[128] = {0};
    char date_text[128] = {0};
    char phone_text[128] = {0};
    char email_text[128] = {0};
    char num_people_text[128] = {0};

    
    int makereservation_button_x = WINDOW_WIDTH / 2 - (MeasureText("Make Reservation", FONT_SIZE) + 20) / 2;
    int makereservation_button_y = phone_textbox_y + 90;

    bool name_textbox_active = true;
    bool from_textbox_active = false;
    bool to_textbox_active = false;
    bool date_textbox_active = false;
    bool phone_textbox_active = false;
    bool email_textbox_active = false;
    bool numpeople_textbox_active = false;

public:
    CharterRequest(){};
    View* render();
    void registerController(void(*view_controller)(Context& ctx));
    void validate_internal_states(bool name_butt_st, bool from_butt_st, bool to_butt_st, bool date_butt_st, bool phone_butt_st, bool email_butt_st, bool numpeople_butt_st);
};

class MakingReservationOverlay: public View{
     private:
        std::chrono::time_point<std::chrono::system_clock> start_time;
        bool start_timer = true;
        char overlay_progress[1024] = "..";
        char overlay_text[128] = "Making Flight Reservation";
        int overlay_text_x = WINDOW_WIDTH / 2 - (MeasureText(overlay_text, FONT_SIZE) / 2 + 3);
        int overlay_text_y = WINDOW_HEIGHT / 2;

    public:
    MakingReservationOverlay(){};
    View* render();
    void registerController(void(*view_controller)(Context& ctx));

};


class Ticket: public View{
    private:
      Image ticket_bg;
      Texture2D ticket_texture;
    public:
        Ticket();
        View* render();
        void registerController(void(*view_controller)(Context& ctx));
};

#endif //VIEWS_H
