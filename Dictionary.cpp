#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void helpMessage();
void searchDictionary(const string & input);
void loadDictionary(const string & file);
void toLower(string & input);
void trim(string & s);

struct DictionaryEntry {    // Struct for dictionary and it's parameters
    string keyword;
    string partOfSpeech;
    string definition;
};

vector<DictionaryEntry> dictionary; // Array to hold each dictionary entry

int keywordCount = 0;   // Keyword and definition count tracker
int definitionCount = 0;

int main() {
   // string filePath {R"(C:\Users\MickeyMouse\AbsolutePath\DB\Data.CS.SFSU.txt)"};

    string filePath = "Data.CS.SFSU.txt";

    cout << "! Opening data file... " << filePath << endl;

    ifstream fileCheck(filePath);
    while (!fileCheck) { // Loop to verify if file available or can be opened
        cout << "<!>ERROR<!> ===> File could not be opened.\n";
        cout << "<!>ERROR<!> ===> Provided file path: " << filePath << endl;
        cout << "<!>Enter the CORRECT data file path: ";
        cin >> filePath;
        fileCheck.close(); // Closes and reopens file path inputted by user
        fileCheck.open(filePath);
    }

    cout << "! Loading data... " << endl;
    loadDictionary(filePath); // Gathers data from opened file, reading and storing the dictionary entries
    cout << "! Loading completed..." << endl;
    cout << "! Closing data file..." << filePath << endl;
    fileCheck.close();

    cout << "\n====== DICTIONARY 340 C++ =====\n------ Keywords: "
         << keywordCount << "\n------ Definitions: " << definitionCount << endl;

    int searchNum = 1;

    while (true) {  // Loop for search function, processing user's input by calling searchDictionary function
        string input;
        cout << "\nSearch [" << searchNum << "]: ";
        getline(cin, input);
        toLower(input);

        if (input == "!q") {
            cout << "-----THANK YOU-----" << endl;
            break;
        }
        if (input == "!help" || input.empty()) {
            helpMessage();
        } else {
            searchDictionary(input);
        }
        searchNum++;
    }
    return 0;
}

void helpMessage() { // Help message with system instructions
    cout << " |" << endl;
    cout << "  PARAMETER HOW-TO, please enter:" << endl;
    cout << "  1. A search key - then 2. An optional part of speech - then" << endl;
    cout << "  3. An optional 'distinct' - then 4. An optional 'reverse'" << endl;
    cout << " |" << endl;
}
void searchDictionary(const string &input) { // Search function to process user's input
    cout << "|" << endl;

    stringstream ss(input); // String stream to splice user's input
    vector<string> params;
    string param;

    while (ss >> param) { // Store user's input into vector
        params.push_back(param);
    }

    if (params.empty()) { // Outputs help message if there are no parameters inputted
        helpMessage();
        return;
    }

    string keyword = params[0]; // First parameter should be keyword
    string partOfSpeech;

    bool isDistinct = false; // Flags to check if user's input contains distinct or reverse
    bool isReverse = false;

    vector<string> posCheck = { // Storing the parts of speech used within the data file
        "noun", "verb", "adjective", "adverb",
        "conjunction", "preposition", "interjection", "pronoun"
    };

     for (int i = 1; i < static_cast<int>(params.size()); i++) { // Method to check parameters after keyword
        const string& original = params[i]; // Read only reference to original parameters from user's input
        string lowerParam = params[i];
        toLower(lowerParam); // Make parameter lower case

        bool isValidPOS = false; // Check the parameter and if it's valid, using posCheck
        for (const auto & j : posCheck) {
            if (lowerParam == j) {
                isValidPOS = true;
                break;
            }
        }

        if (i == 1 && isValidPOS) { // Checking parameters after the keyword
            partOfSpeech = lowerParam;
        } else if ((i == 1 || i == 2) && lowerParam == "distinct") { // Checking if second or third parameter is distinct
            isDistinct = true;
        } else if ((i == 1 || i == 2 || i == 3) && lowerParam == "reverse") { // Checking if second, third, or fourth parameter is reverse
            isReverse = true;
        } else { // Message that prints if the parameters entered do not match
            cout << "  <The entered parameter '" << original
                 << "' is NOT a part of speech or 'distinct' or 'reverse'.>" << endl;
            cout << "  <The entered parameter '" << original
                 << "' was disregarded.>" << endl;
        }
    }

    string lowerKeyword = keyword;
    toLower(lowerKeyword);

    vector<DictionaryEntry> matches; // Storing matched entries

    for (auto & i : dictionary) { // Loop to check dictionary data
        string dictKeyword = i.keyword;
        string dictPOS = i.partOfSpeech;
        toLower(dictKeyword);
        toLower(dictPOS);

        if (dictKeyword == lowerKeyword) { // Checking if existing keyword matches user's inputted keyword
            if (!partOfSpeech.empty()) {
                if (dictPOS == partOfSpeech) {
                    matches.push_back(i); // If there's a part of speech indicated, only entries with matching part of speech is added
                }
            } else {
                matches.push_back(i); // If none are indicated, adds all entries
            }
        }
    }

    if (isDistinct) { // Method for distinct definitions
        vector<DictionaryEntry> distinctDefs; // Store distinct defs
        for (auto & match : matches) {
            bool added = false;
            for (auto & uniqueDef : distinctDefs) {
                if (match.definition == uniqueDef.definition) { // Checking if definition has been added, stops if it has been
                    added = true;
                    break;
                }
            }
            if (!added) { // If it wasn't added, it gets added to vector
                distinctDefs.push_back(match);
            }
        }
        matches = distinctDefs; // Setting the matches to be outputted to the distinct ones
    }

    vector<string> posList; // Methods for distinct parts of speech
    for (auto & match : matches) {
        string currentPOS = match.partOfSpeech;
        bool added = false;
        for (const auto & j : posList) { // Check if definition with unique part of speech has been added
            if (j == currentPOS) {
                added = true;
                break;
            }
        }
        if (!added) { // Adds part of speech
            posList.push_back(currentPOS);
        }
    }

    for (int i = 0; i < static_cast<int>(posList.size()) - 1; i++) { // Loop to alphabetize output
        for (int j = i + 1; j < static_cast<int>(posList.size()); j++) {
            if (posList[i] > posList[j]) {
                string temp = posList[i];
                posList[i] = posList[j];
                posList[j] = temp;
            }
        }
    }

    vector<DictionaryEntry> sortedResults;  // To store processed entries to output
    for (const auto& currentPOS : posList) { // Checking the parts of speech one by one to alphabetisize and organize output
        vector<DictionaryEntry> tempList;

        for (auto & match : matches) {
            if (match.partOfSpeech == currentPOS) {
                tempList.push_back(match);  // Added to list if matches
            }
        }

        for (int m = 0; m < static_cast<int>(tempList.size()) - 1; m++) { // Sorting the list alphabetically
            for (int n = m + 1; n < static_cast<int>(tempList.size()); n++) { // Bubble sort
                if (tempList[m].definition > tempList[n].definition) {
                    DictionaryEntry temp = tempList[m];
                    tempList[m] = tempList[n];
                    tempList[n] = temp;
                }
            }
        }

        for (const auto & k : tempList) { // Store the organized list to the list for output
            sortedResults.push_back(k);
        }
    }

    if (isReverse) { // Checks if reverse is requested
        for (int i = static_cast<int>(sortedResults.size()) - 1; i >= 0; i--) { // Prints the definitions in reverse
            string capitalizedKey = sortedResults[i].keyword;
            if (!capitalizedKey.empty()) {
                capitalizedKey[0] = toupper(capitalizedKey[0]); // Capitalization for output accuracy
            }
            cout << "  " << capitalizedKey << " [" << sortedResults[i].partOfSpeech << "] : " << sortedResults[i].definition << endl;
        }
    } else {
        for (auto &[keyword, partOfSpeech, definition] : sortedResults) { // Prints definitions
            string capitalizedKey = keyword;
            if (!capitalizedKey.empty()) {
                capitalizedKey[0] = toupper(capitalizedKey[0]);
            }
            cout << "  " << capitalizedKey << " [" << partOfSpeech << "] : " << definition << endl;
        }
    }

    // If input doesn't match any keywords
    if (sortedResults.empty()) {
        cout << "  <NOT FOUND> To be considered for the next release. Thank you." << endl;
    }

    cout << " |";
}

void loadDictionary(const string & file) { // Function to read file and store it in dictionary
    ifstream fileCheck(file); // Opening and reading file
    string line;

    while (getline(fileCheck, line)) { // Looping through lines in file
        if (line.empty()) continue;

        string keyword, word, partOfSpeech, definition;
        stringstream ss(line); // String stream to split line

        getline(ss, keyword, '|'); // Reads line until "|"
        trim(keyword);
        toLower(keyword);

        while (getline(ss, word, '|')) { // Gathering definitions for keyword
            size_t arrow = word.find("-=>>");
            if (arrow == string::npos) continue;

            partOfSpeech = word.substr(0, arrow); // Sets string before the arrow to the part of speech
            definition = word.substr(arrow + 4); // Sets string after arrow as the definition

            trim(partOfSpeech); // Formatting
            toLower(partOfSpeech);
            trim(definition);

            dictionary.push_back({keyword, partOfSpeech, definition}); // Adding a dictionary entry
            definitionCount++;
        }
        keywordCount++;
    }
}

void toLower(string &input) { // Function to help turn string to lower case
    for (char &c : input) {
        c = tolower(c);
    }
}

void ltrim(string &s) { // Functions to trim spaces before and afer
    int i = 0;
    while (i < s.length() && isspace(s[i])) {
        i++;
    }
    s = s.substr(i);
}

void rtrim(string &s) {
    int i = s.length() - 1;
    while (i >= 0 && isspace(s[i])) {
        i--;
    }
    s = s.substr(0, i + 1);
}

void trim(string &s) { // Combines ltrim and rtrim
    ltrim(s);
    rtrim(s);
}

