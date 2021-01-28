#include <iostream>

using namespace std;

bool hasBadLength(string str)
{
    const string::size_type strLength = 26;
    return str.length() != strLength;
}

bool hasBadCharacters(string str)
{
    const char a = 'a', z = 'z';

    for (int i = 0; static_cast<string::size_type>(i) < str.length(); i++) {
        char strChar = str.at(i);
        if (strChar < a || strChar > z) {
            return true;
        }
    }
    return false;
}

bool missingCharacter(string str)
{
    for (char strChar = 'a'; strChar <= 'z'; strChar++) {
        string::size_type location = 0;
        location = str.find(strChar);
        if (location == string::npos) {
            // Could not find a letter from a-z in str
            return true;
        }
    }

    return false;
}

/*
* A function that encrypts string with a given key
*
*@param str Text to be encrypted
*@param key key to be used for the encryption
*
*@returns string
*/
string encryptStr(string str, string key)
{
    string encryptedStr = "";

    for (int i = 0; static_cast<string::size_type>(i) < str.length(); i++) {
        char originalChar = str.at(i); // Get the char at current index
        string::size_type keyIndex = static_cast<string::size_type>(originalChar - 'a'); // Get key index
        encryptedStr += key.substr(keyIndex, 1); // Append key value to text
    }

    return encryptedStr;
}

int main()
{
    string key = "";
    cout << "Enter the encryption key: ";
    cin >> key;

    if (hasBadLength(key)) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    if (hasBadCharacters(key)) {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    if (missingCharacter(key)) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }
    string text = "";
    cout << "Enter the text to be encrypted: ";
    cin >> text;

    if (hasBadCharacters(text)) {
        cout << "Error! The encryption text must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    string encryptedText = encryptStr(text, key);
    cout << "Encrypted text: " << encryptedText << endl;

    return EXIT_SUCCESS;
}
