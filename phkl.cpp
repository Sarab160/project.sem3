#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct node {
    string name;
    string number;
    node* next;
};
node* head = NULL, * newnode, * temp;

class phone {
public:
    int contactlength = 0;
    const string filename = "contacts.txt";
    const string password = "12345"; 

    
    phone() {
        loadContacts();
    }

    
    ~phone() {
        saveContacts();
    }

    void createnode() {
        newnode = new node;
        cout << "Enter the name:  ";
        cin >> newnode->name;
        cout << "Enter the number:  ";
        cin >> newnode->number;
        newnode->next = NULL;
        if (head == NULL) {
            head = newnode;
            temp = newnode;
        }
        else {
            temp->next = newnode;
            temp = newnode;
        }
    }

    void display() {
        contactlength = 0;
        if (head == NULL) {
            cout << "Contact list is empty" << endl;
        }
        else {
            node* data = head;
            while (data != NULL) {
                cout << "Name: " << data->name << endl;
                cout << "Number: " << data->number << endl;
                data = data->next;
                contactlength++;
            }
            cout << "Total contacts = " << contactlength << endl;
        }
    }

    void search() {
        node* searchnode = head;
        string srch;
        int count = 1;
        cout << "Enter a contact (name or number) to search: ";
        cin >> srch;
        bool found = false;
        if (head == NULL) {
            cout << "Contact list is empty" << endl;
        }
        else {
            while (searchnode != NULL) {
                if (srch == searchnode->name || srch == searchnode->number) {
                    cout << "Name: " << searchnode->name << endl;
                    cout << "Number: " << searchnode->number << endl;
                    found = true;
                    break;
                }
                searchnode = searchnode->next;
                count++;
            }
        }
        if (found) {
            cout << "Contact index: " << count << endl;
        }
        else {
            cout << "Contact not found" << endl;
        }
    }

    void deletion() {
        int position;
        node* nextnode;
        temp = head;
        cout << "Enter the position you want to delete: ";
        cin >> position;
        if (head == NULL) {
            cout << "List is empty" << endl;
        }
        else if (position > contactlength || position <= 0) {
            cout << "Invalid position" << endl;
        }
        else if (position == 1) {
            temp = head;
            head = head->next;
            delete temp;
        }
        else {
            for (int i = 1; i < position - 1; i++) {
                temp = temp->next;
            }
            nextnode = temp->next;
            temp->next = nextnode->next;
            delete nextnode;
        }
    }

    void clear() {
        if (head == NULL) {
            cout << "List is empty" << endl;
        }
        else {
            node* temp = head;
            while (head != NULL) {
                head = head->next;
                delete temp;
                temp = head;
            }
            cout << "All contacts cleared" << endl;
        }
    }

    void saveContacts() {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving contacts to file." << endl;
            return;
        }
        node* temp = head;
        while (temp != NULL) {
            file << temp->name << " " << temp->number << endl;
            temp = temp->next;
        }
        file.close();
    }

    void loadContacts() {
        ifstream file(filename);
        if (!file) {
            return; 
        }
        while (!file.eof()) {
            newnode = new node;
            file >> newnode->name >> newnode->number;
            if (newnode->name.empty()) {
                delete newnode;
                break;
            }
            newnode->next = NULL;
            if (head == NULL) {
                head = newnode;
                temp = newnode;
            }
            else {
                temp->next = newnode;
                temp = newnode;
            }
        }
        file.close();
    }

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    bool pass() {
       
        string password = "123";
        string inputPassword;
        cout << "Enter password: ";
        cin >> inputPassword;
        return inputPassword == password;
    }

    void menu() {
        cout << "\n1. Add Contact" << endl;
        cout << "2. Display All Contacts" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Delete Contact" << endl;
        cout << "5. Clear All Contacts" << endl;
        cout << "6. Exit" << endl;
    }

    
};

int main() {
    phone p;
    cout << "\n.Name: Muhammad Sarab Rafique" << endl;
    cout << "\n.Roll Number: 23_NTU_CS_1191" << endl;
    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cin.get();
    p.clearScreen();
    if (!p.pass()) {

        cout << "Invalid password. Exiting..." << endl;
        return 0;
    }
    else {
        int op;
        while (true) {
            p.clearScreen();
            p.menu();
            cout << "Choose an option: ";
            cin >> op;
            switch (op) {
            case 1:
                p.createnode();
                break;
            case 2:
                p.display();
                break;
            case 3:
                p.search();
                break;
            case 4:
                p.deletion();
                break;
            case 5:
                p.clear();
                break;
            case 6:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid option! Try again." << endl;
            }
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}
