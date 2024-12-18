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


//reservation_no,name,email,from,to,date,no_of_people,ph.no
struct Reservation{
    std::string reservation_no;
    std::string name;
    std::string email;
    std::string from;
    std::string to;
    std::string date_departure;
    std::string no_of_people;
    std::string ph_no;
};



struct Datastore{ 
    std::string user_name;
    std::string password;
    Reservation reservation;
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
