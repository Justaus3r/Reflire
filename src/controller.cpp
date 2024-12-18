#include "raygui.h"

#include <string.h>
#include "controller.h"
#include "datastore.h"
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
