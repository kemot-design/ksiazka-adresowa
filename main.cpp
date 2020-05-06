#include <iostream>
#include <stdlib.h>
#include <limits>   //potrrzebne do okreœlenia maksymalnej dlugosci strumienia wejscia cin - podczas czysczenia strumienia
#include <ios>      // potrzebne do <streamsize>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct User {
    string name = "";
    string password = "";
    int userID = 0;
};

void diplayUserMenu();
void addNewUser(vector <User> &users);
void saveUsersToFile(const vector <User> &users);
void loadUsersFromFile(vector <User> &users);
int findSeparatorIndex(string text);
User findLoggedUser(const vector <User> &users);
//void adressBook(User loggedUser);

int main()
{
    vector <User> users;
    loadUsersFromFile(users);
    User loggedUser;

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
            loggedUser = findLoggedUser(users);
            if(loggedUser.userID != 0){
                system("cls");
                system("pause");
            }
            else{
                system("cls");
                cout << "Bledne dane logowania" << endl;
                Sleep(1500);
            }
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

    vector <User> :: const_iterator citr = users.begin();
    for(citr ; citr != users.end() ; ++citr) {
        saveFile << citr->userID << "|";
        saveFile << citr->name << "|";
        saveFile << citr->password << "|" << endl;
    }
    saveFile.close();
}

void loadUsersFromFile(vector <User> &users){
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
                    loadedUser.userID = (int)loadedData[0] - 48;
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

User findLoggedUser(const vector <User> &users){
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
            return users[i];
        }
    }
    User noUser;
    return noUser;
}


