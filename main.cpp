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
void addNewUser(vector <User> &users);
void saveUsersToFile(const vector <User> &users);
//void loadUsersFromFile(vector <User> &users);

int main()
{
    vector <User> users;
    //loadUsersFromFile(users);

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
            addNewUser(users);
            saveUsersToFile(users);
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

void addNewUser(vector <User> &users) {
    fstream loadFile("users.txt", ios::in);

    if(!loadFile.is_open()) {
        fstream loadFile("users.txt", ios::out);
        loadFile.close();
    }

    system("cls");
    string userName, userPw;

    cout << "--- Rajestracja ---" << endl << endl;
    cout << "Wpisz login: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin >> userName;
    cout << "Wpisz haslo: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin >> userPw;

    User newUser;
    newUser.name = userName;
    newUser.password = userPw;
    if(users.empty()){
        newUser.userID = 1;
    }
    else{
        vector<User>::iterator itr = users.end();
        itr--;
        newUser.userID = (*itr).userID + 1;
    }

    users.push_back(newUser);
    cout<<endl<<"Uzytkownik dodany"<<endl;
    Sleep(2000);
}

void saveUsersToFile(const vector <User> &users){
    fstream saveFile("users.txt", ios::out);
    if(!saveFile.is_open()) {
        cout<<"Blad otwarcia pliku do zapisu"<<endl;
        return;
    }

    vector <User> :: const_iterator itr = users.begin();
    for(itr ; itr != users.end() ; ++itr) {
        saveFile << itr->userID << "|";
        saveFile << itr->name << "|";
        saveFile << itr->password << endl;
    }
    saveFile.close();
}

