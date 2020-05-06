#include <iostream>
#include <stdlib.h>
#include <limits>   //potrrzebne do okreœlenia maksymalnej dlugosci strumienia wejscia cin - podczas czysczenia strumienia
#include <ios>      // potrzebne do <streamsize>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct User {
    string name, password;
    int userID;
};

void diplayUserMenu();

int main()
{
    vector <User> users;

    int selection = 0;
    while(1) {
        diplayUserMenu();
        cin >> selection;

        while(cin.fail()){ //Zabezpiecznie przed wpisaniem innych znakow niz liczby
            cout << "Wpisz liczbe (1 - 3) : " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cin >> selection;
        }
        switch(selection) {
        case 1:
            //loggin();
            break;
        case 2:
            //signIn(users);
            break;
        case 3:
            exit(0);
            break;
        default:
            cout<<"Nie ma takiej opcji!"<<endl;
            Sleep(2000);
            break;
        }
        system("cls");
    }
    return 0;
}

void diplayUserMenu(){
    cout << " --- User menu ---" << endl;
    cout << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zamknij program" << endl;
}
