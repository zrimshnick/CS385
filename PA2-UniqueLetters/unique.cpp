/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Zachary Rimshnick
 * Date        : 9/28/2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    // will be the variable that dynamically changes and lets program know if a char is not lowercase
    bool lowercase = true;                       

    // loop to check each one
    // will repeat until i is length of string input
    for (size_t i = 0; i < s.length(); i++) {
        // checks to make sure the difference between s[i] and 'a' is between 0 and 25 (means it's lowercase)
        if (((s[i]-'a') >= 0) && ((s[i]-'a') <= 25)) {
            lowercase = true;
        } else {
            lowercase = false; 
            // if not lowercase, print this error message
            cerr << "Error: String must contain only lowercase letters." << endl;
            return lowercase;
        }
    }
    // if the variable is false after the loops complete, give this error message
    if (lowercase == false) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 0;
    } 

    return lowercase;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.

    // vector and setter variables that will provide the int in binary
    unsigned int vector = 0;
    unsigned int setter;
    //  will be the variable that dynamically changes and lets program know if a char is repeated
    bool repeated = false;

    // will repeat until i is length of string input
    for (size_t i = 0; i < s.length(); i++) {
        // setter will shift left by difference of s[i]-'a' (distance between beginning of alphabet and character s[i])
        setter = 1 << (s[i]-'a');

        // if the bitwise AND of vector and setter is 0, then vector changes to become the bitwise OR of vector and setter
        if ((vector & setter) == 0) {
            vector = (vector | setter);
        } else {
            repeated = true; 
        }

    }
    // after loop, if a char has been repeated, then give this error message
    if (repeated == true) {
        cerr << "Duplicate letters found." << endl;
        return repeated;
    } 
    // after loop, if a char has not been repeated, then give this message
    if (repeated == false) {
        cerr << "All letters are unique." << endl;
        return repeated;
    }

    return repeated;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    // if there are 0 inputs, or more than 1 input, give this error message
    if ((argc == 1) || (argc > 2)) {
        cerr << "Usage: ./unique <string>" << endl;
        return 0;
    }

    // runs is_all_lowercase function, and stops if there is an uppercase
    // if all chars are lowercase, then it runs all_unique_letters
    if (is_all_lowercase(argv[1]) == 0) {
        return 0;
    } 
    if (is_all_lowercase(argv[1]) == 1) {
        all_unique_letters(argv[1]);
        return 0;
    } 
    
    return 0;
}
