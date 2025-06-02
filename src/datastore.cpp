#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <mysql+++.h>
#include "datastore.h"

using namespace daotk::mysql;

using namespace std;

connection db_conn;

DataStore::DataStore(char datastore_name[100]){
    strcpy(dstore_name,datastore_name);
    const char* db_pass = getenv("REFLIRE_DBPASS");
    db_conn.open("localhost", "dbproj", (char*)db_pass, "dbproject");
}

void DataStore::createDataStore(Datastore ds, DataStoreType ds_type){
    switch(ds_type){
        case CREDENTIALS: { 
            auto res = db_conn.query("create table if not exists credentials(username varchar(40), password varchar(40))");         
            writeToDataStore(ds, ds_type); 
            break;
        }
    
        case RESERVATIONS: { 
            auto res = db_conn.query("create table if not exists reservations(username varchar(40), name varchar(40), email varchar(40), departure varchar(40), destination varchar(40), date varchar(40), noof_people int, phone_no varchar(20))");        
            
            writeToDataStore(ds, ds_type); 
            break; 
        }
    
    }

}


void DataStore::writeToDataStore(Datastore ds, DataStoreType ds_type){
    switch(ds_type){

        case CREDENTIALS:{
            string username();
            string password();
            auto res = db_conn.query("insert into credentials values ('%s','%s')", ds.user_name.c_str(), ds.password.c_str());
            break;
        }

        case RESERVATIONS:{
            int no_of_people = atoi(ds.reservation.no_of_people);
            
            string phone_no  (ds.reservation.ph_no);
            auto res = db_conn.query("insert into reservations values('%s', '%s', '%s', '%s', '%s', '%s', %d, '%s')", ds.user_name.c_str(), ds.reservation.name, ds.reservation.email, ds.reservation.from, ds.reservation.to, ds.reservation.date_departure, no_of_people, ds.reservation.ph_no);
            break;        
        }

    }
}

DataStore* DataStore::readDataStore(char datastore_name[100], DataStoreType ds_type){
    
    DataStore *dstore = new DataStore(datastore_name);
    string user(datastore_name);
    switch(ds_type){
    
        case CREDENTIALS:{
                auto res = db_conn.query("select * from credentials where username='%s'", user.c_str());
                if(res.is_empty()){
                    cout<<"WARNING: USER NOT FOUND!"; 
                    return NULL;
                }
               string username, password;
               res.fetch(username, password);
               dstore->d_store.user_name = username;
               dstore->d_store.password = password;
             break;
            }

        case RESERVATIONS:{
                string loggedin_username, name, email, from, to, date_departure, phone_no;
                int no_of_people;

                auto res = db_conn.query("select * from reservations where username='%s'", user.c_str());
                if(res.is_empty()){
                    cout<<"WARNING: NO RESERVATIONS FOUND!";
                    break;
                }
                int counter = 0;
                while(!res.eof()){
                    res.fetch(loggedin_username, name, email, from, to, date_departure, no_of_people, phone_no);
                    char no_of_people_carr[128];
                    sprintf(no_of_people_carr, "%d", no_of_people);
                    strcpy(dstore->d_store.reservation_store[counter].name, name.c_str());  
                    strcpy(dstore->d_store.reservation_store[counter].email, email.c_str());
                    strcpy(dstore->d_store.reservation_store[counter].from, from.c_str());
                    strcpy(dstore->d_store.reservation_store[counter].to, to.c_str());
                    strcpy(dstore->d_store.reservation_store[counter].date_departure, date_departure.c_str());
                    strcpy(dstore->d_store.reservation_store[counter].no_of_people, no_of_people_carr);
                    strcpy(dstore->d_store.reservation_store[counter].ph_no, phone_no.c_str());

                    dstore->d_store.reservation_store[counter].is_occupied = true;
                    ++counter;

                    res.next();
                }
            break;
            }


    }
    
    return dstore;
}
