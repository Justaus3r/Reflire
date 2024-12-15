#ifndef DATASTORE_H
#define DATASTORE_H

#include <iostream>

enum DataStoreType{
    CREDENTIALS;
    RESERVATIONS;
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
    std::string user_names[100] = {0};
    std::string passwords[100] = {0};
    Reservation reservation;
};


class DataStore{
    private:
        Datastore d_store;
    public:
    DataStore(char* datastore_name);
    void createDataStore(Datastore d_store, DataStoreType ds_type);
    DataStore* readDataStore(char* datastore_name, DataStoreType ds_type);
    void WriteToDataStore();
};



#endif //DATASTORE_H
