#include "views.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <iostream>

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

View* Login::render(){
    
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
        strcpy(ctx.username, signup_textbox_username);
        strcpy(ctx.password, signup_textbox_password);

        
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
    

        ctx.is_doing_signup = false;
        strcpy(ctx.username, signin_textbox_username);
        strcpy(ctx.password, signin_textbox_password);
        bool signin_error = ctx.show_error_nouser || ctx.login_failed;

        if(do_signin_button_status || signin_error){     
            this->executeController(ctx);
        }


    }
    
    if(ctx.has_completed_signup){
        signup_button_active = false;
        signin_button_active = true;
    }

    if(ctx.is_currentview_complete){
        ctx.is_currentview_complete = false;
        return this->next_view; 
    }
    else{
        return this;
    }
}



void Login::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}



View* Dashboard::render() {
    
    DrawText("Dashboard", WINDOW_WIDTH / 2 - MeasureText("Dashboard", FONT_SIZE_HEAD) / 2, WINDOW_HEIGHT * 0.05, FONT_SIZE_HEAD, BLACK);

    Rectangle charter_flight_rect = { WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.3, 250, 85 };
    Rectangle query_services_rect = { WINDOW_WIDTH * 0.6, WINDOW_HEIGHT * 0.3, 250, 85 };
    Rectangle contact_us_rect = { WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.6, 250, 85 };
    Rectangle check_reservation_rect = { WINDOW_WIDTH * 0.6, WINDOW_HEIGHT * 0.6, 250, 85 };

    DrawRectangleRec(charter_flight_rect, LIGHTGRAY);
    DrawRectangleRec(query_services_rect, LIGHTGRAY);
    DrawRectangleRec(contact_us_rect, LIGHTGRAY);
    DrawRectangleRec(check_reservation_rect, LIGHTGRAY);

    bool clicked_charterflight = GuiButton((Rectangle){charter_flight_rect.x + 10, charter_flight_rect.y + 10, charter_flight_rect.width - 20, charter_flight_rect.height - 20}, "Charter a Flight");
    bool clicked_queryservices = GuiButton((Rectangle){query_services_rect.x + 10, query_services_rect.y + 10, query_services_rect.width - 20, query_services_rect.height - 20}, "Query Services");
    bool clicked_contactus = GuiButton((Rectangle){contact_us_rect.x + 10, contact_us_rect.y + 10, contact_us_rect.width - 20, contact_us_rect.height - 20}, "Contact Us");
    bool clicked_pastreservations = GuiButton((Rectangle){check_reservation_rect.x + 10, check_reservation_rect.y + 10, check_reservation_rect.width - 20, check_reservation_rect.height - 20}, "Past Reservations");

    if(clicked_charterflight){
        return this->next_view;     
    }
    else if(clicked_queryservices){

    }
    else if(clicked_contactus){

    }

    else if(clicked_pastreservations){

    }


    return this;

}

void Dashboard::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}

void CharterRequest::validate_internal_states(bool name_butt_st, bool from_butt_st, bool to_butt_st, bool date_butt_st, bool phone_butt_st, bool email_butt_st, bool numpeople_butt_st) {

    if(name_butt_st){
        name_textbox_active = !name_textbox_active;
    }

    else if(from_butt_st){
        from_textbox_active = !from_textbox_active;
    }

    else if(to_butt_st){
        to_textbox_active = !to_textbox_active;
    }

    else if(date_butt_st){
        date_textbox_active = !date_textbox_active;
    }

    else if(phone_butt_st){
        phone_textbox_active = !phone_textbox_active;
    }

    else if(email_butt_st){
        email_textbox_active = !email_textbox_active;
    }

    else if(numpeople_butt_st){
        numpeople_textbox_active = !numpeople_textbox_active;
    }

}

View* CharterRequest::render() {
  
    this->title = "Make Flight Reservation";
    this->title_x = WINDOW_WIDTH / 2 -  (MeasureText(this->title, FONT_SIZE_HEAD) / 2);
    this->title_y = WINDOW_HEIGHT * 0.08; 
    DrawText(this->title, title_x, title_y, FONT_SIZE_HEAD, DARKGRAY);


   
    DrawText("Name:", 42, name_textbox_y, FONT_SIZE, BLACK);
    DrawText("From:", 42, from_textbox_y, FONT_SIZE, BLACK);
    DrawText("To:", 595, from_textbox_y, FONT_SIZE, BLACK);
    DrawText("Date:", 42, date_textbox_y, FONT_SIZE, BLACK);
    DrawText("Phone No:", name_textbox_x, phone_textbox_y - 20, FONT_SIZE, BLACK);
    DrawText("Email:", 595, name_textbox_y, FONT_SIZE, BLACK);
    DrawText("No. of People:", 500, date_textbox_y, FONT_SIZE, BLACK);

    bool name_butt_st = GuiTextBox((Rectangle){150, name_textbox_y, textbox_size, 20}, name_text, input_size, name_textbox_active);
    bool from_butt_st = GuiTextBox((Rectangle){150, from_textbox_y, textbox_size, 20}, from_text, input_size, from_textbox_active);
    bool to_butt_st = GuiTextBox((Rectangle){700, from_textbox_y, textbox_size, 20}, to_text, input_size, to_textbox_active);
    bool date_butt_st = GuiTextBox((Rectangle){150, date_textbox_y, textbox_size, 20}, date_text, input_size, date_textbox_active);
    bool phone_butt_st = GuiTextBox((Rectangle){name_textbox_x, phone_textbox_y+20, textbox_size, 20}, phone_text, input_size, phone_textbox_active);
    bool email_butt_st = GuiTextBox((Rectangle){700, name_textbox_y, textbox_size, 20}, email_text, input_size, email_textbox_active);
    bool numpeople_butt_st = GuiTextBox((Rectangle){710, date_textbox_y, textbox_size, 20}, num_people_text, input_size, numpeople_textbox_active);

    bool do_reservation_button_status = GuiButton((Rectangle){makereservation_button_x, makereservation_button_y, MeasureText("Make Reservation", FONT_SIZE) + 20, 30}, "Make Reservation");
     

    validate_internal_states(name_butt_st, from_butt_st, to_butt_st, date_butt_st, phone_butt_st, email_butt_st, numpeople_butt_st);
   
    strcpy(ctx.name, name_text);
    strcpy(ctx.from, from_text);
    strcpy(ctx.to_, to_text);
    strcpy(ctx.date, date_text);
    strcpy(ctx.phone, phone_text);
    strcpy(ctx.email, email_text);
    strcpy(ctx.num_people, num_people_text);

    if(do_reservation_button_status){
        this->executeController(ctx);
    }

    if(ctx.is_currentview_complete){
        ctx.is_currentview_complete = false;
        return this->next_view;
    }
    else{
        return this;
    }
}

void CharterRequest::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}

View* MakingReservationOverlay::render(){
    if(start_timer){
        start_time = std::chrono::system_clock::now();
        start_timer = false;
    }
 
    DrawText(overlay_text, overlay_text_x, overlay_text_y, FONT_SIZE, BLACK ); 
    DrawText(overlay_progress, overlay_text_x * 0.80, (overlay_text_y + 10), FONT_SIZE, BLACK );

    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now(); 
    std::chrono::duration<double> time_elapsed = time_now - start_time;
        
    int time_elapsed_int = time_elapsed.count();
    // add a . every second
    if(time_elapsed_int == 1){
        strcat(overlay_progress, ".");
    }

    else if(time_elapsed_int == 2){
        // do nothing on 2nd second
        ;
    }

    else if(time_elapsed_int == 3){
        strcat(overlay_progress, ".");
    }

    else if(time_elapsed_int == 4){
        //strcat(overlay_progress, ".");
        ;
    }

    else if(time_elapsed_int == 5){
        return this->next_view;
    }
   return this; 
}

void MakingReservationOverlay::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}


View* Ticket::render(){
    DrawText("FINAL VIEW", 0,0, 14, BLACK);
    return this;
}

void Ticket::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}
