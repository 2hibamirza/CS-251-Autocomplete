/*
 * File: application.cpp
 * Name: Hiba Mirza
 * NetID: hmirz4
 * Course: CS 251 Data Structures (21814) 2024 Summer
 * Program Overview: Uses an array to store terms with associated weights. Supports sorting by 
 * lexicographic order and weight, and provides methods to find and count terms starting with a given 
 * prefix.
 */

#include <iostream>
#include <string>
#include "AutocompleteList.h"

using namespace std;

void getInput(string &filename, char &mode);
void displayWelcome();
void promptSearch(string &searchQuery);
void displayInstructions();
void getSearchInput(string &searchQuery, int &wordCount);

int main() {
    char mode = ' ';
    string filename, searchQuery, temp = "";

    getInput(filename, mode);
    AutocompleteList autocompleteList(filename);
    int wordCount = 0;

    switch (mode) {
        case 's':
            displayWelcome();
            getline(cin, temp);
            promptSearch(searchQuery);
            while (searchQuery != "#") {
                autocompleteList.allMatches(searchQuery).print();
                promptSearch(searchQuery);
            }
            break;
        case 'c':
            displayInstructions();
            getSearchInput(searchQuery, wordCount);
            while (searchQuery != "#") {
                for (size_t i = 0; i < searchQuery.length(); i++) {
                    string letter = searchQuery.substr(i, 1);
                    cout << "\nPossible Words You Can Make with '" << letter << "' : \n";
                    autocompleteList.allMatches(letter);
                }
                getSearchInput(searchQuery, wordCount);
            }
            break;
    }  
    return 0;
}

void getInput(string &filename, char &mode) {
    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter s-search or c-creative search: ";
    cin >> mode;
}

void displayWelcome() {
    cout << "Welcome!\n";
    cout << "Type your search below, press enter for autocomplete (# to stop).\n";
}

void promptSearch(string &searchQuery) {
    cout << "Search: ";
    getline(cin, searchQuery);
}

void displayInstructions() {
    cout << "\nWelcome to the Scrabble Cheater App!\n";
    cout << "Instructions:\n";
    cout << "1. Enter the letters you have or the word you want to start from.\n";
    cout << "2. Enter the number of words you want to generate.\n";
    cout << "3. The resulting output will be possible words generated based on your input.\n";
}

void getSearchInput(string &searchQuery, int &wordCount) {
    cout << "\nSearch: ";
    cin >> searchQuery;
    if (searchQuery != "#") {
        cout << "How many words do you want to generate: ";
        cin >> wordCount;
    }
}

