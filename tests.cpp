/*
 * File: tests.cpp
 * Name: Hiba Mirza
 * NetID: hmirz4
 * Course: CS 251 Data Structures (21814) 2024 Summer
 * Program Overview: Uses an array to store terms with associated weights. Supports sorting by 
 * lexicographic order and weight, and provides methods to find and count terms starting with a given 
 * prefix.
 */

#include <iostream>
#include "AutocompleteList.h"

using namespace std;

// Tests getSize() on first constructor
bool size_test1() {
    AutocompleteList  list;  // empty list
    if (list.getSize() == 0) {
        return true;
    }
    return false;
}
// Tests getSize() on second constructor
bool size_test2() {
    int n = 10;
    AutocompleteList  list(n);  // empty list
    if (list.getSize() == 10) {
        return true;
    }
    return false;
}

// Tests sortByLexOrder()
bool sort_lex_test() {
    Term terms[] = {{"banana", 1}, {"apple", 2}, {"orange", 3}};
    AutocompleteList list(3);
    for (int i = 0; i < 3; i++) {
        list[i] = terms[i];
    }
    list.sortByLexOrder();
    return list[0].query == "apple" && list[1].query == "banana" && list[2].query == "orange";
}

// Tests sortByWeightOrder()
bool sort_weight_test() {
    Term terms[] = {{"banana", 1}, {"apple", 2}, {"orange", 3}};
    AutocompleteList list(3);
    for (int i = 0; i < 3; i++) {
        list[i] = terms[i];
    }
    list.sortByWeightOrder();
    return list[0].weight == 1 && list[1].weight == 2 && list[2].weight == 1;
}

// Tests numberOfMatches()
bool number_of_matches_test() {
    Term terms[] = {{"banana", 1}, {"apple", 2}, {"apricot", 3}};
    AutocompleteList list(3);
    for (int i = 0; i < 3; i++) {
        list[i] = terms[i];
    }
    list.sortByLexOrder();
    return list.numberOfMatches("ap") == 2 && list.numberOfMatches("banana") == 1 && list.numberOfMatches("z") == 0;
}

// Tests numberOfMatches()
bool all_matches_test() {
    Term terms[] = {{"banana", 1}, {"apple", 2}, {"apricot", 3}};
    AutocompleteList list(3);
    for (int i = 0; i < 3; i++) {
        list[i] = terms[i];
    }
    list.sortByLexOrder();
    AutocompleteList matches = list.allMatches("ap");
    return matches.getSize() == 2 && matches[0].query == "apricot" && matches[1].query == "apple";
}

// Tests third constructor
bool file_constructor_test() {
    AutocompleteList list(tiny.txt");
    return list.getSize() == 3;
}

// Tests copy constructor
bool copy_constructor_test() {
    Term terms[] = {{"banana", 1}, {"apple", 2}, {"orange", 3}};
    AutocompleteList list(3);
    for (int i = 0; i < 3; i++) {
        list[i] = terms[i];
    }
    list.sortByLexOrder();
    AutocompleteList matches = list.allMatches("ap");
    return matches.getSize() == 2 && matches[0].query == "apricot" && matches[1].query == "apple";
}

// Tests copy operator
bool copy_operator_test() {
    Term terms[] = {{"banana", 1}, {"apple", 2}, {"orange", 3}};
    AutocompleteList list(3);
    for (int i = 0; i < 3; i++) {
        list[i] = terms[i];
    }
    AutocompleteList copy = list;
    return copy.getSize() == 3 && copy[0].query == "banana" && copy[1].query == "apple" && copy[2].query == "orange";
}

// Tests print
bool print_test() {
    Term terms[] = {{"banana", 1}, {"apple", 2}, {"orange", 3}};
    AutocompleteList list(3);
    for (int i = 0; i < 3; i++) {
        list[i] = terms[i];
    }
    list.print();
    return true;    
}

int main() {
    // TODO:  Write lots of tests.  Here are two very simple examples.
    // You need to write a lot more than this.
    int passed = 0;
    int failed = 0;
    // Run tests
    if (size_test1()) {
        passed++;
    } else {
        cout << "size_test1 failed" << endl;
        failed++;
    }
    if (size_test2()) {
        passed++;
    } else {
        cout << "size_test2 failed" << endl;
        failed++;
    }
    if (size_test2()) {
        passed++;
    } else {
        cout << "size_test2 failed" << endl;
        failed++;
    }
    if (sort_lex_test()) {
        passed++;
    } else {
        cout << "sort_lex_test failed" << endl;
        failed++;
    }
    if (sort_weight_test()) {
        passed++;
    } else {
        cout << "sort_weight_test failed" << endl;
        failed++;
    }
    if (number_of_matches_test()) {
        passed++;
    } else {
        cout << "number_of_matches_test failed" << endl;
        failed++;
    }
    if (all_matches_test()) {
        passed++;
    } else {
        cout << "all_matches_test failed" << endl;
        failed++;
    }
    if (file_constructor_test()) {
        passed++;
    } else {
        cout << "file_constructor_test failed" << endl;
        failed++;
    }
    if (copy_constructor_test()) {
        passed++;
    } else {
        cout << "copy_constructor_test failed" << endl;
        failed++;
    }
    if (copy_operator_test()) {
        passed++;
    } else {
        cout << "copy_operator_test failed" << endl;
        failed++;
    }
    if (print_test()) {
        passed++;
    } else {
        cout << "print_test failed" << endl;
        failed++;
    }

    cout << "Tests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;
    return 0;
}
