#include <iostream>
#include <iomanip>
#include <cstring>
#include<fstream>

using namespace std;

const int MAX_CONTACTS = 100;

// Structure to store contact information
struct Contact {
    char name[50];
    char phone[20];
    char email[50];
};

Contact addressBook[MAX_CONTACTS];
int numberOfContacts = 0;

// Function to add a contact to the address book
void addContact() {
    try {
        if (numberOfContacts < MAX_CONTACTS) {
            cout << "Enter the name: ";
            cin.ignore(); // Ignore newline character from previous input
            cin.getline(addressBook[numberOfContacts].name, sizeof(addressBook[numberOfContacts].name));

            cout << "Enter the phone number: ";
            cin >> addressBook[numberOfContacts].phone;

            cout << "Enter the email address: ";
            cin >> addressBook[numberOfContacts].email;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw "Invalid input. Please enter valid data.";
            }

            
            
            // Writing contact information to the file
            ofstream outfile("C:\\Users\\TOSHIBA\\Desktop\\addressbook.txt", ios::app);
            if (!outfile) {
                cout << "Error: Unable to open the file for writing." << endl;
                return;
            }

            outfile << addressBook[numberOfContacts].name << " "
                    << addressBook[numberOfContacts].phone << " "
                    << addressBook[numberOfContacts].email << endl;

            outfile.close();

            cout << "Contact added successfully!" << endl;
            numberOfContacts++;
        } else {
            throw "Address book is full. Cannot add more contacts.";
        }
    } catch (const char* errorMsg) {
        cout << "Error: " << errorMsg << endl;
    }
    
}

void loadContactsFromFile() {
    ifstream infile("C:\\Users\\TOSHIBA\\Desktop\\addressbook.txt");
    if (!infile) {  // Check if the file opening failed
        cout << "Error: Unable to open the file for reading." << endl;
        return;
    }

    while (infile >> addressBook[numberOfContacts].name >> addressBook[numberOfContacts].phone >> addressBook[numberOfContacts].email) {
        numberOfContacts++;
        if (numberOfContacts >= MAX_CONTACTS) {
            cout << "Warning: Maximum number of contacts reached." << endl;
            break;
        }
    }

    infile.close();
}

// Function to delete a contact from the address book
void deleteContact() {
    try {
        if (numberOfContacts == 0) {
            throw "Address book is empty. No contacts to delete.";
        }

        char deleteName[50];
        cout << "Enter the name of the contact you want to delete: ";
        cin.ignore();
        cin.getline(deleteName, sizeof(deleteName));

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            throw "Invalid input. Please enter a valid name.";
        }

        bool contactFound = false;
        for (int i = 0; i < numberOfContacts; ++i) {
            if (strcmp(addressBook[i].name, deleteName) == 0) {
                for (int j = i; j < numberOfContacts - 1; ++j) {
                    addressBook[j] = addressBook[j + 1];
                }
                numberOfContacts--;
                contactFound = true;
                cout << "Contact deleted successfully!" << endl;
                break;
            }
        }

        if (!contactFound) {
            throw "Contact not found. Cannot delete.";
        }
    } catch (const char* errorMsg) {
        cout << "Error: " << errorMsg << endl;
    }
}

// Function to update the phone number or email address of an existing contact
void updateContact() {
    try {
        if (numberOfContacts == 0) {
            throw "Address book is empty. No contacts to update.";
        }

        char updateName[50];
        cout << "Enter the name of the contact you want to update: ";
        cin.ignore();
        cin.getline(updateName, sizeof(updateName));

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            throw "Invalid input. Please enter a valid name.";
        }

        bool contactFound = false;
        for (int i = 0; i < numberOfContacts; ++i) {
            if (strcmp(addressBook[i].name, updateName) == 0) {
                cout << "Enter the new phone number: ";
                cin >> addressBook[i].phone;

                cout << "Enter the new email address: ";
                cin >> addressBook[i].email;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw "Invalid input. Please enter valid data.";
                }

                cout << "Contact updated successfully!" << endl;
                contactFound = true;
                break;
            }
        }

        if (!contactFound) {
            throw "Contact not found. Cannot update.";
        }
    } catch (const char* errorMsg) {
        cout << "Error: " << errorMsg << endl;
    }
}

// Function to view detailed information about a specific contact
void viewDetailedContact() {
    try {
        if (numberOfContacts == 0) {
            throw "Address book is empty. No contacts to view.";
        }

        char viewName[50];
        cout << "Enter the name of the contact you want to view: ";
        cin.ignore();
        cin.getline(viewName, sizeof(viewName));

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            throw "Invalid input. Please enter a valid name.";
        }

        bool contactFound = false;
        for (int i = 0; i < numberOfContacts; ++i) {
            if (strcmp(addressBook[i].name, viewName) == 0) {
                cout << "Contact details:" << endl;
                cout << setw(10) << "Name:" << addressBook[i].name << endl;
                cout << setw(10) << "Phone: " << addressBook[i].phone << endl;
                cout << setw(10) << "Email: " << addressBook[i].email << endl;
                contactFound = true;
                break;
            }
        }

        if (!contactFound) {
            throw "Contact not found. Cannot view details.";
        }
    } catch (const char* errorMsg) {
        cout << "Error: " << errorMsg << endl;
    }
}

// Function to sort contacts alphabetically based on their names (bubble sort)
void sortContacts() {
    try {
        if (numberOfContacts == 0) {
            throw "Address book is empty. No contacts to sort.";
        }

        for (int i = 0; i < numberOfContacts - 1; ++i) {
            for (int j = 0; j < numberOfContacts - i - 1; ++j) {
                if (strcmp(addressBook[j].name, addressBook[j + 1].name) > 0) {
                    swap(addressBook[j], addressBook[j + 1]);
                }
            }
        }

        cout << "Contacts sorted alphabetically." << endl;
    } catch (const char* errorMsg) {
        cout << "Error: " << errorMsg << endl;
    }
}

// Function to show the total number of contacts in the address book
void showTotalContacts() {
    cout << "Total number of contacts: " << numberOfContacts << endl;
}

// Function to delete all contacts from the address book
void deleteAllContacts() {
    numberOfContacts = 0;
    cout << "All contacts deleted successfully!" << endl;
}

// Function to extend the search option to allow users to search for contacts by phone number or email address
void extendedSearch() {
    try {
        if (numberOfContacts == 0) {
            throw "Address book is empty. No contacts to search.";
        }

        cout << "Enter the phone number or email address to search: ";
        char searchTerm[50];
        cin.ignore();
        cin.getline(searchTerm, sizeof(searchTerm));

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            throw "Invalid input. Please enter a valid search term.";
        }

        bool contactFound = false;
        for (int i = 0; i < numberOfContacts; ++i) {
            if (strcmp(addressBook[i].phone, searchTerm) == 0 || strcmp(addressBook[i].email, searchTerm) == 0) {
                cout << "Contact found:" << endl;
                cout << setw(10) << "Name:" << addressBook[i].name << endl;
                cout << setw(10) << "Phone: " << addressBook[i].phone << endl;
                cout << setw(10) << "Email: " << addressBook[i].email << endl;
                contactFound = true;
                break;
            }
        }

        if (!contactFound) {
            cout << "Contact not found." << endl;
        }
    } catch (const char* errorMsg) {
        cout << "Error: " << errorMsg << endl;
    }
}
void viewAllContacts(){
	try {
        if (numberOfContacts == 0) {
            throw "Address book is empty. No contacts to view.";
        }
	 if (numberOfContacts == 0) {
        cout << "Address book is empty." << endl;
    } else {
        cout << "Contacts in the address book:" << endl;
        for (int i = 0; i < numberOfContacts; ++i) {
            cout << setw(10) << "Name:" << addressBook[i].name <<endl;
            cout << setw(10) << "Phone: " << addressBook[i].phone << endl;
            cout << setw(10) << "Email: " << addressBook[i].email <<endl;
            cout << endl;
        }
    }
}
catch(const char* errorMsg){
	cout<<"Error :"<<errorMsg;
}
}

int main() {
    cout << "Welcome to the Address Book!" << endl;
     
    loadContactsFromFile();
    
    

    while (true) {
        cout << "\nAddress Book Menu:" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Delete Contact" << endl;
        cout << "3. Update Contact" << endl;
        cout << "4. View Detailed Contact" << endl;
        cout << "5. Sort Contacts" << endl;
        cout << "6. Show Total Contacts" << endl;
        cout << "7. Delete All Contacts" << endl;
        cout << "8. Extended Search" << endl;
        cout << "9. viewAllContacts" << endl;

        int choice;
        cout << "Enter your choice (1-9): ";
        cin >> choice;

        try {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw "Invalid input. Please enter a valid choice.";
            }

            switch (choice) {
                case 1:
                    addContact();
                    break;
                case 2:
                    deleteContact();
                    break;
                case 3:
                    updateContact();
                    break;
                case 4:
                    viewDetailedContact();
                    break;
                case 5:
                    sortContacts();
                    break;
                case 6:
                    showTotalContacts();
                    break;
                case 7:
                    deleteAllContacts();
                    break;
                case 8:
                    extendedSearch();
                    break;
                case 9:
                	viewAllContacts();
                    break;
                default:
                    throw "Invalid choice. Please enter a number between 1 and 9.";
            }
        } catch (const char* errorMsg) {
            cout << "Error: " << errorMsg << endl;
        }
    }

    return 0;
}

