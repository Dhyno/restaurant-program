#ifndef user_h
#define user_h

#include"data.h"
#include<fstream>

class user{

public:

    user();
    ~user();

    int log_in();
    void sign_up();
    void change_data();

    void record(char* file_name,short to_do);

    data user_data;

private:
    char* file_of_user;
    int indeks[3];//indeks 0 is start of username data, ind 1 is end of username data, ind 2 start of user pasword in file
    int indeks_to_change;//change operation in file indeks file

    std::fstream operation_file;

    char* record_account;
};

#endif // user_h
