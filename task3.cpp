#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Define the Toy structure
struct Toy {
    char name[50]; // Toy name (string up to 50 characters)
    int cost;      // Cost in rubles
    int minAge;    // Minimum age limit
    int maxAge;    // Maximum age limit
};

// Function to fill the binary file with toy data
void fillFile(const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Error creating file: " << filename << endl;
        return;
    }

    // Create some sample toys
    Toy toys[] = {
        {"ball", 500, 2, 5},
        {"car", 700, 3, 6},
        {"doll", 800, 1, 4},
        {"puzzle", 600, 5, 8},
        {"lego", 1200, 5, 10}
    };

    // Write toys to the file
    for (const Toy& toy : toys) {
        outFile.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));
    }

    outFile.close();
}

// Function to find a suitable toy for a 3-year-old child
void findSuitableToy(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    Toy toy;
    bool found = false;

    cout << "Checking for suitable toys for a 3-year-old (excluding 'ball')..." << endl;

    // Read toys from the file
    while (inFile.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        if (string(toy.name) != "ball" && toy.minAge <= 3 && toy.maxAge >= 3) {
            cout << "Suitable toy found: " << endl;
            cout << "Name: " << toy.name << endl;
            cout << "Cost: " << toy.cost << " rubles" << endl;
            cout << "Age range: " << toy.minAge << "-" << toy.maxAge << " years" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No suitable toy found for a 3-year-old (excluding 'ball')." << endl;
    }

    inFile.close();
}

int main() {
    string filename = "toys.bin";

    // Step 1: Fill the binary file with toy data
    fillFile(filename);

    // Step 2: Find a suitable toy for a 3-year-old child
    findSuitableToy(filename);

    return 0;
}
