#ifndef DATASTORE_H
#define DATASTORE_H

#ifdef _WIN32
    #define PATH_DELIMITER "\\"
#else
    #define PATH_DELIMITER "/"
#endif

#include <iostream>

enum DataStoreType{
    CREDENTIALS,
    RESERVATIONS
};


//name,email,from,to,date,no_of_people,ph.no
struct Reservation{
    char name[128];
    char email[128];
    char from[128];
    char to[128];
    char date_departure[128];
    char no_of_people[128];
    char ph_no[128];
};



struct Datastore{ 
    std::string user_name;
    std::string password;
    Reservation reservation, reservation_store[100];
};


class DataStore{
    private:
        char dstore_name[100];
        char creds_file[200] = "creds.creds";
        char reservations_file[200] = "reservations.csv";
    public:
        Datastore d_store;
        DataStore(char datastore_name[100]);
        void createDataStore(Datastore dstore, DataStoreType ds_type);
        DataStore* readDataStore(char datastore_name[100], DataStoreType ds_type);
        void writeToDataStore(Datastore dstore, DataStoreType ds_type);
};



#endif //DATASTORE_H
