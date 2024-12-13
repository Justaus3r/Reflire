#include "raygui.h"

#include <string.h>
#include "controller.h"




void login_view_controller(Context& ctx){
    char* username = ctx.username;
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
    
    ctx.is_currentview_complete = true;
    
    break;
    }
   
    case false:{
        ;
    break;
    }
    
    }

}
