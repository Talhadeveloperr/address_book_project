#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include<conio.h>
#include<iomanip>
#include <algorithm> 
#include <map>
#include<windows.h>
#include <ctime>
using namespace std;

string encryptDecrypt(const string& input, const string& key) {
    string output = input;
    for (int i = 0; i < input.size(); ++i)
        output[i] = input[i] ^ key[i % key.size()];
    return output;
}
/*
void checkSimOperator() {
    ifstream file("contacts.txt");
    if (!file) {
        cout << "Error reading from file!" << endl;
        return;
    }

    string name, number, address, email;
    int jazz = 0, zong = 0, warid = 0, ufone = 0, telenor = 0, none = 0;

    while (getline(file, name)) {
        getline(file, number);
        getline(file, address);
        getline(file, email);

        // Extract the first four digits of the number
        string prefix = number.substr(0, 4);

        if (prefix >= "0300" && prefix <= "0309") {
            jazz++;
        }
        else if (prefix >= "0310" && prefix <= "0319") {
            zong++;
        }
        else if (prefix >= "0320" && prefix <= "0329") {
            warid++;
        }
        else if (prefix >= "0330" && prefix <= "0339") {
            ufone++;
        }
        else if (prefix >= "0340" && prefix <= "0349") {
            telenor++;
        }
        else {
            none++;
        }
    }

    file.close();

    // Display the count of numbers per company
    cout << "\nPhone Number Distribution by Operator:" << endl;
    cout << "Jazz: " << jazz << endl;
    cout << "Zong: " << zong << endl;
    cout << "Warid: " << warid << endl;
    cout << "Ufone: " << ufone << endl;
    cout << "Telenor: " << telenor << endl;
    cout << "None: " << none << endl;
}

*/
// Node for Linked List
struct Node {
    string name;
    string number;
    string address;
    string email;
    int birthdayDay;
    int birthdayMonth;
    string birthdayYear;
    string anniversaryDay;
    string anniversaryMonth;
    string anniversaryYear;
    Node* next;
};

// Linked List for Phone Book
class PhoneBook {
private:
    Node* head;

public:
    PhoneBook() { head = nullptr; }
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    void checkSimOperator() {
        ifstream file("contacts.txt");
        if (!file) {
            SetConsoleTextAttribute(h, 4);
            cout << "\t\tError reading from file!" << endl;
            return;
        }

        string name, number, address, email,birthdayYear;
        int birthdayDay, birthdayMonth;
        int jazz = 0, zong = 0, warid = 0, ufone = 0, telenor = 0, none = 0;

        while (getline(file, name)) {
            getline(file, number);
            getline(file, address);
            getline(file, email);
            string birthdayDayStr, birthdayMonthStr; // Temporary strings for conversion
            getline(file, birthdayDayStr);          // Read day as a string
            getline(file, birthdayMonthStr);
            birthdayDay = stoi(birthdayDayStr);
            birthdayMonth = stoi(birthdayMonthStr);
            getline(file, birthdayYear);
            

            // Extract the first four digits of the number
            string prefix = number.substr(0, 4);

            if (prefix >= "0300" && prefix <= "0309") {
                jazz++;
            }
            else if (prefix >= "0310" && prefix <= "0319") {
                zong++;
            }
            else if (prefix >= "0320" && prefix <= "0329") {
                warid++;
            }
            else if (prefix >= "0330" && prefix <= "0339") {
                ufone++;
            }
            else if (prefix >= "0340" && prefix <= "0349") {
                telenor++;
            }
            else {
                none++;
            }
        }

        file.close();
        SetConsoleTextAttribute(h, 1);
        // Display the count of numbers per company
        cout << "\n\t\tPhone Number Distribution by Operator:" << endl;
        cout << "\t\tJazz: " << " " << jazz << endl;
        cout << "\t\tZong: " << " " << zong << endl;
        cout << "\t\tWarid: " << " " << warid << endl;
        cout << "\t\tUfone: " << " " << ufone << endl;
        cout << "\t\tTelenor: " << " " << telenor << endl;
        cout << "\t\tNone: " << " " << none << endl;
    }

    void insertContact(string name, string number, string address, string email, int birthdayDay, int birthdayMonth,
        string birthdayYear) {
        // Check for duplicate name
        if (searchContact(name) != nullptr) {
            cout << "\t\tError: Contact with the name \"" << name << "\" already exists. Please enter a different name." << endl;
            return; // Exit the function if a duplicate is found
        }

        Node* newNode = new Node;
        newNode->name = name;
        newNode->number = number;
        newNode->address = address;
        newNode->email = email;
        newNode->birthdayDay = birthdayDay;
        newNode->birthdayMonth = birthdayMonth;
        newNode->birthdayYear = birthdayYear;

        newNode->next = nullptr;

        if (head == nullptr || head->name >= name) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr && current->next->name < name) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        saveToFile();
    }


    void printContacts() {
        if (head == nullptr) {
            SetConsoleTextAttribute(h, 6);
            cout << "\t\tPhone book is empty!" << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            SetConsoleTextAttribute(h, 9);
            cout << "\t\tName: " << current->name << endl;
            cout << "\t\tNumber: " << current->number << endl;
            cout << "\t\tAddress: " << current->address << endl;
            cout << "\t\tEmail: " << current->email << endl;

            cout << "\t\t-----------------------------" << endl;
            current = current->next;
        }
    }

    Node* searchContact(string name) {
        Node* current = head;
        while (current != nullptr) {
            if (current->name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Not found
    }

    bool modifyContact(string name, string newNumber, string newAddress, string newEmail, int newbirthdayDay,
        int newbirthdayMonth, string newbirthdayYear) {
        Node* contact = searchContact(name);

        if (contact == nullptr) {
            cout << "\t\tError: Contact with the name \"" << name << "\" does not exist. Please enter a valid name." << endl;
            return false; // Exit if the contact is not found
        }

        // Check if the new name already exists as another contact
        if (name != contact->name && searchContact(name) != nullptr) {
            cout << "\t\tError: A contact with the name \"" << name << "\" already exists. Please enter a different name." << endl;
            return false; // Exit if a duplicate is found
        }

        // Update contact details
        contact->number = newNumber;
        contact->address = newAddress;
        contact->email = newEmail;
        contact->birthdayDay = newbirthdayDay;
        contact->birthdayMonth = newbirthdayMonth;
        contact->birthdayYear = newbirthdayYear;

        saveToFile();
        return true;
    }


    bool deleteContact(string name) {
        if (head == nullptr) return false;

        if (head->name == name) {
            Node* temp = head;
            head = head->next;
            delete temp;
            saveToFile();
            return true;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->name != name) {
            current = current->next;
        }

        if (current->next == nullptr) return false; // Not found

        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        saveToFile();
        return true;
    }

    void saveToFile() {
        ofstream file("contacts.txt", ios::trunc);
        if (!file) {
            SetConsoleTextAttribute(h, 4);
            cout << "\t\tError writing to file!" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            file << current->name << endl;
            file << current->number << endl;
            file << current->address << endl;
            file << current->email << endl;
            file << current->birthdayDay << endl;
            file << current->birthdayMonth << endl;
            file << current->birthdayYear << endl;

            current = current->next;
        }
        file.close();
        //cout << "Contacts saved successfully to file!" << endl;
    }

    void loadFromFile() {
        ifstream file("contacts.txt");
        if (!file) {
            SetConsoleTextAttribute(h, 4);
            cout << "\t\tError reading from file!" << endl;
            return;
        }

        string name, number, address, email, birthdayYear;
        int birthdayDay, birthdayMonth;
        while (getline(file, name)) {
            getline(file, number);
            getline(file, address);
            getline(file, email);
            string birthdayDayStr, birthdayMonthStr; // Temporary strings for conversion
            getline(file, birthdayDayStr);          // Read day as a string
            getline(file, birthdayMonthStr);
            birthdayDay = stoi(birthdayDayStr);
            birthdayMonth = stoi(birthdayMonthStr);
            getline(file, birthdayYear);

            insertContact(name, number, address, email, birthdayDay, birthdayMonth, birthdayYear);
        }
        file.close();
        SetConsoleTextAttribute(h, 2);
        cout << "\t\tContacts loaded successfully from file!" << endl;
    }
    void generateBirthdayCards() {
        time_t now = time(0);
        char dt[26]; // ctime_s requires a buffer of at least 26 bytes
        ctime_s(dt, sizeof(dt), &now);  // Get the current time as a string

        // Extract day and month from the string (e.g., "Tue Dec 18 12:34:56 2024")
        int todayDay = dt[8] - '0';  // Extract the first digit of the day
        todayDay = todayDay * 10 + (dt[9] - '0');
        const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
        int todayMonth = 0;
        for (int i = 0; i < 12; ++i) {
            if (strncmp(dt + 4, months[i], 3) == 0) {
                todayMonth = i + 1;  // Months are 1-based (1 for January, 2 for February, etc.)
                break;
            }
        }// Month (0-based, so add 1)
        //int todayDay = dt->tm_mday;
        //int todayMonth = dt->tm_mon + 1;

        bool found = false;
        Node* current = head;
        while (current != nullptr) {
            if (current->birthdayDay == todayDay && current->birthdayMonth == todayMonth) {
                found = true;
                cout << "\n================ BIRTHDAY CARD ================\n";
                cout << "\t\tName: " << current->name << endl;
                cout << "\t\tNumber: " << current->number << endl;
                cout << "\t\tAddress: " << current->address << endl;
                cout << "\t\tEmail: " << current->email << endl;

                cout << "\t\t-----------------------------" << endl;
                cout << "==============================================\n";
            }
            current = current->next;
        }

        if (!found) {
            cout << "\t\tNo birthdays today.\n";
        }
    }


};

// User Node for Linked List
struct User {
    string name;
    string phone;
    string age;
    string password;
    string securityQuestion;
    string address;
    int birthdayDay;
    int birthdayMonth;
    string birthdayYear;
    string Rpass;
    User* next;


};

// User Management System
class UserManager {
private:
    User* head;

public:
    UserManager() { head = nullptr; }

    void registerUser() {
        User* newUser = new User;
        try {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 1);


            do {
                try {
            // Name
            cout << "\t\tEnter Name: ";
            cin.ignore();
            getline(cin, newUser->name);
            if (cin.fail() || newUser->name.length() > 20) {
                cin.clear();
                cin.ignore(100, '\n');
                throw "\t\tInvalid input. Name must be 20 characters or fewer.";
            }
            break;
                }
                catch (const char* errorMsg) {
                    //SetConsoleTextAttribute(h, 4);
                    cout << "\t\tError: " << errorMsg << endl;
                }
            } while (true);


            do {
                try {
            // Phone
            cout << "\t\tEnter Phone: ";
            getline(cin, newUser->phone);
            if (cin.fail() || newUser->phone.length() != 11) {
                cin.clear();
                cin.ignore(100, '\n');
                throw "\t\tInvalid input. Phone must be exactly 11 characters.";
            }
            break;
                }
                catch (const char* errorMsg) {
                   // SetConsoleTextAttribute(h, 4);
                    cout << "\t\tError: " << errorMsg << endl;
                }
            } while (true);


            do {
                try {
            // Age
            cout << "\t\tEnter Age: ";
            cin >> newUser->age;
            if (cin.fail() || newUser->age.length() != 2) {
                cin.clear();
                cin.ignore(100, '\n');
                throw "\t\tInvalid input. Age must be exactly 2 characters.";
            }
            break;
                }
                catch (const char* errorMsg) {
                  //  SetConsoleTextAttribute(h, 4);
                    cout << "\t\tError: " << errorMsg << endl;
                }
            } while (true);


            do {
                try {
            // Password
            cout << "\t\tEnter Password: ";
            string key = "mysecretkey";
            char ch;

            while ((ch = _getch()) != '\r') {
                newUser->password.push_back(ch);
                cout << '*';
            }
            if (newUser->password.length() != 4) {
                throw "\t\tInvalid input. Password must be exactly 4 characters.";
            }

            string encryptedPassword = encryptDecrypt(newUser->password, key);
            newUser->password.clear(); // Clear password after saving
            newUser->password = encryptedPassword;
            break;
                }
                catch (const char* errorMsg) {
                  //  SetConsoleTextAttribute(h, 4);
                    cout << "\t\tError: " << errorMsg << endl;
                }
            } while (true);

            // Security Question
            cout << endl;
            cout << "\t\tEnter Answer to Security Question (Your favorite color): ";
            cin >> newUser->securityQuestion;


            

            do {
                try {
            // Address
            cout << endl;
            cout << "\t\tEnter Address: ";
            cin >> newUser->address;
            
            if (newUser->address.length() > 30) {
                throw "Contact address must not exceed 30 characters.";
            }
            break;
                }
                catch (const char* errorMsg) {
                  //  SetConsoleTextAttribute(h, 4);
                    cout << "\t\tError: " << errorMsg << endl;
                }
            } while (true);

            newUser->next = nullptr;

            // Insert user at the beginning of the list
            newUser->next = head;
            head = newUser;

            saveUsersToFile();
        }
        catch (const char* errorMsg) {
            cout << "\t\tError: " << errorMsg << endl;
            return; // Exit registration process on error
        }

        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 3);
        cout << "\t\tRegistration successful!" << endl;
    }


    bool loginUser(string name, string password) {
        User* current = head;
        while (current != nullptr) {
            if (current->name == name && current->password == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void ChangePassword(string pass) {
        User* curr = head;
        
        
                curr->password = pass;
         
        saveUsersToFile();
    }
    bool recoverPassword(string name, string answer) {
        User* current = head;
        while (current != nullptr) {
            if (current->name == name && current->securityQuestion == answer) {
                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, 5);
                string key = "mysecretkey";
                string encryptedPassword = encryptDecrypt(current->password, key);
                string password = encryptedPassword;
                cout << "\t\tYour password is: " << password << endl;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void saveUsersToFile() {
        ofstream file("users.txt", ios::trunc);
        if (!file) {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 4);
            cout << "\t\tError writing to user file!" << endl;
            return;
        }

        User* current = head;
        while (current != nullptr) {
            file << current->name << endl;
            file << current->phone << endl;
            file << current->age << endl;
            file << current->password << endl;
            file << current->securityQuestion << endl;
            file << current->address << endl;
            current = current->next;
        }
        file.close();
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 8);
        cout << "\t\tUser data saved successfully to file!" << endl;
    }

    void loadUsersFromFile() {
        ifstream file("users.txt");
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!file) {

            SetConsoleTextAttribute(h, 4);
            cout << "\t\tError reading from user file!" << endl;
            return;
        }

        string name, phone, password, securityQuestion, address;
        int age;
        string birthdayDay;
        string birthdayMonth;
        string birthdayYear;

        while (getline(file, name)) {
            getline(file, phone);
            file >> age;
            file.ignore();
            getline(file, password);
            getline(file, securityQuestion);
            getline(file, address);

            User* newUser = new User;
            newUser->name = name;
            newUser->phone = phone;
            newUser->age = age;
            newUser->password = password;
            newUser->securityQuestion = securityQuestion;
            newUser->address = address;

            newUser->next = head;
            head = newUser;
        }
        file.close();
        SetConsoleTextAttribute(h, 6);
        cout << "\t\tUser data loaded successfully from file!" << endl;
    }
};
void Display();
// Main Program
int main() {


    UserManager userManager;
    PhoneBook phoneBook;

    userManager.loadUsersFromFile();
    phoneBook.loadFromFile();
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 9);
    Display();

    int choice;
    do {
        try {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 3);
            cout << "\n\t\t1. Register\n\t\t2. Login\n\t\t3. Forgot Password\n\t\t4. Exit\n\t\tChoose an option: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                throw "Invalid input. Please enter a valid choice.";
            }

            if (choice == 1) {
                userManager.registerUser();
            }

            else if (choice == 2) {



                string name, password;
                do {
                    try {
                        cout << "\t\tEnter Name: ";
                        cin.ignore();
                        getline(cin, name);
                        if (name.length() > 20) {
                            throw "Name must not exceed 20 characters.";
                        }
                        break; // Exit loop if valid
                    }
                    catch (const char* errorMsg) {
                        //SetConsoleTextAttribute(h, 4);
                        cout << "\t\tError: " << errorMsg << endl;
                    }
                } while (true);

                do {
                    try {
                        cout << "\t\tEnter Password: ";
                        password.clear();
                        char ch;
                        while ((ch = _getch()) != '\r') {
                            password.push_back(ch);
                            cout << '*';
                        }
                        cout << endl;

                        if (password.length() != 4) {
                            throw "Password must be exactly 4 characters.";
                        }
                        break; // Exit loop if valid
                    }
                    catch (const char* errorMsg) {
                        //SetConsoleTextAttribute(h, 4);
                        cout << "\t\tError: " << errorMsg << endl;
                    }
                } while (true);

                string encryptedPassword = encryptDecrypt(password, "mysecretkey");
                password = encryptedPassword;


                if (userManager.loginUser(name, password)) {
                    SetConsoleTextAttribute(h, 7);
                    cout << "\n\t\tLogin successful! Welcome to the Phone Book Directory.\n";
                    int phoneChoice;
                    do {
                        SetConsoleTextAttribute(h, 8);
                        cout << "\n\t\tPhone Book Menu:\n";
                        cout << "\t\t1. Add Contact\n\t\t2. View Contacts\n\t\t3. Search Contact\n\t\t4. Modify Contact\n\t\t5. Delete Contact\n\t\t6. Check SIM Operator\n\t\t7. Generate birthday card\n\t\t8. Change Password\n\t\t9. Logout\n\t\tChoose an option: ";
                        cin >> phoneChoice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            throw "Invalid input. Please enter a valid choice.";
                        }

                        if (phoneChoice == 1) {
                            SetConsoleTextAttribute(h, 9);
                            string cname, cnumber, caddress, cemail, cbyear;
                            int cbday, cbmonth;


                            do {
                                try {
                            cout << "\t\tEnter Contact Name: ";
                            cin.ignore();
                            getline(cin, cname);
                            if (cname.length() > 20) {
                                throw "Contact name must not exceed 20 characters.";
                            }
                            break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                            cout << "\t\tEnter Contact Number: ";
                            getline(cin, cnumber);
                            if (cnumber.length() != 11) {
                                throw "Contact number must be exactly 11 characters.";
                            }
                            break;
                                }
                                catch (const char* errorMsg) {
                                   // SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                            cout << "\t\tEnter Contact Address: ";
                            getline(cin, caddress);
                            if (caddress.length() > 30) {
                                throw "Contact address must not exceed 30 characters.";
                            }
                            break;
                                }
                                catch (const char* errorMsg) {
                                   // SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                            cout << "\t\tEnter Contact Email: ";
                            getline(cin, cemail);
                            if (cemail.length() > 30) {
                                throw "Contact email must not exceed 30 characters.";
                            }
                            break;
                                }
                                catch (const char* errorMsg) {
                                   // SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                            cout << "\t\tEnter Birthday Day (1-31): ";
                            string bday;
                            getline(cin, bday);
                            cbday = stoi(bday);
                            if (cbday < 1 || cbday > 31) {
                                throw "Birthday day must be between 1 and 31.";
                            }
                            break;
                                }
                                catch (const char* errorMsg) {
                                 //   SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                            cout << "\t\tEnter Birthday Month (1-12): ";
                            string bmonth;
                            getline(cin, bmonth);
                            cbmonth = stoi(bmonth);
                            if (cbmonth < 1 || cbmonth > 12) {
                                throw "Birthday month must be between 1 and 12.";
                            }
                            break;
                                }
                                catch (const char* errorMsg) {
                                   // SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                            cout << "\t\tEnter Birthday Year (4 digits): ";
                            getline(cin, cbyear);
                            if (cbyear.length() != 4) {
                                throw "Birthday year must be exactly 4 digits.";
                            }
                            break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);

                            phoneBook.insertContact(cname, cnumber, caddress, cemail, cbday, cbmonth, cbyear);
                        }
                        else if (phoneChoice == 2) {
                            phoneBook.printContacts();
                        }
                        else if (phoneChoice == 3) {
                            string cname;
                            SetConsoleTextAttribute(h, 1);
                            cout << "\t\tEnter Contact Name to Search: ";
                            cin.ignore();
                            getline(cin, cname);
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw "Invalid input. Please enter a valid character.";
                            }

                            Node* contact = phoneBook.searchContact(cname);
                            if (contact) {
                                SetConsoleTextAttribute(h, 2);
                                cout << "\t\tContact Found!\n";
                                cout << "\t\tName: " << contact->name << endl;
                                cout << "\t\tNumber: " << contact->number << endl;
                                cout << "\t\tAddress: " << contact->address << endl;
                                cout << "\t\tEmail: " << contact->email << endl;
                            }
                            else {
                                cout << "\t\tContact Not Found!" << endl;
                            }
                        }
                        else if (phoneChoice == 4) {
                            string cname, cnumber, caddress, cemail, cbyear;
                            int cbday, cbmonth;
                            SetConsoleTextAttribute(h, 3);
                            do {
                                try {
                                    cout << "\t\tEnter Contact Name: ";
                                    cin.ignore();
                                    getline(cin, cname);
                                    if (cname.length() > 20) {
                                        throw "Contact name must not exceed 20 characters.";
                                    }
                                    break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                                    cout << "\t\tEnter Contact Number: ";
                                    getline(cin, cnumber);
                                    if (cnumber.length() != 11) {
                                        throw "Contact number must be exactly 11 characters.";
                                    }
                                    break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                                    cout << "\t\tEnter Contact Address: ";
                                    getline(cin, caddress);
                                    if (caddress.length() > 30) {
                                        throw "Contact address must not exceed 30 characters.";
                                    }
                                    break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                                    cout << "\t\tEnter Contact Email: ";
                                    getline(cin, cemail);
                                    if (cemail.length() > 30) {
                                        throw "Contact email must not exceed 30 characters.";
                                    }
                                    break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                                    cout << "\t\tEnter Birthday Day (1-31): ";
                                    string bday;
                                    getline(cin, bday);
                                    cbday = stoi(bday);
                                    if (cbday < 1 || cbday > 31) {
                                        throw "Birthday day must be between 1 and 31.";
                                    }
                                    break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                                    cout << "\t\tEnter Birthday Month (1-12): ";
                                    string bmonth;
                                    getline(cin, bmonth);
                                    cbmonth = stoi(bmonth);
                                    if (cbmonth < 1 || cbmonth > 12) {
                                        throw "Birthday month must be between 1 and 12.";
                                    }
                                    break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);


                            do {
                                try {
                                    cout << "\t\tEnter Birthday Year (4 digits): ";
                                    getline(cin, cbyear);
                                    if (cbyear.length() != 4) {
                                        throw "Birthday year must be exactly 4 digits.";
                                    }
                                    break;
                                }
                                catch (const char* errorMsg) {
                                  //  SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);

                            if (phoneBook.modifyContact(cname, cnumber, caddress, cemail, cbday, cbmonth, cbyear)) {
                                cout << "\t\tContact Modified Successfully!" << endl;
                            }
                            else {
                                cout << "\t\tContact Not Found!" << endl;
                            }
                        }
                        else if (phoneChoice == 5) {
                            string cname;
                            SetConsoleTextAttribute(h, 6);
                            cout << "\t\tEnter Contact Name to Delete: ";
                            cin.ignore();
                            getline(cin, cname);
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                throw "Invalid input. Please enter a valid character.";
                            }

                            if (phoneBook.deleteContact(cname)) {
                                cout << "\t\tContact Deleted Successfully!" << endl;
                            }
                            else {
                                SetConsoleTextAttribute(h, 4);
                                cout << "\t\tContact Not Found!" << endl;
                            }
                        }
                        else if (phoneChoice == 6) {
                            phoneBook.checkSimOperator();
                        }
                        else if (phoneChoice == 7) {
                            phoneBook.generateBirthdayCards();
                        }
                        else if (phoneChoice == 8) {

                          
                            string key = "mysecretkey";
                            do {
                                try {
                            cout << "\t\tEnter new Password" << endl;
                            
                            //password.clear();
                            char ch;
                            string password;
                            while ((ch = _getch()) != '\r') {
                                password.push_back(ch);
                                cout << '*';
                            }

                            if (password.length() != 4) {
                                throw "Password must be exactly 4 characters.";
                            }
                            break; // Exit loop if valid
                                }
                                catch (const char* errorMsg) {
                                    //SetConsoleTextAttribute(h, 4);
                                    cout << "\t\tError: " << errorMsg << endl;
                                }
                            } while (true);
                            string encryptedPassword = encryptDecrypt(password, key);
                            /* ofstream file("users.txt", ios::binary | ios::app);
                             if (!file) {
                                 cout << "\tUnable to open file for writing" << endl;
                                 return;
                             }

                             file << encryptedPassword << endl;
                             file.close();*/
                            password.clear(); // Clear password after saving
                            password = encryptedPassword;
                            userManager.ChangePassword(password);
                            }

                    } while (phoneChoice != 9);
                }
                else {
                    SetConsoleTextAttribute(h, 4);
                    cout << endl;
                    cout << "\t\tLogin failed. Please try again.\n";
                }



            }
            else if (choice == 3) {
                SetConsoleTextAttribute(h, 7);
                string name, answer;
                cout << "\t\tEnter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "\t\tAnswer to Security Question (Your favorite color): ";
                getline(cin, answer);

                if (!userManager.recoverPassword(name, answer)) {
                    cout << "\t\tIncorrect answer or user not found.\n";
                }
            }
            
        }
        catch (const char* errorMsg) {
            //SetConsoleTextAttribute(h, 4);
            cout << "\t\tError: " << errorMsg << endl;
        }

    } while (choice != 4);
    SetConsoleTextAttribute(h, 9);
    cout << "\t\tExiting program. Goodbye!\n";



    return 0;
}
void Display() {
    for (int i = 0; i <= 14; i++) {
        cout << " ";

    }
    for (int j = 0; j <= 24; j++) {
        cout << ":";
    }
    cout << endl;
    for (int k = 1; k != 2; k++) {
        cout << " ";
        for (int l = 0; l <= 13; l++) {
            cout << " ";
        }
        for (int m = 1; m != 2; m++) {
            cout << ":::                   :::";
        }
        cout << endl;
    }
    for (int n = 1; n != 2; n++) {
        cout << " ";
        for (int o = 0; o <= 13; o++) {
            cout << " ";
        }
        for (int p = 1; p != 2; p++) {
            cout << ":::   W E L C O M E   :::          Presented By:";
        }
        cout << endl;
    }

    for (int t = 1; t != 2; t++) {
        cout << " ";
        for (int u = 0; u <= 13; u++) {
            cout << " ";
        }
        for (int v = 1; v != 2; v++) {
            cout << ":::         TO        :::           *Hamza Nazir*";
        }
        cout << endl;
    }
    for (int w = 0; w <= 1; w++) {
        cout << " ";
        for (int x = 0; x <= 13; x++) {
            cout << " ";
        }
        for (int y = 1; y != 2; y++) {
            cout << ":::                   :::";
        }
        cout << endl;
    }


    for (int z = 1; z != 2; z++) {
        cout << " ";
        for (int a = 0; a <= 11; a++) {
            cout << " ";
        }
        for (int b = 1; b != 2; b++) {
            cout << "|````|                 |````|         *Talha Khalid*";
        }
        cout << endl;
    }
    for (int c = 1; c != 2; c++) {
        cout << " ";
        for (int d = 0; d <= 11; d++) {
            cout << " ";
        }
        for (int e = 1; e != 2; e++) {
            cout << "|    |*) PHONE BOOK (* |    |";
        }
        cout << endl;
    }
    for (int f = 1; f != 2; f++) {
        cout << " ";
        for (int g = 0; g <= 11; g++) {
            cout << " ";
        }
        for (int h = 1; h != 2; h++) {
            cout << "|____|_________________|____|";
        }
        cout << endl;
    }


}
