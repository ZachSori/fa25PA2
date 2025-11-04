//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    //1.
    MinHeap heap;
    //2.
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i,weightArr);
    }
    //3.
    while (heap.size>1) {
        int least = heap.pop(weightArr);
        int nextLeast = heap.pop(weightArr);
        //pops last two nodes and saves them

        int parent = nextFree++;

        //create a node for the parent for each arr defined: weight, left, right, char
        //each arr/tree are essentially duplicates of each other that hold different values that will be used
        weightArr[parent] = weightArr[least] + weightArr[nextLeast];
        leftArr[parent] = least;
        rightArr[parent] = nextLeast;
        charArr[parent] = ' ';//combination of char to make parent does not make new char so placeholder
        heap.push(parent, weightArr);
    }
    //4.
    return heap.pop(weightArr); //pops last node and returns the value of it in the heap
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    stack<pair<int,string>> stack;
    stack.push({root,""});

    while (!stack.empty()){
        pair<int,string> top = stack.top();
        stack.pop();

        int node = top.first;
        string code = top.second;
        if (leftArr[node]==-1 && rightArr[node]==-1) { //if the arr is -1 then it has reached the leaf node
            int charIndex = charArr[node] - 'a';
            codes[charIndex] = code.empty() ? "0" : code; //edge case if input is one character
        }
        if (leftArr[node]!=-1) {
            stack.push({leftArr[node], code+"0"}); //if traverse to left adds 0 to end of code
        }
        if (rightArr[node]!=-1) {
            stack.push({rightArr[node], code+"1"}); //if traverse to right adds 1 to end of code
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}