#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Node structure for linked list
struct Node {
    string website;
    string username;
    string password;
    Node* next;
};

class CrypticKeeper {
private:
    Node* head; // Head of the linked list

    // Vigenere Cipher encryption method
    string vigenereEncrypt(const string& plaintext, const string& key) {
        string ciphertext;
        int keyLength = key.length();
        int textLength = plaintext.length();
        for (int i = 0; i < textLength; ++i) {
            char plainChar = plaintext[i];
            char keyChar = key[i % keyLength];
            char encryptedChar = ((plainChar + keyChar) % 256);
            ciphertext += encryptedChar;
        }
        return ciphertext;
    }

    // Vigenere Cipher decryption method
    string vigenereDecrypt(const string& ciphertext, const string& key) {
        string decryptedText;
        int keyLength = key.length();
        int textLength = ciphertext.length();
        for (int i = 0; i < textLength; ++i) {
            char encryptedChar = ciphertext[i];
            char keyChar = key[i % keyLength];
            char decryptedChar = ((encryptedChar - keyChar + 256) % 256);
            decryptedText += decryptedChar;
        }
        return decryptedText;
    }

public:
    // Constructor
    CrypticKeeper() : head(nullptr) {}

    // Destructor
    ~CrypticKeeper() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Method to add new password entry
    void addEntry(const string& website, const string& username, const string& password, const string& key) {
        string encryptedPassword = vigenereEncrypt(password, key);
        Node* newNode = new Node {website, username, encryptedPassword, nullptr};
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Method to display all password entries
    void displayEntries(const string& key) {
        Node* temp = head;
        while (temp) {
            cout << "Website: " << temp->website << endl;
            cout << "Username: " << temp->username << endl;
            string decryptedPassword = vigenereDecrypt(temp->password, key);
            cout << "Password: " << decryptedPassword << endl;
            cout << endl;
            temp = temp->next;
        }
    }

    // Method to search for password entry by website
    void searchEntry(const string& website, const string& key) {
        Node* temp = head;
        bool found = false;
        while (temp) {
            if (temp->website == website) {
                cout << "Website: " << temp->website << endl;
                cout << "Username: " << temp->username << endl;
                string decryptedPassword = vigenereDecrypt(temp->password, key);
                cout << "Password: " << decryptedPassword << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "Password entry for " << website << " not found." << endl;
        }
    }

    // Method to delete password entry by website
    void deleteEntry(const string& website) {
        if (!head) {
            cout << "Password entries list is empty." << endl;
            return;
        }

        if (head->website == website) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Password entry for " << website << " deleted successfully." << endl;
            return;
        }

        Node* prev = head;
        Node* curr = head->next;
        while (curr) {
            if (curr->website == website) {
                prev->next = curr->next;
                delete curr;
                cout << "Password entry for " << website << " deleted successfully." << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Password entry for " << website << " not found." << endl;
    }
};

int main() {
    CrypticKeeper manager;
    string masterKey;

    // Taking master key input
    cout << "Enter your master key: ";
    cin >> masterKey;
    cin.ignore(); // Clear input buffer

    char choice;
    do {
        cout << "1. Add new password entry\n";
        cout << "2. Display all password entries\n";
        cout << "3. Search for password entry\n";
        cout << "4. Delete password entry\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch(choice) {
            case '1': {
                string website, username, password;
                cout << "Enter website: ";
                getline(cin, website);
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                manager.addEntry(website, username, password, masterKey);
                cout << "Password entry added successfully!\n\n";
                break;
            }
            case '2':
                cout << "\n*** All Password Entries ***\n\n";
                manager.displayEntries(masterKey);
                cout << endl;
                break;
            case '3': {
                string website;
                cout << "Enter website to search: ";
                getline(cin, website);
                manager.searchEntry(website, masterKey);
                cout << endl;
                break;
            }
            case '4': {
                string website;
                cout << "Enter website to delete: ";
                getline(cin, website);
                manager.deleteEntry(website);
                cout << endl;
                break;
            }
            case '5':
                cout << "Exiting CrypticKeeper. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '5');

    return 0;
}

