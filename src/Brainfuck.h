#pragma once
#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <string>
#include <vector>

/**
 * Standard Brainfuck interpreter, without macro support.
 *
 * Written by Samuel Lorétan on March 12th, 2010.
 * Contact: sloretan<at>gmail.com
 */
class Brainfuck
{
private:
	// Standard memory buffer is 30000 octets
	static const unsigned int MEMORY_BUFFER_SIZE = 30000;

	// Brainfuck supports 8 operators.
	static const unsigned char I_MOVE_RIGHT		= '>';
	static const unsigned char I_MOVE_LEFT		= '<';
	static const unsigned char I_INCREMENT		= '+';
	static const unsigned char I_DECREMENT		= '-';
	static const unsigned char I_DISPLAY		= '.';
	static const unsigned char I_GET			= ',';
	static const unsigned char I_LOOP_FORWARD	= '[';
	static const unsigned char I_LOOP_BACKWARD	= ']';

	// Storing memory and instructions in vectors.
	std::vector<unsigned char> m_memory;
	unsigned int m_memoryPointer;
	std::vector<unsigned char> m_instructions;
	unsigned int m_instructionsPointer;

public:
	/**
	 * Instanciate a new Brainfuck interpreter.
	 */
	Brainfuck();
	virtual ~Brainfuck();

	/**
	 * Set instructions to be interpreted. This string can
	 * contain any characters, only Brainfuck operators
	 * will be interpreted.
	 */
	void setInstructions(const std::string instructions);

	/**
	 * Execute the interpreter on the previously given
	 * instructions.
	 */
	void execute();

private:
	/**
	 * Process the next instruction.
	 */
	void processNextInstruction();
};

#endif /* BRAINFUCK_H */