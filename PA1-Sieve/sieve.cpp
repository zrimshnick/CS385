/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Zachary Rimshnick
 * Date        : 09/19/2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    // sets max_prime to be the result of count_num_primes (max)
    max_prime_ = count_num_primes();
    display_primes();

}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.


    // print line indicating to find all primes up to the entered number
    cout << "Primes up to " << limit_ << ":"<< endl;

    // given on canvas -- sets max prime width, as well as finds out primes per row
    const int max_prime_width = num_digits(max_prime_),
              primes_per_row = 80 / (max_prime_width + 1);
    // just to use primes_per_row
    if (primes_per_row == 10000000000000000) {
    } 

    // since the highest prime to be all on one line is 101, the rest of this loop doesn't need setw
    if (limit_ <= 101) {
        // loop for printing each number
        for (int i = 0; i <= limit_; i++) {
            // if element is true (prime), print the index (the prime #) with space after, unless it is the last one, then end line
            if (is_prime_[i] == true) {
                if (i == max_prime_) {
                    cout << i << endl;
                } else {cout << i << " ";} 
            }
        }
    } else {
        // create a variable to count the rows
        int row_counter = 1;
        // loop when the max prime creates a need for more than one line
        for (int i = 0; i <= limit_; i++) {
            // setw will use the max prime width to set the width
            cout << setw(max_prime_width);
            // if the element is true (prime), moves on to more else/if statements
            if (is_prime_[i] == true) {
                // if prime is the max prime, then end the line
                if (i == max_prime_) {
                    cout << i << endl;
                // if the row countrer is equal to the primes per row value, then end line and reset counter
                } else if (row_counter == primes_per_row){
                    cout << i << endl;
                    row_counter = 1;
                // if prime is not the max prime, then increment row counter by 1 and print with a space after
                } else {
                    row_counter++;
                    cout << i << " ";
                }
            }
        }
    }    
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    // creates a new integer variable that will contain the count for total number of primes
    int number_of_primes = 0;

    int max = 0;

    // loops through the already modified array, checking each element if it's true
    // if true, it increases the count on number_of_primes by 1
    for (int i = 0; i <= limit_; i++) {

        if (is_prime_[i] == true) {
            number_of_primes++;
            max = i;
        } 
        // prints out the number of primes found
    } cout << "\nNumber of primes found: " << number_of_primes << endl;
    
    return max;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // sets first two indexes (0 and 1) to be false since they aren't prime
    is_prime_[0] = false;
    is_prime_[1] = false;
    // starting at index 2, sets each future element as true
    for (int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
    }

    // SIEVE ALGORITHM
    // starting at index 2 (since 0 and 1 are never prime), checks if element is true
    // if element is true, it then loops again using the sieve algorithm of i^2, i^2 + i, i^2 + 2i, ...
    // if the element makes it out of the loop then it is true and it is a prime number
    // if not, then it is labeled false, and stops that loop
    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i] == true) {
             for (int j = pow(i, 2); j <= limit_; j = j + i) {
                is_prime_[j] = false;
            }
        }
    }
    // prints out the true/false array for me to see
/*     for (int i = 0; i <= limit_; i++) {
        cout << is_prime_[i] << " ";
    }
    cout << "\n"; */

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int i = 0;
    for (i = 0; num >= 1; i++) {
        num = num / 10;
    } 
    //cout << "NUMBER OF DIGITS: " << i << endl;
    return i;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    //cout << "TESTING" << endl;
    PrimesSieve sieve1(limit);
    return 0;
}
