#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

// Function to fill the file with random integers
void fillFile(const string& filename, int count, int maxNumber) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error creating file: " << filename << endl;
        return;
    }

    srand(time(nullptr)); // Seed for random number generation
    for (int i = 0; i < count; ++i) {
        int num = rand() % (maxNumber + 1); // Random number between 0 and maxNumber
        outFile << num << endl;
    }

    outFile.close();
}

// Function to find the sum of the maximum and minimum elements in the file
int findSumOfMaxAndMin(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        return 0;
    }

    int num;
    int maxVal = numeric_limits<int>::min(); // Initialize to smallest possible integer
    int minVal = numeric_limits<int>::max(); // Initialize to largest possible integer

    // Read numbers from the file
    while (inFile >> num) {
        if (num > maxVal) maxVal = num;
        if (num < minVal) minVal = num;
    }

    inFile.close();
    return maxVal + minVal;
}

int main() {
    string filename = "numbers.txt";
    int numCount = 10;    // Number of random integers
    int maxNumber = 100;  // Maximum random number value

    // Step 1: Fill the file with random integers
    fillFile(filename, numCount, maxNumber);

    // Step 2: Find the sum of the maximum and minimum elements
    int sum = findSumOfMaxAndMin(filename);

    // Step 3: Output the result
    cout << "The sum of the maximum and minimum elements in the file is: " << sum << endl;

    return 0;
}
