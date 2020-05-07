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

using namespace std;

struct User {
    string name = "";
    string password = "";
    int userId = 0;
};

struct Recipent {
    string name = "", surname ="", email = "", homeAdress = "", phoneNumber = "";
    int id = 0;
    int userId = 0;
};

void diplayUserMenu();
void addNewUser(vector <User> &users);
void saveUsersToFile(const vector <User> &users);
void loadUsersFromFile(vector <User> &users);
int findSeparatorIndex(string text);
User findLoggedUser(const vector <User> &users);
void adressBookApp(User loggedUser);
void displayMainMenu();
void addNewContact(vector <Recipent> &adressBook, int userId);
void saveModificationsToFile(const vector <Recipent> &adressBook, Recipent modifiedContact, bool recipentToDelete);
void saveNewContactToFile(const vector <Recipent> &adressBook, int userId);
void displayAdressBook(const vector <Recipent> &adressBook);
void displayRecipentData(Recipent recipentToDisplay);
void loadAdressbookFromFile(vector <Recipent> &adressBook, int userId);
int findSeparatorIndex(string text);
void displayRecipentByName(const vector <Recipent> &adressBook);
void displayRecipentBySurname(const vector <Recipent> &adressBook);
void deleteRecipent(vector <Recipent> &adressBook);
void editRecipent(vector <Recipent> &adressBook);
bool isPhoneNumberValid(string word);
bool isEmailAdressValid(string word);
int findBiggestId();
int strToInt(string numberStr);

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
            if(loggedUser.userId != 0){
                system("cls");
                adressBookApp(loggedUser);
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

void saveUsersToFile(const vector <User> &users){
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

void adressBookApp(User loggedUser) {
    vector <Recipent> adressBook;
    int loggedUserId = loggedUser.userId;
    loadAdressbookFromFile(adressBook, loggedUserId);

    int selection = 0;
    while(1) {
        displayMainMenu();
        cin >> selection;

        while(cin.fail()){ //Zabezpiecznie przed wpisaniem innych znakow niz liczby
            cout << "Wpisz liczbe" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cin >> selection;
        }
        switch(selection) {
        case 1:
            addNewContact(adressBook, loggedUserId);
            saveNewContactToFile(adressBook, loggedUserId);
            break;
        case 2:
            displayRecipentByName(adressBook);
            break;
        case 3:
            displayRecipentBySurname(adressBook);
            break;
        case 4:
            displayAdressBook(adressBook);
            break;
        case 5:
            deleteRecipent(adressBook);
            break;
        case 6:
            editRecipent(adressBook);
            break;
        case 9:
            return;
        default:
            cout<<"Nie ma takiej opcji!"<<endl;
            Sleep(2000);
            break;
        }
        system("cls");
    }
}

void displayMainMenu() {
    cout << " --- Ksiazka adresowa ---" << endl;
    cout << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "9. Wyjdz" << endl;
    cout << "Twoj wybor: ";
}

void addNewContact(vector <Recipent> &adressBook, int userId) {
    fstream loadFile("adress_book.txt", ios::in);

    if(!loadFile.is_open()) {
        fstream loadFile("adress_book.txt", ios::out);
        loadFile.close();
    }

    system("cls");
    string name, surname, email, homeAdress, phoneNum;

    cout << "--- Dodaj nowy kontakt ---" << endl << endl;
    cout << "Wpisz imie: ";
    cin.clear();                                        //czyszczenie strumienia wejscia
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,name);
    cout << "Wpisz nazwisko: ";
    getline(cin,surname);
    cout << "Wpisz numer telefonu: ";
    getline(cin,phoneNum);
    while(!isPhoneNumberValid(phoneNum)){
        cout << "Niepoprawny format danych, sprobuj jeszcze raz." << endl;
        cout << "Wpisz numer telefonu: ";
        getline(cin,phoneNum);
    }
    cout << "Wpisz adres email: ";
    getline(cin,email);
    while(!isEmailAdressValid(email)){
        cout << "Niepoprawny format danych, sprobuj jeszcze raz." << endl;
        cout << "Wpisz adres email (x@y.z): ";
        getline(cin,email);
    }
    cout << "Wpisz adres zamieszkania: ";
    getline(cin,homeAdress);

    Recipent newRecipent;
    newRecipent.name = name;
    newRecipent.surname = surname;
    newRecipent.phoneNumber = phoneNum;
    newRecipent.email = email;
    newRecipent.homeAdress = homeAdress;
    newRecipent.userId = userId;
    newRecipent.id = findBiggestId() + 1;

    adressBook.push_back(newRecipent);
    cout<<endl<<"Kontakt dodany"<<endl;
    Sleep(2000);
}

int strToInt(string numberStr){
    stringstream someStrNumber(numberStr);
    int convertedNumber = 0;
    someStrNumber >> convertedNumber;
    return convertedNumber;
}

void saveModificationsToFile(const vector <Recipent> &adressBook, Recipent modifiedContact, bool recipentToDelete){

    fstream loadFile("adress_book.txt", ios::in);
    if(!loadFile.is_open()) {
        cout<<"Blad otwarcia pliku do zapisu"<<endl;
        return;
    }

    fstream tempFile("adresaci_temp.txt",ios::out);
    string loadedData, loadedLine;

    while(getline(loadFile,loadedLine)) {
        for(int i = 0 ; i < 7 ; i++){
            int separatorIndex = findSeparatorIndex(loadedLine);
            loadedData = loadedLine.substr(0,separatorIndex);
            if(recipentToDelete && i == 0 && strToInt(loadedData) == modifiedContact.id){
                break;
            }
            else if(i == 0 && strToInt(loadedData) == modifiedContact.id){
                tempFile << modifiedContact.id << "|";
                tempFile << modifiedContact.userId << "|";
                tempFile << modifiedContact.name << "|";
                tempFile << modifiedContact.surname << "|";
                tempFile << modifiedContact.phoneNumber << "|";
                tempFile << modifiedContact.email << "|";
                tempFile << modifiedContact.homeAdress << "|" << endl;
                i = 6;
            }
            else{
                tempFile << loadedData << "|";
                loadedLine.erase(0,separatorIndex+1);
                if(i == 6)  tempFile << endl;
            }
        }
    }

    loadFile.close();
    tempFile.close();
    remove("adress_book.txt");
    rename("adresaci_temp.txt","adress_book.txt");
}

void saveNewContactToFile(const vector <Recipent> &adressBook, int userId){
    fstream saveFile("adress_book.txt", ios::app);
    if(!saveFile.is_open()) {
        cout<<"Blad otwarcia pliku do zapisu"<<endl;
        return;
    }

    vector <Recipent> :: const_iterator itrToNewestContact = adressBook.end()-1;
    saveFile << itrToNewestContact->id << "|";
    saveFile << itrToNewestContact->userId << "|";
    saveFile << itrToNewestContact->name << "|";
    saveFile << itrToNewestContact->surname << "|";
    saveFile << itrToNewestContact->phoneNumber << "|";
    saveFile << itrToNewestContact->email << "|";
    saveFile << itrToNewestContact->homeAdress << "|";
    saveFile << endl;
    saveFile.close();
}

void displayRecipentData(Recipent recipentToDisplay){
    cout << "Id: "<< recipentToDisplay.id << endl;
    cout << "Imie: "<< recipentToDisplay.name << endl;
    cout << "Nazwisko: "<<recipentToDisplay.surname << endl;
    cout << "Telefon: "<<recipentToDisplay.phoneNumber << endl;
    cout << "Email: "<<recipentToDisplay.email << endl;
    cout << "Adres: "<<recipentToDisplay.homeAdress << endl;
    cout << "-----------------------" << endl;
}

void displayAdressBook(const vector <Recipent> &adressBook){
    system("cls");
    cout<<"--- LISTA KONTAKTOW ---"<<endl<<endl;

    int bookLength = adressBook.size();
    if(bookLength == 0){
        cout << "Ksiazka adresowa jest pusta" ;
        Sleep(1500);
        return;
    }
    for(int i = 0 ; i < bookLength ; i++) {
        displayRecipentData(adressBook[i]);
    }
    system("pause");
}

void loadAdressbookFromFile(vector <Recipent> &adressBook, int userId) {

    fstream loadFile("adress_book.txt", ios::in);

    if(!loadFile.is_open()) {
        return;
    }

    string loadedData, loadedLine;

    while(getline(loadFile,loadedLine)) {
        Recipent loadedRecipent;
        for(int i = 0 ; i < 7 ; i++){
            int separatorIndex = findSeparatorIndex(loadedLine);
            loadedData = loadedLine.substr(0,separatorIndex);
            if(i == 1 && strToInt(loadedData) != userId) break;
            switch(i){
                case 0:
                    loadedRecipent.id = strToInt(loadedData);
                    break;
                case 1:
                    loadedRecipent.userId = strToInt(loadedData);
                    break;
                case 2:
                    loadedRecipent.name = loadedData;
                    break;
                case 3:
                    loadedRecipent.surname = loadedData;
                    break;
                case 4:
                    loadedRecipent.phoneNumber = loadedData;
                    break;
                case 5:
                    loadedRecipent.email = loadedData;
                    break;
                case 6:
                    loadedRecipent.homeAdress = loadedData;
                    break;
                default:
                    cout << "Something wrong with loading from string" << endl;
                    break;
            }
            loadedLine.erase(0,separatorIndex+1);
        }
        if(loadedRecipent.userId != 0){
            adressBook.push_back(loadedRecipent);
        }
    }
    loadFile.close();
}

void displayRecipentByName(const vector <Recipent> &adressBook){
    system("cls");
    if(adressBook.empty()) {
        cout << "Ksiazka adresowa jest pusta" << endl;
        Sleep(2000);
        return;
    }

    string searchData;
    bool isRecipentInAdressbook = false;

    cout << "Podaj imie: ";
    cin >> searchData;

    for(int i = 0 ; i < adressBook.size() ; i++){
        if(adressBook[i].name == searchData) {
            displayRecipentData(adressBook[i]);
            isRecipentInAdressbook = true;
        }
    }
    if(!isRecipentInAdressbook) {
        cout<<"Nie znaleziono kontaktu o takim imieniu"<<endl;
    }
    system("pause");
}

void displayRecipentBySurname(const vector <Recipent> &adressBook){
    system("cls");
    if(adressBook.empty()) {
        cout << "Ksiazka adresowa jest pusta" << endl;
        Sleep(2000);
        return;
    }

    string searchData;
    bool isRecipentInAdressbook = false;

    cout << "Podaj nazwisko: ";
    cin >> searchData;

    for(int i = 0 ; i < adressBook.size() ; i++){
        if(adressBook[i].surname == searchData) {
            displayRecipentData(adressBook[i]);
            isRecipentInAdressbook = true;
        }
    }
    if(!isRecipentInAdressbook) {
        cout<<"Nie znaleziono kontaktu o takim nazwisku"<<endl;
    }
    system("pause");
}

void deleteRecipent(vector <Recipent> &adressBook) {
    system("cls");
    if(adressBook.empty()) {
        cout << "Ksiazka adresowa jest pusta" << endl;
        Sleep(2000);
        return;
    }
    int recipentId;
    cout << "Wpisz id kontaktu do usuniecia: ";
    cin >> recipentId;

    vector <Recipent> :: iterator itr = adressBook.begin();
    for(itr ; itr != adressBook.end() ; ++itr) {
        if(itr->id == recipentId) {
            cout << "Czy na pewno chcesz usunac kontakt " << itr->name << " " << itr->surname << "?\n(wcisnij \"t\" aby potwierdzic, cokolwiek innego by anulowac): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            char confirmation = getchar();
            if(confirmation != 't'){
                cout << "Anulowano probe usuniecia kontaktu" << endl;
                Sleep(1500);
                return;
            }
            saveModificationsToFile(adressBook, *itr, true);
            cout << "Usunieto kontakt: " << itr->name << " " << itr->surname;
            adressBook.erase(itr);
            Sleep(2000);
            return;
        }
    }
    cout << "Nie odnaleziono kontaktu o takim numerze id" << endl;
    Sleep(2000);
}

void editRecipent(vector <Recipent> &adressBook){
    system("cls");

    if(adressBook.empty()) {
        cout << "Ksiazka adresowa jest pusta" << endl;
        Sleep(2000);
        return;
    }

    int recipentId;
    cout<<"--- Edycja kontaktu ---\n\n";
    cout<<"Wpisz id kontaktu do edycji: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin >> recipentId;

    vector <Recipent> :: iterator itr = adressBook.begin();
    for(itr ; itr != adressBook.end() ; ++itr) {
        if(itr->id == recipentId) {
            string changedData;
            int menuSelection;
            while(1) {
                system("cls");
                cout << "--- Edycja kontaktu ---\n\n";
                cout << "Ktore dane chcesz edytowac?"<<endl;
                cout << "1. Imie"<<endl;
                cout << "2. Nazwisko"<<endl;
                cout << "3. Numer telefonu"<<endl;
                cout << "4. Adres email"<<endl;
                cout << "5. Adres zamieszkania"<<endl;
                cout << "6. Zakoncz edycje kontaktu"<<endl;
                cin >> menuSelection;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');

                switch(menuSelection) {
                case 1:
                    cout << endl << "Wprowadz nowe imie: ";
                    getline(cin,changedData);
                    itr->name = changedData;
                    cout << "Imie zostalo zmieniona na " << changedData << endl;
                    Sleep(1500);
                    break;
                case 2:
                    cout << endl << "Wprowadz nowe nazwisko: ";
                    getline(cin,changedData);
                    itr->surname = changedData;
                    cout << "Nazwisko zostalo zmieniona na " << changedData << endl;
                    Sleep(1500);
                    break;
                case 3:
                    cout << endl << "Wprowadz nowy numer telefonu: ";
                    getline(cin,changedData);
                    while(!isPhoneNumberValid(changedData)){
                        cout << "Wprowadzono niepoprawne dane, sprobuj jeszcze raz" << endl;
                        cout << "Wprowadz nowy numer telefonu: ";
                        getline(cin,changedData);
                    }
                    itr->phoneNumber = changedData;
                    cout << "Numer telfonu zostal zmieniony na " << changedData << endl;
                    Sleep(1500);
                    break;
                case 4:
                    cout << endl << "Wprowadz nowy adres email: ";
                    getline(cin,changedData);
                    while(!isEmailAdressValid(changedData)){
                        cout << "Wprowadzono niepoprawne dane, sprobuj jeszcze raz" << endl;
                        cout << "Wprowadz nowy adres email (x@y.z): ";
                        getline(cin,changedData);
                    }
                    itr->email = changedData;
                    cout << "Adres email zostal zmieniony na " << changedData << endl;
                    Sleep(1500);
                    break;
                case 5:
                    cout << endl << "Wprowadz nowy adres zamieszkania: ";
                    getline(cin,changedData);
                    itr->homeAdress = changedData;
                    cout << "Adres zamieszkania zostal zmieniony na " << changedData << endl;
                    Sleep(1500);
                    break;
                case 6:
                    saveModificationsToFile(adressBook, *itr, false);
                    return;
                default:
                    cout<<"Nie ma takiej opcji, wprowadz liczbe od 1 do 6"<<endl;
                    Sleep(2000);
                    break;
                }
                system("cls");
            }
            return;
        }

    }
    cout << "Nie odnaleziono kontaktu o takim id " << endl;
    Sleep(2000);
}

bool isPhoneNumberValid(string word) {
    int wordLength = word.length();
    for(int i = 0 ; i < wordLength ; i++) {
        if(((int)word[i] < 48 || (int)word[i] > 57) && (int)word[i] != 32)
            return false;
    }
    return true;
}

bool isEmailAdressValid(string word) {
    int wordLength = word.length();
    int numberOfAts = 0;
    for(int i = 0 ; i < wordLength ; i++) {
        if(word[i] == '@') {
            numberOfAts++;
        }
        if(word[i] == ' ') {
            return false;
        }
    }
    if(numberOfAts == 1)
        return true;
    return false;
}

int findBiggestId(){
    fstream loadFile("adress_book.txt", ios::in);

    if(!loadFile.is_open()) {
        return 0;
    }

    string loadedLine, loadedData;
    int biggestId = 0;
    while(getline(loadFile,loadedLine)) {
        int separatorIndex = findSeparatorIndex(loadedLine);
        loadedData = loadedLine.substr(0,separatorIndex);
        biggestId = (int)loadedData[0] - 48;
    }
    loadFile.close();
    return biggestId;
}
