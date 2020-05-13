#include <iostream>

using namespace std;

class User {
public:
    User(string = "", string = "", int = 0);
    void diplayUserMenu();
    void addNewUser(vector <User> &users);
    void saveUsersToFile(const vector <User> &users);
    void loadUsersFromFile(vector <User> &users);
    User* findLoggedUser(vector <User> &users);
    int getUserId();
    void setPassword(string newPassword);

private:
    string name;
    string password;
    int userId;

};

int findSeparatorIndex(string text);
