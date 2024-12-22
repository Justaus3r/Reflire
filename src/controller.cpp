#include "raygui.h"

#include <string.h>
#include "controller.h"
#include "datastore.h"
#include <iterator>
#include <iostream>


void login_view_controller(Context& ctx){
    char* password  = ctx.password;
    bool is_doing_signup = ctx.is_doing_signup; 
    

    switch(is_doing_signup){

    case true: {
    if(strlen(password) < 8){
        ctx.show_error_passlen = true;

    }

    if(ctx.show_error_passlen){
        int result = GuiMessageBox((Rectangle){ 85, 70, 550, 200 },
                    "#191#ERROR", "PIN Number must be atleast 8-digits", "Return");
        if(result >= 0) ctx.show_error_passlen = false;
        return;
    }
     
    char special_characters[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'};
    bool special_char_found = false;
    for(int i=0; i<strlen(password); ++i){
        for(int j=0; j<strlen(special_characters); ++j){
            if(password[i] == special_characters[j]) special_char_found = true;
        }
    }
     
    if(!special_char_found){
          ctx.show_error_nospecialchar = true;   
    }

    if(ctx.show_error_nospecialchar){
     int result = GuiMessageBox((Rectangle){ 85, 70, 550, 200 },
                    "#191#ERROR", "PIN Number must have a alteast 1 special character", "Return");
     if(result >= 0) ctx.show_error_nospecialchar = false;
     return;
    }
   
    DataStore dstore(ctx.username);
    
    Datastore ds;

    ds.user_name = ctx.username;
    ds.password = ctx.password;


    dstore.createDataStore(ds, CREDENTIALS);

    ctx.is_doing_signup = false;    
    ctx.has_completed_signup = true; 
    break;
    }
   
    case false:{
       DataStore dstore(ctx.username);
       DataStore* store;
       store = dstore.readDataStore(ctx.username, CREDENTIALS);
       if(store == NULL){
           //  user doesn't exists
            ctx.show_error_nouser = true;
       }
        
       if(ctx.show_error_nouser){
           int result = GuiMessageBox((Rectangle){ 85, 70, 550, 200 },
                    "#191#ERROR", "No Such User Found!", "Return");
            if(result >= 0) ctx.show_error_nouser = false;
            return;
       }
        

       std::string username_str(ctx.username);
       std::string password_str(ctx.password);
       bool login_successfully = (store->d_store.user_name == username_str && store->d_store.password == password_str);
       if(!login_successfully){
           ctx.login_failed = true; 
       }
        

        if(ctx.login_failed){
            int result = GuiMessageBox((Rectangle){ 85, 70, 550, 200 },
                    "#191#ERROR", "Incorrect Password!", "Return");
            if(result >= 0) ctx.login_failed = false;
            return;
       }
       ctx.is_currentview_complete = true;
    break;
    }
    
    }

}


void make_reservations_view_controller(Context& ctx){

    DataStore dstore(ctx.username);
    Datastore ds;

    strcpy(ds.reservation.name, ctx.name);
    strcpy(ds.reservation.email, ctx.email);
    strcpy(ds.reservation.from, ctx.from);
    strcpy(ds.reservation.to, ctx.to_);
    strcpy(ds.reservation.date_departure, ctx.date);
    strcpy(ds.reservation.no_of_people, ctx.num_people);
    strcpy(ds.reservation.ph_no, ctx.phone);

    dstore.createDataStore(ds, RESERVATIONS);

    ctx.is_currentview_complete = true;
}


void finished_booking_controller(Context& ctx){
    // emptying all the input buffers for ctx
    // before restarting at dashboard

    strcpy(ctx.name, "");
    strcpy(ctx.from, "");
    strcpy(ctx.to_, "");
    strcpy(ctx.date, "");
    strcpy(ctx.phone, "");
    strcpy(ctx.email, "");
    strcpy(ctx.num_people, "");

    ctx.is_currentview_complete = true;
}

void dashboard_showpastreservations_controller(Context& ctx){
    int init_x = ctx.x;
    int init_y = ctx.y + 30;
    
    DrawText("Name  Email  From  To  DateOfDeparture NoOfPeople Ph.No", ctx.x, ctx.y, 18, DARKBLUE);

    DataStore dstore(ctx.username);
    DataStore* read_store;

    read_store = dstore.readDataStore(ctx.username, RESERVATIONS);
    
    int store_elements = 0;
    
    for(int i=0;i<100;++i){ 
        if((!read_store->d_store.reservation_store[i].is_occupied)) break;
            ++store_elements;
    } 
   
    int start_reservation_count = 0; 
    
    if(store_elements > 5){
      start_reservation_count = store_elements - 6; // if reservations are greater than 5, then take the last 5 of them. its since cuz, we got 0-indexed arrays
    }
    
     
    char row[1024] = "";
    int offset = 0;
    std::string idx_no;
    for(int j=start_reservation_count;j<store_elements; ++j){
        idx_no = std::to_string(j);
        idx_no += ": ";
        strcat(row, idx_no.c_str());
        strcat(row, read_store->d_store.reservation_store[j].name);
        strcat(row, "  ");
        strcat(row, read_store->d_store.reservation_store[j].email);
        strcat(row, "  ");
        strcat(row, read_store->d_store.reservation_store[j].from);
        strcat(row, "  ");
        strcat(row, read_store->d_store.reservation_store[j].to);
        strcat(row, "  ");
        strcat(row, read_store->d_store.reservation_store[j].date_departure);
        strcat(row, "  ");
        strcat(row, read_store->d_store.reservation_store[j].no_of_people);
        strcat(row, "  ");
        strcat(row, read_store->d_store.reservation_store[j].ph_no);
        DrawText(row, init_x, init_y + offset, 18 , BLACK);
        strcpy(row, "");
        offset += 30;
    }

}
