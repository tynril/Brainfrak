#include "Brainfuck.h"
#include <string>
#include <fstream>
#include <iostream>

/**
 * Sample program to test the Brainfuck interpreter. It
 * reads the file on the path given as the first argument,
 * and pass it as instructions to the Brainfuck interpreter.
 */
int main(int argc, char *argv[])
{
	// Checking if there's a file.
	if(argc < 2) {
		std::cout << "First argument must point to a file." << std::endl;
		return EXIT_FAILURE;
	}

	// Opening the BF source file.
	std::ifstream bfFile(argv[1]);
	if(!bfFile || !bfFile.is_open()) {
		std::cout << "Error opening the given file." << std::endl;
		return EXIT_FAILURE;
	}

	// Reading the instructions set.
	std::string instructions;
	std::string line;
	while(getline(bfFile, line)) {
		instructions += line;
	}
	bfFile.close();

	// Executing the brainfuck interpreter.
	Brainfuck bf;
	bf.setInstructions(instructions);
	bf.execute();

	// Waiting for a user interaction.
	std::cin.ignore();
	return EXIT_SUCCESS;
}