#include <cstdlib>
#include <sstream>
#include <cstring>
#include "strings.h"
#include "datastore.h"
#include <fstream>

using namespace std;

DataStore::DataStore(char datastore_name[100]){
    strcpy(dstore_name,datastore_name);
}


void DataStore::createDataStore(Datastore dstore, DataStoreType ds_type){
    switch(ds_type){
        case CREDENTIALS: {
            // following command will fail on both *nix and windows
            // if the directory that we want to create, already exists
            system("mkdir credentials");
            writeToDataStore(dstore, ds_type);
            break; 
        }

        case RESERVATIONS:{
            system("mkdir reservations");
            writeToDataStore(dstore, ds_type);
            break;
        }

    }

}


void DataStore::writeToDataStore(Datastore dstore, DataStoreType ds_type){
    switch(ds_type){
        case CREDENTIALS:{
            const char* path_delimiter = PATH_DELIMITER;
            char base_cmd[200] = "mkdir credentials";
            strcat(base_cmd, path_delimiter);
            strcat(base_cmd, this->dstore_name);
            system(base_cmd); // make the parent directory
            char creds_filepath[200] = "credentials";
            strcat(creds_filepath, path_delimiter);
            strcat(creds_filepath, this->dstore_name);
            strcat(creds_filepath, path_delimiter);
            strcat(creds_filepath, creds_file);
            fstream credential_file;
            credential_file.open(creds_filepath, ios::out | ios::app);
            char csv_record[200] = "";
            strcat(csv_record, dstore.user_name.c_str());
            strcat(csv_record, " , ");
            strcat(csv_record, dstore.password.c_str());
            string csv_record_str(csv_record);

            credential_file.write(csv_record_str.data(), csv_record_str.size());
            credential_file.close();

        break;
        }
        
        case RESERVATIONS:{
            const char* path_delimiter = PATH_DELIMITER;
            char base_cmd[200] = "mkdir reservations";
            strcat(base_cmd, path_delimiter);
            strcat(base_cmd, this->dstore_name);
            system(base_cmd);
            fstream reservations_file;
            char reservations_filepath[200] = "reservations";
            strcat(reservations_filepath, path_delimiter);
            strcat(reservations_filepath, dstore_name);
            strcat(reservations_filepath, path_delimiter);
            strcat(reservations_filepath, reservation_file);
            reservations_file.open(reservations_filepath, ios::out | ios:: app);
            char reservations_record[1024] = "";

            strcat(reservations_record, dstore.reservation.name);
            strcat(reservations_record, ",");

            strcat(reservations_record, dstore.reservation.email);
            strcat(reservations_record, ",");

            strcat(reservations_record, dstore.reservation.from);
            strcat(reservations_record, ",");


            strcat(reservations_record, dstore.reservation.to);
            strcat(reservations_record, ",");


            strcat(reservations_record, dstore.reservation.date_departure);
            strcat(reservations_record, ",");


            strcat(reservations_record, dstore.reservation.no_of_people);
            strcat(reservations_record, ",");

            strcat(reservations_record, dstore.reservation.ph_no);

            strcat(reservations_record, "\n");
            
            string reservations_record_str(reservations_record);
            reservations_file.write(reservations_record_str.data(), reservations_record_str.size());

            reservations_file.close();
        break;
        }

    }
}


DataStore* DataStore::readDataStore(char datastore_name[100], DataStoreType ds_type){
    
    DataStore* dstore = new DataStore(datastore_name);
    switch(ds_type){

        case CREDENTIALS:{
                const char* path_delimiter = PATH_DELIMITER;
                char creds_filepath[200] = "credentials";
                strcat(creds_filepath, path_delimiter);
                strcat(creds_filepath, datastore_name);
                strcat(creds_filepath, path_delimiter);
                strcat(creds_filepath, creds_file);
                fstream creds_file;
                creds_file.open(creds_filepath, ios::in);
                
                if(!creds_file.is_open()){
                    // creds file couldn't be opened
                    cout<<"ERROR: Credentials file could not be opened!";
                    return NULL;
                }

                std::string csv_delim;
                creds_file >> dstore->d_store.user_name >> csv_delim >> dstore->d_store.password;
        
                return dstore;
        }


        case RESERVATIONS:{
            const char* path_delimiter = PATH_DELIMITER;
            char reservations_filepath[200] = "reservations";
            strcat(reservations_filepath, path_delimiter);
            strcat(reservations_filepath, dstore_name);
            strcat(reservations_filepath, path_delimiter);
            strcat(reservations_filepath, reservation_file);
            fstream reser_file;

            reser_file.open(reservations_filepath, ios::in);

        
            std::string line;
            std::string csv_delim;
            int counter = 0; 
            
            std::string name_s;
            std::string email_s;
            std::string from_s;
            std::string to_s;
            std::string date_departure_s;
            std::string no_of_people_s;
            std::string ph_no_s;
            

            while (std::getline(reser_file, line)) {
                std::istringstream iss(line); 
                std::getline(iss, name_s, ',');
                std::getline(iss, email_s, ',');
                std::getline(iss, from_s, ',');
                std::getline(iss, to_s, ',');
                std::getline(iss, date_departure_s, ',');
                std::getline(iss, no_of_people_s, ',');
                std::getline(iss, ph_no_s, ',');
            
                strcpy(dstore->d_store.reservation_store[counter].name, name_s.c_str());
                strcpy(dstore->d_store.reservation_store[counter].email, email_s.c_str());
                strcpy(dstore->d_store.reservation_store[counter].from, from_s.c_str());
                strcpy(dstore->d_store.reservation_store[counter].to, to_s.c_str());
                strcpy(dstore->d_store.reservation_store[counter].date_departure, date_departure_s.c_str());
                strcpy(dstore->d_store.reservation_store[counter].no_of_people, no_of_people_s.c_str());
                strcpy(dstore->d_store.reservation_store[counter].ph_no, ph_no_s.c_str());

                dstore->d_store.reservation_store[counter].is_occupied = true;
                ++counter;
            }
            return dstore;
        }

    }


}
