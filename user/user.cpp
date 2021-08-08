#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>
#include<cstring>
#include<cstdlib>
#include"user.h"
#include"../input_data/normal_input/inp_unk_str.h"
#include"../input_data/hide_input_character/hide_str.h"
#include"../input_data/search_sub_str.h"

using std::cout;
using std::endl;
using std::ios;

short maks_char=0;

user::user()
{
    user_data.id=0;
    user_data.user_name=NULL;
    user_data.pasword=NULL;
    user_data.id=0;

    indeks_to_change=0;
    file_of_user=new char[strlen("./user/user.txt")+1];
    strcpy(file_of_user,"./user/user.txt");


    //make file when object is create and get last id indeks and maks char indeks
    std::ifstream make_file( file_of_user, ios::app);
    char temp;
    short now=0;
    while(!make_file.eof())
    {
        make_file.get(temp);
        if(temp=='\n')
        {
            user_data.id+=1;
            if(maks_char < now)
                maks_char=now;
            now=0;
            continue;
        }
        now++;
    }
    if(user_data.id==0)
        user_data.id=1;

    make_file.close();

    make_file.open("./record_file/log_in.txt", ios::app);
    make_file.close();
}

user::~user()
{
    delete[] file_of_user;
    delete[] user_data.user_name;
    delete[] user_data.pasword;

    delete[] file_of_user;

    operation_file.close();
}

int user::log_in()
{
    cout<<"\tLOG IN\n";
    cout<<"    +++++++++++++++\n\n";

    //empty old data in username and pasword variable
    delete[] user_data.user_name;
    delete[] user_data.pasword;

    int failed=0;

    cout<<"ID   : ";

    if(unsigned (my_input_str(user_data.user_name)))
        failed=1;

    if(unsigned (my_custom_hide_input(user_data.pasword,user_data.user_name)))//user_name for print in funct
        failed=1;

    if(failed)
    {
        cout<<"log in failed . . . id or user is invalid\n\n";
        return 0;
    }

    operation_file.open(file_of_user,ios::in | ios::out);

    char temp[maks_char++];
    int found=0;
    while(!operation_file.eof())
    {
        operation_file.getline(temp,maks_char);
        indeks[0]=search_str(temp,"username: ");
        indeks[1]=search_str(temp,"pasword: ");
        indeks[2]=indeks[1]+strlen("pasword: ");//strlen

        found=0;
        int j;
        if(strlen(user_data.user_name) == (indeks[1]-1) - indeks[0])
        {
            for(int i=0, j=indeks[0]; j<indeks[1]-1; i++,j++)//compare username i for input indeks
            {
                if(user_data.user_name[i] != temp[j])
                {
                    found=0;
                    break;
                }
                found=1;
            }
        }

        indeks_to_change++;
        if(!found)//if username not suitable
            continue;

        found=0;//reinitate to find pasword if pasword find then data is valid
        if(strlen(user_data.pasword) == strlen(temp)-indeks[2])
        {
            for(int i=0, j=indeks[2]; i<strlen(temp)-indeks[2]; i++,j++)//i for input indeks j for start indeks in temp from txt file
            {
                if(user_data.pasword[i] != temp[j])
                {

                    found=0;
                    break;
                }
                found=1;
            }
        }

        if(found)
            break;
    }

    operation_file.close();

    record("./record_file/log_in.txt",0);

    return found;
}

void user::sign_up()
{
    cout<<"\tMAKE ACCOUNT\n";
    cout<<"    ++++++++++++++++++\n\n";

    int failed=0;

    cout<<"ID   : ";

    if(unsigned (my_input_str(user_data.user_name)))
        failed=1;

    if(unsigned (my_custom_hide_input(user_data.pasword,user_data.user_name)))//user_name for print in funct
        failed=1;

    if(failed)
    {
        cout<<"can not make account . . . id or user is invalid\n\n";
        system("pause");
        return;
    }

    operation_file.open(file_of_user, ios::in | ios::out | ios::app);
    operation_file<<user_data.id<<" username: "<<user_data.user_name<<" pasword: "<<user_data.pasword<<endl;
    operation_file.close();
    user_data.id++;

    cout<<"success make account\n\n";
    record("./record_file/account.txt",1);

    system("pause");
}

void user::change_data()
{
    cout<<"--YOU MUST LOG IN BEFORE--\n------------------------\n";
    indeks_to_change=0;//reset indeks because in log in hve increase indeks

    if(!log_in())
        return;

    cout<<"      ACCOUNT SETTING\n";
    cout<<"    ++++++++++++++++++\n\n";

    //choose change data
    int choose_data;
    cout<<"1.change username\n\n2.change pasword\n\n3.delete acoount\n\n";
    cout<<"choose : ";
    std::cin>>choose_data;

    system("cls");

    if(choose_data==1)
        cout<<"NEW ID: ";
    else if(choose_data==2)
        cout<<"NEW PASWORD: ";
    else if(choose_data==3)
        goto del;

    std::cin.ignore();

    //change username
    char* new_user_data;
    if(unsigned (my_input_str(new_user_data)))
    {
        cout<<"failed name must be fill\n";
        return;
    }

    record_account=new char(strlen(new_user_data)+1);
    strcpy(record_account,new_user_data);

del:
    operation_file.open(file_of_user,ios::in | ios::out);
    std::fstream _temp_file("./user/temp.txt", ios::in | ios::out |ios::trunc );
    if(!_temp_file)
        ios::app;

    char temp[maks_char++];
    int const_indeks=1;
    while(!operation_file.eof())
    {
        operation_file.getline(temp,maks_char);
        if(strlen(temp)==0)
            continue;

        if(const_indeks==indeks_to_change)
        {
            if(choose_data==1){
                _temp_file<<const_indeks<<" username: "<<new_user_data<<" pasword: "<<user_data.pasword<<endl;
                record("./record_file/account.txt",2);}

            else if(choose_data==2){
                _temp_file<<const_indeks<<" username: "<<user_data.user_name<<" pasword: "<<new_user_data<<endl;
                record("./record_file/account.txt",3);}
            else if(choose_data==3)
            {
                record("./record_file/account.txt",4);
                cout<<"DELETE ACCOUNT";
                indeks_to_change=-1;//to avoid loop in if
                continue;
            }

            const_indeks++;
            continue;
        }

        _temp_file<<const_indeks<<" ";

        for(int i=search_str(temp,"username: ")-10; i<strlen(temp); i++)
            _temp_file<<temp[i];

        _temp_file<<endl;
        const_indeks++;
    }

    if(operation_file.eof())
    {
        operation_file.close();//close to trunc a file
        operation_file.open(file_of_user,ios::in | ios::out | ios::trunc);//trunc file

        _temp_file.clear();
        _temp_file.seekg(ios::beg);

        while(!_temp_file.eof())
        {
            _temp_file.getline(temp,maks_char);

            if(strlen(temp)==0)//throw empty line twice
                break;

            operation_file<<temp<<endl;

        }
    }

    operation_file.close();
    _temp_file.close();
}

void user::record(char* file_name,short todo)
{
    std::ofstream save(file_name, ios::app);

    if(todo==0)
        save<<user_data.user_name<<"  "<<__TIME__<<"  "<<__DATE__<<endl;

    else if(todo==1)
        save<<"make account  "<<user_data.user_name<<"  "<<__TIME__<<"  "<<__DATE__<<endl;

    else if(todo==2)
        save<<user_data.user_name<<" change to "<<record_account<<"  "<<__TIME__<<"  "<<__DATE__<<endl;

    else if(todo==3)
        save<<user_data.user_name<<" change pw to "<<record_account<<"  "<<__TIME__<<"  "<<__DATE__<<endl;

    else if(todo==4)
        save<<"delete "<<user_data.user_name<<"  "<<__TIME__<<"  "<<__DATE__<<endl;
}































