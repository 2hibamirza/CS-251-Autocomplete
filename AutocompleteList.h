/*
 * File: AutocompleteList.h
 * Name: Hiba Mirza
 * NetID: hmirz4
 * Course: CS 251 Data Structures (21814) 2024 Summer
 * Program Overview: Uses an array to store terms with associated weights. Supports sorting by 
 * lexicographic order and weight, and provides methods to find and count terms starting with a given 
 * prefix.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
};

//
// AutocompleteList
//
class AutocompleteList {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted

    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //

    int firstIndexOf(string prefix) {
        int low = 0;
        int high = size - 1;
        int start = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (terms[mid].query.compare(0, prefix.size(), prefix) >= 0) {
                high = mid - 1;
                if (terms[mid].query.compare(0, prefix.size(), prefix) == 0) {
                    start = mid;
                }
            } else {
                low = mid + 1;
            }
        }

        return start;
    }

    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int lastIndexOf(string prefix) {
        int low = 0;
        int high = size - 1;
        int end = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (terms[mid].query.compare(0, prefix.size(), prefix) <= 0) {
                low = mid + 1;
                if (terms[mid].query.compare(0, prefix.size(), prefix) == 0) {
                    end = mid;
                }
            } else {
                high = mid - 1;
            }
        }

        return end;
    }

    //
    // Private member function.
    // This function sorts the terms array by lexicographic order of the query
    // string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByLexOrder() {
        sort(terms, terms + getSize(), [](const Term& x, const Term& y) { 
            return x.query < y.query; 
        });
        sortType = "lex";
    }
    //
    // Private member function.
    // This function sorts the terms array by decreasing weight order.
    // Set the sortType to "weight".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByWeightOrder() {
        sort(terms, terms + getSize(), [](const Term& x, const Term& y) { 
            return x.weight > y.weight; 
        });
        sortType = "weight";
    }

 public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList() {
        size = 0;
        terms = nullptr;
        sortType = "none";
    }

    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList(int n) {
        size = n;
        terms = new Term[size];
        sortType = "none";
    }

    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    AutocompleteList(string filename) {
        ifstream infile(filename);

        string header;
        getline(infile, header);
        size = stoi(header);
        terms = new Term[size];

        for (int i = 0; i < size; i++) {
            string fileWeight;
            infile >> fileWeight;
            terms[i].weight = stoll(fileWeight);
            infile.ignore(1, '\t');
            getline(infile, terms[i].query);
        }

        sortByLexOrder();
        sortType = "lex";
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        size = other.size;
        terms = new Term[size];
        for (int i = 0; i < size; i++) {
            terms[i] = other.terms[i];
        }
    }

    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList& operator=(const AutocompleteList& other) {
        // so starter code compiles
        if (this == &other)
            return *this;

        delete[] terms;

        size = other.size;
        terms = new Term[size];
        sortType = other.sortType;

        for (int i = 0; i < size; i++) {
            terms[i] = other.terms[i];
        }

        return *this;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    virtual ~AutocompleteList() {
        delete[] terms;
    }

    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() const {
        return size;
    }

    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        if (i < 0 || i >= size) {
            throw out_of_range("AutocompleteList: i out of bounds");
        }
        return terms[i];
    }
    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        if (prefix.empty() || sortType != "lex") {
            return AutocompleteList(0);
        }

        int start = firstIndexOf(prefix);
        if (start == -1) {
            return AutocompleteList(0);
        }

        int end = lastIndexOf(prefix);
        int numMatches =  end - start + 1;

        AutocompleteList result(numMatches);
        for (int i = 0; i < numMatches; i++) {
            result.terms[i] = terms[start + i];
        }

        result.sortByWeightOrder();
        result.sortType = "weight";
        return result;
    }
    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        if (prefix.empty() || sortType != "lex") {
            return 0;
        }

        int first = firstIndexOf(prefix);
        if (first == -1) {
            return 0;
        }

        int last = lastIndexOf(prefix);
        if (last == -1) {
            return 0;
        }

        return last - first + 1;
    }
    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    void print() const {
        for (int i = 0; i < getSize(); i++) {
            cout << "        " << terms[i].query << "," << terms[i].weight << endl;
        }
    }
};