#include <cctype>
#include <iostream>
#include <string>

using namespace std;

bool is_valid_message(const string &text) {
    for (char c : text) {
        if (!isalpha(static_cast<unsigned char>(c)) && c != ' ') {
            return false;
        }
    }

    return true;
}

char shift_char(char c, int shift) {
    if (c == ' ') {
        return c;
    }

    if (!isalpha(static_cast<unsigned char>(c))) {
        return c;
    }

    shift = (shift % 26 + 26) % 26;

    char base = isupper(static_cast<unsigned char>(c)) ? 'A' : 'a';

    return static_cast<char>(
        (c - base + shift) % 26 + base
    );
}

string caesar_encrypt(const string &plaintext, int shift) {
    string ciphertext;
    ciphertext.reserve(plaintext.size());

    for (char c : plaintext) {
        ciphertext += shift_char(c, shift);
    }

    return ciphertext;
}

string caesar_decrypt(const string &ciphertext, int shift) {
    return caesar_encrypt(ciphertext, -shift);
}

int main() {
    cout << "=== Caesar Cipher Demo ===\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Choose: ";

    int choice;

    if (!(cin >> choice)) {
        cout << "Invalid choice.\n";
        return 0;
    }

    cin.ignore();

    string message;
    int shift;

    cout << "Enter message: ";
    getline(cin, message);

    cout << "Enter key: ";

    if (!(cin >> shift)) {
        cout << "Invalid key.\n";
        return 0;
    }

    if (!is_valid_message(message)) {
        cout << "Invalid input. Only letters and spaces are allowed.\n";
        return 0;
    }

    if (choice == 1) {
        cout << "Ciphertext: "
             << caesar_encrypt(message, shift)
             << "\n";
    }
    else if (choice == 2) {
        cout << "Plaintext: "
             << caesar_decrypt(message, shift)
             << "\n";
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
