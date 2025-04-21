/**
 * Simple Blockchain Implementation in C++
 *
 * This program demonstrates the fundamental concepts of blockchain technology
 * through a simplified implementation. It allows users to create a chain of blocks,
 * each containing data and linked to the previous block through cryptographic hashes.
 *
 * Concepts demonstrated:
 * - Block structure
 * - Hashing
 * - Chain linking
 * - Immutability
 *
 */

#include <iostream> // For input/output operations
#include <string>   // For string manipulation
using namespace std;

// Maximum number of blocks allowed in our blockchain
const int MAX_BLOCKS = 10;

/**
 * Block Structure
 *
 * Represents a single block in the blockchain with three key components:
 * - data: The information stored in this block
 * - prevHash: Hash of the previous block (creates the "chain")
 * - hash: This block's own hash (derived from its data and the previous hash)
 */
struct Block
{
    string data;     // Information stored in the block
    string prevHash; // Hash of the previous block
    string hash;     // Hash of this block (calculated from data + prevHash)
};

/**
 * Simple Hash Function
 *
 * This function creates a unique identifier (hash) for a given input string.
 * While real blockchains use complex cryptographic hash functions (like SHA-256),
 * this simplified version demonstrates the basic concept.
 *
 * How it works:
 * 1. Calculates a numeric hash by summing the ASCII values of each character
 *    multiplied by its position (to make order matter)
 * 2. Converts this numeric hash to an 8-character hexadecimal string
 *
 * Example:
 * For input "Hello":
 * - 'H' (ASCII 72) × position 1 = 72
 * - 'e' (ASCII 101) × position 2 = 202
 * - 'l' (ASCII 108) × position 3 = 324
 * - 'l' (ASCII 108) × position 4 = 432
 * - 'o' (ASCII 111) × position 5 = 555
 * - Sum = 1585
 * - This number is then converted to an 8-character hexadecimal representation
 *
 * @param input The string to be hashed
 * @return An 8-character hexadecimal hash string
 */
string simpleHash(string input)
{
    // Initialize hash value
    int hash = 0;

    // Step 1: Calculate the hash by summing ASCII values × position
    for (int i = 0; i < input.length(); i++)
    {
        // Add the ASCII value of each character multiplied by its position (i+1)
        // This ensures that different arrangements of the same characters produce different hashes
        hash += (int)input[i] * (i + 1);
    }

    // Step 2: Convert the numeric hash to an 8-character hexadecimal string
    char hashArray[9]; // 8 characters + null terminator
    for (int i = 0; i < 8; i++)
    {
        // Extract 4 bits (a single hex digit) from the hash
        // >> shifts bits right, (i * 4) determines which group of 4 bits
        // & 0xF masks all but the lowest 4 bits (hexadecimal digit)
        int value = (hash >> (i * 4)) & 0xF;

        // Convert the 4-bit value to a hexadecimal character
        // 0-9 become '0'-'9', 10-15 become 'A'-'F'
        hashArray[i] = value < 10 ? '0' + value : 'A' + (value - 10);
    }

    // Add null terminator to make it a proper C-string
    hashArray[8] = '\0';

    // Convert C-string to C++ string and return
    return string(hashArray);
}

/**
 * Create a New Block
 *
 * This function creates a new block with the provided data and links it
 * to the previous block by storing its hash.
 *
 * @param data The information to store in the new block
 * @param prevHash The hash of the previous block in the chain
 * @return A new Block structure with calculated hash
 */
Block createBlock(string data, string prevHash)
{
    Block block;
    block.data = data;         // Store the data
    block.prevHash = prevHash; // Link to previous block

    // Calculate this block's hash by combining its data and the previous hash
    // This ensures that any change to either the data or the chain would invalidate the hash
    block.hash = simpleHash(data + prevHash);

    return block;
}

/**
 * Main Function
 *
 * Controls the blockchain creation process:
 * 1. Creates a genesis block (first block)
 * 2. Allows user to add blocks with custom data
 * 3. Displays the entire blockchain
 */
int main()
{
    // Array to store our blockchain
    Block blockchain[MAX_BLOCKS];
    int blockCount = 0;

    // Create the genesis block (first block in the chain)
    // It has arbitrary prevHash "00000000" since there is no actual previous block
    blockchain[0] = createBlock("Genesis Block", "00000000");
    blockCount++;

    // User interaction loop to add blocks
    char choice = 'y';
    while (choice == 'y' && blockCount < MAX_BLOCKS)
    {
        // Get data for the new block
        string data;
        cout << "\nEnter data for block " << blockCount << ": ";
        getline(cin, data);

        // Create a new block and add it to the chain
        // Note how each block references the hash of the previous block
        blockchain[blockCount] = createBlock(data, blockchain[blockCount - 1].hash);
        blockCount++;

        // Ask if user wants to add another block
        cout << "Add another block? (y/n): ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from input buffer
    }

    // Display the entire blockchain
    cout << "\n=== Blockchain ===\n";
    for (int i = 0; i < blockCount; i++)
    {
        cout << "Block " << i << ":\n";
        cout << "  Data      : " << blockchain[i].data << "\n";
        cout << "  Prev Hash : " << blockchain[i].prevHash << "\n";
        cout << "  Hash      : " << blockchain[i].hash << "\n\n";
    }

    return 0;
}