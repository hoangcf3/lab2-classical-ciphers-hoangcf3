#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_valid_message(const string &text) {
    for (char c : text) {
        if (!isalpha(static_cast<unsigned char>(c)) && c != ' ') {
            return false;
        }
    }
    return true;
}

string rail_fence_encrypt(const string &plaintext, int rails) {
    if (rails <= 1 || plaintext.empty() || static_cast<int>(plaintext.length()) <= rails) {
        return plaintext;
    }

    vector<string> fence(rails, "");
    int rail = 0;
    int direction = 1;

    for (char c : plaintext) {
        fence[rail] += c;

        if (rail == 0) {
            direction = 1;
        } else if (rail == rails - 1) {
            direction = -1;
        }

        rail += direction;
    }

    string ciphertext;

    for (const string &row : fence) {
        ciphertext += row;
    }

    return ciphertext;
}

string rail_fence_decrypt(const string &ciphertext, int rails) {
    if (rails <= 1 || ciphertext.empty() || static_cast<int>(ciphertext.length()) <= rails) {
        return ciphertext;
    }

    int len = ciphertext.length();
    vector<vector<char>> fence(rails, vector<char>(len, '\n'));

    int rail = 0;
    int direction = 1;

    for (int i = 0; i < len; ++i) {
        fence[rail][i] = '*';

        if (rail == 0) {
            direction = 1;
        } else if (rail == rails - 1) {
            direction = -1;
        }

        rail += direction;
    }

    int index = 0;

    for (int r = 0; r < rails; ++r) {
        for (int c = 0; c < len; ++c) {
            if (fence[r][c] == '*' && index < len) {
                fence[r][c] = ciphertext[index++];
            }
        }
    }

    string plaintext;
    plaintext.reserve(len);

    rail = 0;
    direction = 1;

    for (int i = 0; i < len; ++i) {
        if (fence[rail][i] != '\n') {
            plaintext += fence[rail][i];
        }

        if (rail == 0) {
            direction = 1;
        } else if (rail == rails - 1) {
            direction = -1;
        }

        rail += direction;
    }

    return plaintext;
}

string read_message_from_file(const string &path) {
    ifstream fin(path);
    string line;

    if (fin.is_open()) {
        getline(fin, line);
        fin.close();
    }

    return line;
}

int main() {
    cout << "=== Rail Fence Cipher Demo ===\n";
    cout << "1. Encrypt\n2. Decrypt\n3. Read from file and encrypt\nChoose: ";

    int choice;

    if (!(cin >> choice)) {
        cout << "Invalid choice.\n";
        return 0;
    }

    cin.ignore();

    string message;
    int rails;

    if (choice == 3) {
        message = read_message_from_file("data/input.txt");
        cout << "Message from file: " << message << "\n";
    } else {
        cout << "Enter message: ";
        getline(cin, message);
    }

    cout << "Enter rails: ";

    if (!(cin >> rails)) {
        cout << "Invalid rails.\n";
        return 0;
    }

    if (!is_valid_message(message)) {
        cout << "Invalid input. Only letters and spaces are allowed.\n";
        return 0;
    }

    if (choice == 1 || choice == 3) {
        cout << "Ciphertext: " << rail_fence_encrypt(message, rails) << "\n";
    } else if (choice == 2) {
        cout << "Plaintext: " << rail_fence_decrypt(message, rails) << "\n";
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
