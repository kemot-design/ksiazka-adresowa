#include <iostream>
#include <fstream>

using namespace std;

struct User {
    string name, password;
    int userID;
};

void diplayUserMeny();

int main()
{
    diplayUserMeny();

    return 0;
}

void diplayUserMeny(){
    cout << " --- User menu ---" << endl;
    cout << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zamknij program" << endl;
}
