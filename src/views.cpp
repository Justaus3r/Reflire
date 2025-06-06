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


void Dashboard::validate_internal_states(bool new_click_queryservices, bool new_click_contactus, bool new_click_pastres){
    if(new_click_queryservices){
        query_services_subview_active = true;
        bool contactus_subview_active = false;
        bool pastreservations_subview_active = false;
    }

    else if(new_click_contactus){
        query_services_subview_active = false;
        bool contactus_subview_active = true;
        bool pastreservations_subview_active = false;

    }

    else if(new_click_pastres){
        query_services_subview_active = false;
        bool contactus_subview_active = false;
        bool pastreservations_subview_active = true;
    }
}

View* Dashboard::render() {
    if(!is_subview_active){ 
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
           is_subview_active = true;
           query_services_subview_active = true;
        }
        else if(clicked_contactus){
            is_subview_active = true;
            contactus_subview_active = true;
        }

        else if(clicked_pastreservations){
            pastreservations_subview_active = true;
            is_subview_active = true;
        }
    }
    
    if(query_services_subview_active){
        
        DrawText("Frequently Asked Questions", WINDOW_WIDTH / 2 - MeasureText("Frequently Asked Questions", FONT_SIZE_HEAD) / 2, WINDOW_HEIGHT * 0.05, FONT_SIZE_HEAD, BLACK);
     
        Rectangle InRect = { 20, 100, 760, 400 }; 
        Rectangle backButtRect = { WINDOW_WIDTH / 2 - MeasureText("Back", FONT_SIZE), 530, 100, 40 };

        DrawRectangleRec(InRect, WHITE);
        DrawRectangleLinesEx(InRect, 5, DARKGRAY);

        std::string query1("Do you offer one-way or round-trip charter options?");
        std::string ans1("No, we only provide one-way charter option tailored to your need"); 
        std::string query2("What is your policy for cancellations, refunds, or \nrescheduling?");
        std::string ans2("Cancellation and rescheduling policies vary based on the booking agreement, with\npotential fees applied.Refunds depend on the notice period and terms of the contract.");
        std::string query3("Do you offer corporate packages for business travel?");
        std::string ans3("Yes, we offer customizable corporate packages designed for business travel,\n including priority services and flexible scheduling."); 


        DrawText(("Q->" + query1).c_str(), InRect.x + 20, InRect.y + 20, 22, BLACK);
        DrawText(("" + ans1).c_str(), InRect.x + 20, InRect.y + 70, FONT_SIZE, DARKGRAY);

    
        DrawText(("Q->" + query2).c_str(), InRect.x + 20, InRect.y + 130, 22, BLACK);
        DrawText(("" + ans2).c_str(), InRect.x + 20, InRect.y + 180, FONT_SIZE, DARKGRAY);  

        DrawText(("Q->" + query3).c_str(), InRect.x + 20, InRect.y + 230, 22, BLACK);
        DrawText(("" + ans3).c_str(), InRect.x + 20, InRect.y + 275, FONT_SIZE, DARKGRAY);  

    
        if (GuiButton(backButtRect, "Back")) {
            is_subview_active = false;
            query_services_subview_active = false;
            contactus_subview_active = false;
            pastreservations_subview_active = false;
        }


    }

    else if(contactus_subview_active){

        Rectangle InRect = { 20, 100, 760, 400 }; 
        Rectangle backButtRect = { WINDOW_WIDTH / 2 - MeasureText("Back", FONT_SIZE), 530, 100, 40 };


        DrawText("Contact Us", WINDOW_WIDTH / 2 - MeasureText("Contact Us", FONT_SIZE_HEAD) / 2, WINDOW_HEIGHT * 0.05, FONT_SIZE_HEAD, BLACK);

   
        DrawRectangleRec(InRect, LIGHTGRAY);
        DrawRectangleLinesEx(InRect, 5, DARKGRAY);

     

        DrawText("Email: ifno@reflire.com", InRect.x + 20, InRect.y + 20, 25, BLACK);
        DrawText("Phone: +1 (555) 123-4567", InRect.x + 20, InRect.y + 50, 25, BLACK);

    
        DrawText("Visit our Discussions page for more details:", InRect.x + 20, InRect.y + 150, 25, BLACK);
        DrawText("https://github.com/Justaus3r/Reflire/discussions/", InRect.x + 20, InRect.y + 180, 20, BLUE);  

   
        if (GuiButton(backButtRect, "Back")) {
            is_subview_active = false;
            query_services_subview_active = false;
            contactus_subview_active = false;
            pastreservations_subview_active = false;
        }


    }

    else if(pastreservations_subview_active){
        
        Rectangle InRect = { 20, 100, 760, 400 }; 
        Rectangle backButtRect = { WINDOW_WIDTH / 2 - MeasureText("Back", FONT_SIZE), 530, 100, 40 };

        DrawText("Reservations History", WINDOW_WIDTH / 2 - MeasureText("Reservations History", FONT_SIZE_HEAD) / 2, WINDOW_HEIGHT * 0.05, FONT_SIZE_HEAD, BLACK);
   
        DrawRectangleRec(InRect, LIGHTGRAY);
        DrawRectangleLinesEx(InRect, 5, DARKGRAY);

        ctx.x = InRect.x + 20;
        ctx.y = InRect.y + 30;

        this->executeController(ctx);  
   
        if (GuiButton(backButtRect, "Back")) {
            is_subview_active = false;
            query_services_subview_active = false;
            contactus_subview_active = false;
            pastreservations_subview_active = false;
        }
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
    DrawText("To:", 495, from_textbox_y, FONT_SIZE, BLACK);
    DrawText("Date:", 42, date_textbox_y, FONT_SIZE, BLACK);
    DrawText("Phone No:", name_textbox_x, phone_textbox_y - 20, FONT_SIZE, BLACK);
    DrawText("Email:", 495, name_textbox_y, FONT_SIZE, BLACK);
    DrawText("No. of People:", 495, date_textbox_y, FONT_SIZE, BLACK);

    bool name_butt_st = GuiTextBox((Rectangle){150, name_textbox_y, textbox_size, 20}, name_text, input_size, name_textbox_active);
    bool from_butt_st = GuiTextBox((Rectangle){150, from_textbox_y, textbox_size, 20}, from_text, input_size, from_textbox_active);
    bool to_butt_st = GuiTextBox((Rectangle){550, from_textbox_y, textbox_size, 20}, to_text, input_size, to_textbox_active);
    bool date_butt_st = GuiTextBox((Rectangle){150, date_textbox_y, textbox_size, 20}, date_text, input_size, date_textbox_active);
    bool phone_butt_st = GuiTextBox((Rectangle){name_textbox_x, phone_textbox_y+20, textbox_size, 20}, phone_text, input_size, phone_textbox_active);
    bool email_butt_st = GuiTextBox((Rectangle){550, name_textbox_y, textbox_size, 20}, email_text, input_size, email_textbox_active);
    bool numpeople_butt_st = GuiTextBox((Rectangle){610, date_textbox_y, textbox_size * 0.60, 20}, num_people_text, input_size, numpeople_textbox_active);

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
        //we empty all the input buffers before continuing to
        // the next view
        
        strcpy(name_text, "");
        strcpy(from_text, "");
        strcpy(to_text, "");
        strcpy(date_text, "");
        strcpy(phone_text, "");
        strcpy(email_text, "");
        strcpy(num_people_text, "");

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
        // do nothing on 4th second
        ;
    }

    else if(time_elapsed_int == 5){
        ctx.is_currentview_complete = false;
        start_timer = true;
        strcpy(overlay_progress, "");

        return this->next_view;
    }
   return this; 
}

void MakingReservationOverlay::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}


Ticket::Ticket(){
    ticket_bg = LoadImage("../res/ticket_bg.jpeg");
    ImageResize(&ticket_bg, WINDOW_WIDTH * 0.77, WINDOW_HEIGHT * 0.67);
    ticket_texture = LoadTextureFromImage(ticket_bg);
    UnloadImage(ticket_bg);
}

View* Ticket::render(){
   DrawText("Flight Ticket", WINDOW_WIDTH / 2 - MeasureText("Flight Ticket", FONT_SIZE_HEAD) / 2, WINDOW_HEIGHT * 0.05, FONT_SIZE_HEAD, DARKGRAY);
    

    Rectangle ticketBox = {WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1, WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.7};
    DrawRectangleRec(ticketBox, LIGHTGRAY);
    DrawRectangleLinesEx(ticketBox, 10, DARKBLUE);

    Rectangle ticketBoxShadow = {WINDOW_WIDTH * 0.1 + 5, WINDOW_HEIGHT * 0.1 + 5, WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.7};
    DrawRectangleRec(ticketBoxShadow, Color{0, 0, 0, 50});


    DrawTexture(ticket_texture, WINDOW_WIDTH*0.115, WINDOW_HEIGHT*0.12, WHITE);

    std::string name(ctx.name);
    std::string email(ctx.email);
    std::string num_of_people(ctx.num_people);
    std::string date(ctx.date);
    std::string from(ctx.from);
    std::string to(ctx.to_);
    std::string ph_no(ctx.phone);

    DrawText(("Flight Curator: " + name).c_str(), ticketBox.x + 20, ticketBox.y + 50, FONT_SIZE, BLACK);
    DrawText(("Email: " + email).c_str(), ticketBox.x + 20, ticketBox.y + 80, FONT_SIZE, BLACK);
    DrawText(("Number of People: " + num_of_people).c_str(), ticketBox.x + 20, ticketBox.y + 110, FONT_SIZE, BLACK);
    DrawText(("Date: " + date).c_str(), ticketBox.x + 20, ticketBox.y + 140, FONT_SIZE, BLACK);
    DrawText(("From: " + from).c_str(), ticketBox.x + 20, ticketBox.y + 170, FONT_SIZE, BLACK);
    DrawText(("To: " + to).c_str(), ticketBox.x + 20, ticketBox.y + 200, FONT_SIZE, BLACK);
    DrawText(("Phone Number: " + ph_no).c_str(), ticketBox.x + 20, ticketBox.y + 230, FONT_SIZE, BLACK);

    DrawLine(ticketBox.x, ticketBox.y + 260, ticketBox.x + ticketBox.width, ticketBox.y + 260, DARKGRAY);

    DrawText("Thank you for booking with us!", WINDOW_WIDTH / 2 - MeasureText("Thank you for booking with us!", FONT_SIZE) / 2, ticketBox.y + 290, FONT_SIZE, DARKGRAY);



    Rectangle finishButtonRect = {WINDOW_WIDTH * 0.7, WINDOW_HEIGHT * 0.8, 150, 40};
    bool has_finished_ticketing = GuiButton(finishButtonRect, "Finish");


    if(has_finished_ticketing){
        this->executeController(ctx); 
    } 

    if(ctx.is_currentview_complete){
        ctx.is_currentview_complete = false;
        return this->next_view;
    }

    return this;
}

void Ticket::registerController(void(*view_controller)(Context& ctx)){
    this->view_controller = view_controller;
}
