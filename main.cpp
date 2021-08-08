#include <iostream>
#include<conio.h>
#include<direct.h>
#include<windows.h>
#include"./user/user.h"
#include"./menu/menu_feauture.h"
#include"./guest/_guest.h"

using namespace std;

void intro();
void display_setting(user& _user, menu_feature& _menu_feature);
void success_log_in(user& _user,menu_feature& _menu_feature, guest_activity& _guest);

int main()
{
    user _user;
    menu_feature _menu_feature;
    guest_activity _guest;

    intro();

    int indeks=0;
    char mov;
    char to_display[4][10]={"log in" , "sign up", "exit"};
    while(1)
    {
        if(indeks>3)
            indeks=0;
        else if(indeks<0)
            indeks=3;

        cout<<"++++++++++++++++++++++++++++\n";
        cout<<"++++++++MAIN MENU+++++++++++\n";
        cout<<"++++++++++++++++++++++++++++\n\n";

         for(int i=0;i<4;i++)
        {
            if(indeks==i)
                cout<<"\t->"<<to_display[i]<<"<-\n\n";
            else
                cout<<"\t"<<to_display[i]<<endl<<endl;
        }

        mov=getch();

        if(mov=='s')
            indeks+=1;
        else if(mov=='w')
            indeks--;

        else if(mov=0x0D)
        {
            system("cls");
            switch(indeks)
            {
                case 0:
                    if( _user.log_in())
                        success_log_in(_user,_menu_feature,_guest);
                    else
                    {
                        cout<<"failed log in\n\n";
                        system("pause");
                    }
                    break;

                case 1:
                    _user.sign_up();
                    break;

                case 2:
                    goto close_program;

            }
        }

        system("cls");
    }

close_program:
    cout<<"program is end\n\n";
    cout<<"thank you have tried this program\n\n";

    return 0;
}

void success_log_in(user& _user,menu_feature& _menu_feature, guest_activity& _guest)
{
    int indeks=0;
    char mov;
    char to_display[7][25]={"order","show menu" , "show table reservation", "update table reservation", "order history", "setting",
                            "exit"};
    while(1)
    {
        if(indeks>6)
            indeks=0;
        else if(indeks<0)
            indeks=6;

        cout<<"++++++++++++++++++++++++++++\n";
        cout<<"+++++RESTAURANT PROGRAM+++++\n";
        cout<<"++++++++++++++++++++++++++++\n\n";

        for(int i=0;i<7;i++)
        {
            if(indeks==i)
                cout<<"\t->"<<to_display[i]<<"<-\n\n";
            else
                cout<<"\t"<<to_display[i]<<endl<<endl;
        }
        mov=getch();

        if(mov=='s')
            indeks+=1;
        else if(mov=='w')
            indeks--;

        else if(mov=0x0D)
        {
            system("cls");

            if(indeks==0)
                _guest.display(_user);
            else if(indeks==1)
                _menu_feature.show_menu();
            else if(indeks==2)
                _menu_feature.show_table();
            else if(indeks==3)
                _menu_feature.table_update_reservation();
            else if(indeks==4)
                _guest.show_order_history();
            else if(indeks==5)
                display_setting(_user,_menu_feature);
            else if(indeks==6)
                return;

        }

        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
        }

        system("cls");
    }
}


void display_setting(user& _user, menu_feature& _menu_feature)
{
    int indeks=0;
    char mov;
    char to_display[4][25]={"account setting" , "menu setting", "table setting","back"};
    while(1)
    {
        if(indeks>3)
            indeks=0;
        else if(indeks<0)
            indeks=3;

        cout<<"++++++++++++++++++++++++++++\n";
        cout<<"++++++++++SETTING+++++++++++\n";
        cout<<"++++++++++++++++++++++++++++\n\n";

        for(int i=0;i<4;i++)
        {
            if(indeks==i)
                cout<<"\t->"<<to_display[i]<<"<-\n\n";
            else
                cout<<"\t"<<to_display[i]<<endl<<endl;
        }
        mov=getch();

        if(mov=='s')
            indeks+=1;
        else if(mov=='w')
            indeks--;

        else if(mov=0x0D)
        {
            system("cls");

            if(indeks==0)
                _user.change_data();
            else if(indeks==1)
                _menu_feature.update_menu();
            else if(indeks==2)
                _menu_feature.table_update();
            else if(indeks==3)
                return;

        }

        system("cls");
    }
}

void intro()
{
    cout<<"      _             _   "<<endl;
    cout<<"     (_)           | |   "<<endl;
    cout<<"  ___ _ ____  ____ | | _____"<<endl;
    cout<<" /___) |    \\|   _\\| || ___ |"<<endl;
    cout<<"|___ | | | | | |_| | || ____|"<<endl;
    cout<<"(___/|_|_|_|_|  __/ \\_)_____)"<<endl;
    cout<<"             |_|"<<endl;

    cout<<"                   _                                  _   "<<endl;
    cout<<" ____ _____  ___ _| |_ _____ _   _  ____ _____ ____ _| |_ "<<endl;
    cout<<"/ ___) ___ |/___|_   _|____ | | | |/ ___|____ |  _ (_   _)"<<endl;
    cout<<"| |  | ____|___ | | |_/ ___ | |_| | |   / ___ | | | || |_ "<<endl;
    cout<<"|_|  |_____|___/   \\__)_____|____/|_|   \\_____|_| |_| \\__)"<<endl;



    cout<<" ____   ____ ___   ____  ____ _____ ____"<<endl;
    cout<<"|  _ \\ / ___) _ \\ / _  |/ ___|____ |    \\ "<<endl;
    cout<<"| |_| | |  | |_| ( (_| | |   / __| | | |"<<endl;
    cout<<"|  __/|_|   \\___/ \\__  |_|   \\_____|_|_|_|"<<endl;
    cout<<"|_|               (_____|"<<endl;

    system("pause");
}
