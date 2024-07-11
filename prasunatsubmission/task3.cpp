#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string email;
};

vector<Contact> contacts;

// Function to load contacts from a file
void loadContacts() {
    ifstream inFile("contacts.txt");
    if (inFile.is_open()) {
        Contact contact;
        while (inFile >> ws, getline(inFile, contact.name) && getline(inFile, contact.phoneNumber) && getline(inFile, contact.email)) {
            contacts.push_back(contact);
        }
        inFile.close();
    }
}

// Function to save contacts to a file
void saveContacts() {
    ofstream outFile("contacts.txt");
    if (outFile.is_open()) {
        for (const auto& contact : contacts) {
            outFile << contact.name << endl;
            outFile << contact.phoneNumber << endl;
            outFile << contact.email << endl;
        }
        outFile.close();
    }
}

// Function to add a new contact
void addContact() {
    Contact newContact;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phoneNumber);
    cout << "Enter email: ";
    getline(cin, newContact.email);
    contacts.push_back(newContact);
    saveContacts();
    cout << "Contact added successfully." << endl;
}

// Function to view all contacts
void viewContacts() {
    if (contacts.empty()) {
        cout << "No contacts available." << endl;
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << "Contact " << i + 1 << ":" << endl;
        cout << "Name: " << contacts[i].name << endl;
        cout << "Phone Number: " << contacts[i].phoneNumber << endl;
        cout << "Email: " << contacts[i].email << endl;
        cout << endl;
    }
}

// Function to edit a contact
void editContact() {
    int index;
    cout << "Enter the contact number to edit: ";
    cin >> index;
    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    Contact& contact = contacts[index - 1];
    cout << "Editing contact " << index << ":" << endl;
    cout << "Enter new name (leave empty to keep current): ";
    cin.ignore();
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        contact.name = newName;
    }

    cout << "Enter new phone number (leave empty to keep current): ";
    string newPhoneNumber;
    getline(cin, newPhoneNumber);
    if (!newPhoneNumber.empty()) {
        contact.phoneNumber = newPhoneNumber;
    }

    cout << "Enter new email (leave empty to keep current): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) {
        contact.email = newEmail;
    }

    saveContacts();
    cout << "Contact updated successfully." << endl;
}

// Function to delete a contact
void deleteContact() {
    int index;
    cout << "Enter the contact number to delete: ";
    cin >> index;
    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    saveContacts();
    cout << "Contact deleted successfully." << endl;
}

int main() {
    loadContacts();
    int choice;
    do {
        cout << "Contact Management System" << endl;
        cout << "1. Add New Contact" << endl;
        cout << "2. View Contacts" << endl;
        cout << "3. Edit Contact" << endl;
        cout << "4. Delete Contact" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
