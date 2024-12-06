#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to fill the binary file with random numbers
void fillFile(const string& filename, int count, int maxNumber) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error creating file: " << filename << endl;
        return;
    }
    srand(time(nullptr));
    for (int i = 0; i < count; ++i) {
        int num = rand() % maxNumber + 1; // Random number between 1 and maxNumber
        outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
    }
    outFile.close();
}

// Function to filter numbers not divisible by k
void filterFile(const string& source, const string& destination, int k) {
    ifstream inFile(source, ios::binary);
    ofstream outFile(destination, ios::binary);
    if (!inFile || !outFile) {
        cerr << "Error opening files!" << endl;
        return;
    }

    int num;
    while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        if (num % k != 0) { // Check if not divisible by k
            outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
        }
    }
    inFile.close();
    outFile.close();
}

// Function to print the contents of a binary file
void printFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    cout << "Contents of " << filename << ": ";
    int num;
    while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        cout << num << " ";
    }
    cout << endl;
    inFile.close();
}

int main() {
    string sourceFile = "source.dat";
    string destinationFile = "filtered.dat";
    int numElements = 20; // Number of random elements
    int maxNumber = 100;  // Maximum random number value
    int k = 5;            // Divisor

    // Fill the source file with random numbers
    fillFile(sourceFile, numElements, maxNumber);

    // Print the source file
    printFile(sourceFile);

    // Filter numbers not divisible by k
    filterFile(sourceFile, destinationFile, k);

    // Print the filtered file
    printFile(destinationFile);

    return 0;
}
