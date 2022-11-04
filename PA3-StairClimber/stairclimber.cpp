/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Zachary Rimshnick
 * Date        : 10/03/2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int stairs;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    vector<vector<int>> sol;

    if (num_stairs <= 0) {
        // insert element to end of our vector 
        sol.insert(sol.end(),vector<int>());
    } 
    vector<vector<int>> sol_rec;

    // in range(1,4), loop through this
    int i;
    for (i = 1; i < 4; i++) {
        // loops until we've reached the max number of stairs in problem
        if (i <= num_stairs) {
            // recursion (loops through get_ways by 1 less each time until i is less than number of stairs in problem)
            sol_rec = get_ways(num_stairs - i);

            // will loop through each vector in the vector from the current recursive call 
            for (auto &list : sol_rec) {
                list.insert(list.begin(), i);
            }

            // inserts the vector from current recursive call to our solutions array
            sol.insert(sol.end(), sol_rec.begin(), sol_rec.end());
        }
    }
    return sol; 

}

int num_digits(int num) {
    // function I wrote from Sieve homework to get number of digits in a number
    int i = 0;
    // divides input number by 10 until it is less than or equal to 1
    // the # of times it divides by 10 is another digit
    for (i = 0; num >= 1; i++) {
        num = num / 10;
    } 
    //cout << "NUMBER OF DIGITS: " << i << endl;
    return i;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    int numSolutions = ways.size();

    // Prints how many ways to climb the stairs there are
    if (numSolutions == 1) {   // if only 1 solution, it needs to have no plural
        cout << numSolutions << " way to climb " << stairs << " stair." << endl; 
    } else {                   // if more than 1 solution, then it needs plural
        cout << numSolutions << " ways to climb " << stairs << " stairs." << endl;
    }

    int size = num_digits(numSolutions);
    size_t i = 0;
    // while i is less than number of solutions, put number on the left, formatted properly
    while (i < ways.size()) {
        cout << setw(size) << i+1 << ". [";

        // then, print the actual solutions, in proper order, stopping when the next index is the end
        size_t j = 0;
        while (j < ways[i].size()) {
            cout << ways[i][j];
            if (j + 1 != ways[i].size()) {
                cout << ", ";
            } else {
                break;
            }
            j++;
        }
        cout << "]" << endl;
        i++;
    }
}

int main(int argc, char * const argv[]) {

    istringstream iss;
    
    // if there are 0 inputs, or more than 1 input, give this error message
    if (argc == 1) {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 0;
    }
    if (argc > 2) {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 0;
    }


    // if the input is not a positive integer
    iss.str(argv[1]);
    if (!(iss >> stairs) || stairs < 1) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 0;
    }

    display_ways(get_ways(stairs));
    return 0;
}
