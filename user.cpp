#include <iostream>
#include <stdlib.h>
#include <limits>
#include <ios>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include "user.h"

using namespace std;

User::User(string n, string pw, int id){
    name = n;
    password = pw;
    userId = id;
}

void User::diplayUserMenu(){
    cout << " --- User menu ---" << endl;
    cout << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zamknij program" << endl;
}

void User::addNewUser(vector <User> &users) {
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
        newUser.userId = 1;
    }
    else{
        vector<User>::iterator itr = users.end();
        itr--;
        newUser.userId = (*itr).userId + 1;
    }

    users.push_back(newUser);
    cout<<endl<<"Uzytkownik dodany"<<endl;
    Sleep(2000);
}

void User::saveUsersToFile(const vector <User> &users){
    fstream saveFile("users.txt", ios::out);
    if(!saveFile.is_open()) {
        cout<<"Blad otwarcia pliku do zapisu"<<endl;
        return;
    }

    vector <User> :: const_iterator citr = users.begin();
    for(citr ; citr != users.end() ; ++citr) {
        saveFile << citr->userId << "|";
        saveFile << citr->name << "|";
        saveFile << citr->password << "|" << endl;
    }
    saveFile.close();
}

void User::loadUsersFromFile(vector <User> &users){
    fstream loadFile("users.txt", ios::in);
    if(!loadFile.is_open()){
        return;
    }

    string loadedData, loadedLine;
    User loadedUser;

    while(getline(loadFile,loadedLine)) {
        for(int i = 0 ; i < 3 ; i++){
            int separatorIndex = findSeparatorIndex(loadedLine);
            loadedData = loadedLine.substr(0,separatorIndex);
            switch(i){
                case 0:
                    loadedUser.userId = (int)loadedData[0] - 48;
                    break;
                case 1:
                    loadedUser.name = loadedData;
                    break;
                case 2:
                    loadedUser.password = loadedData;
                    break;
                default:
                    cout << "Something went wrong with loading from string" << endl;
                    break;
            }
            loadedLine.erase(0,separatorIndex+1);
        }
        users.push_back(loadedUser);
    }
    loadFile.close();
}

int findSeparatorIndex(string text){
    int separatorIndex = 0;
    for(int i = 0 ; i < text.length() ; i++){
        if(text[i] == '|') return separatorIndex;
        separatorIndex++;
    }
    cout << "Couldnt find separator" << endl;
    return 0;
}

User* User::findLoggedUser(vector <User> &users){
    system("cls");
    string login, password;
    cout << "----- LOGOWANIE -----" << endl;
    cout << " Login: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin >> login;
    cout << " Password: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin >> password;

    int registeredUsersNumber = users.size();

    for(int i = 0 ; i < registeredUsersNumber ; i++){
        if(users[i].name == login && users[i].password == password){
            return &users[i];
        }
    }
    return NULL;
}

int User::getUserId(){
    return userId;
}

void User::setPassword(string newPassword){
    password = newPassword;
}
