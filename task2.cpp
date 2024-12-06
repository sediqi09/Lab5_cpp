#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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

// Function to load data from the binary file into a square matrix
void loadMatrix(const string& filename, vector<vector<int>>& matrix, int n) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    int num, index = 0;
    while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        matrix[index / n][index % n] = num;
        ++index;
    }
    inFile.close();
}

// Function to find the column with the maximum product of non-zero elements
int findColumnWithMaxProduct(const vector<vector<int>>& matrix, int n) {
    int maxCol = 0;
    long long maxProduct = 0;

    for (int col = 0; col < n; ++col) {
        long long product = 1;
        bool hasNonZero = false;

        for (int row = 0; row < n; ++row) {
            if (matrix[row][col] != 0) { // Ignore zeros
                product *= matrix[row][col];
                hasNonZero = true;
            }
        }

        // Update maxProduct only if the column has non-zero elements
        if (hasNonZero && abs(product) > abs(maxProduct)) {
            maxProduct = product;
            maxCol = col;
        }
    }
    return maxCol;
}

// Function to print the matrix
void printMatrix(const vector<vector<int>>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    string filename = "data.bin";
    int numElements = 12;  // Number of random elements
    int maxNumber = 10;    // Maximum random number value
    int n = 4;             // Size of the square matrix

    // Step 1: Fill the binary file with random data
    fillFile(filename, numElements, maxNumber);

    // Step 2: Create an n x n matrix initialized with zeros
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    // Step 3: Load data from the binary file into the matrix
    loadMatrix(filename, matrix, n);

    // Step 4: Print the matrix
    cout << "Matrix:" << endl;
    printMatrix(matrix, n);

    // Step 5: Find the column with the maximum product
    int maxCol = findColumnWithMaxProduct(matrix, n);
    cout << "Column with the maximum non-zero product: " << maxCol + 1 << endl;

    return 0;
}
