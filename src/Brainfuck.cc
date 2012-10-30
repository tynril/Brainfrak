#include "Brainfuck.h"
#include <iostream>
#include <string>
#include <vector>

/**
 * We create the memory buffer on instanciation.
 */
Brainfuck::Brainfuck()
{
	// Assigning default memory.
	m_memory.assign(Brainfuck::MEMORY_BUFFER_SIZE, 0);
	m_memoryPointer = 0;
}

/**
 * Destructing this object clean memory and instruction
 * buffers.
 */
Brainfuck::~Brainfuck()
{
	m_memory.clear();
	m_instructions.clear();
}

/**
 * Store instructions, keeping only Brainfuck valid
 * operators.
 */
void Brainfuck::setInstructions(std::string instructions)
{
	// Storing the instructions without the comments.
	for(unsigned int i = 0; i < instructions.length(); i ++)
	{
		switch(instructions.at(i))
		{
		case Brainfuck::I_MOVE_RIGHT:
		case Brainfuck::I_MOVE_LEFT:
		case Brainfuck::I_INCREMENT:
		case Brainfuck::I_DECREMENT:
		case Brainfuck::I_DISPLAY:
		case Brainfuck::I_GET:
		case Brainfuck::I_LOOP_FORWARD:
		case Brainfuck::I_LOOP_BACKWARD:
			m_instructions.push_back(instructions.at(i));
		}
	}

	// Reseting the instructions pointer.
	m_instructionsPointer = 0;
}

/**
 * Process every instruction until the end of file, or
 * until an exception is thrown.
 */
void Brainfuck::execute()
{
	// Processing instructions until the pointer hits the end.
	try {
		while(m_instructionsPointer < m_instructions.size()) {
			processNextInstruction();
		}
	}
	catch(const char *e) {
		std::cout << "Error: " << e << std::endl;
	}
}

/**
 * Process one instruction, the one currently pointed by
 * the instruction pointer.
 */
inline void Brainfuck::processNextInstruction()
{
	// Get the current instruction.
	const char instruction = m_instructions.at(m_instructionsPointer);

	switch(instruction)
	{
		// Move the memory pointer by one on the right.
		case Brainfuck::I_MOVE_RIGHT:
		{
			if(m_memoryPointer == Brainfuck::MEMORY_BUFFER_SIZE) {
				m_memoryPointer = 0;
			}
			else {
				m_memoryPointer ++;
			}
			m_instructionsPointer ++;
			break;
		}

		// Move the memory pointer by one on the left. Wraps to
		// the end of memory if the pointer 
		case Brainfuck::I_MOVE_LEFT:
		{
			if(m_memoryPointer == 0) {
				m_memoryPointer = Brainfuck::MEMORY_BUFFER_SIZE;
			}
			else {
				m_memoryPointer --;
			}
			m_instructionsPointer ++;
			break;
		}

		// Increment the current memory segment by one.
		case Brainfuck::I_INCREMENT:
		{	
			m_memory[m_memoryPointer] ++;
			m_instructionsPointer ++;
			break;
		}

		// Decrement the current memory segment by one.
		case Brainfuck::I_DECREMENT:
		{
			m_memory[m_memoryPointer] --;
			m_instructionsPointer ++;
			break;
		}

		// Display the current memory segment as a character.
		case Brainfuck::I_DISPLAY:
		{
			std::cout << m_memory[m_memoryPointer];
			m_instructionsPointer ++;
			break;
		}

		// Get a character from the standard input and put it
		// in the current memory segment.
		case Brainfuck::I_GET:
		{
			unsigned char value;
			std::cin >> value;
			m_memory[m_memoryPointer] = value;
			m_instructionsPointer ++;
			break;
		}

		// Jump the instruction pointer to the corresponding loop
		// backward operation, unless the current memory segment
		// is different from zero.
		case Brainfuck::I_LOOP_FORWARD:
		{
			if(m_memory[m_memoryPointer] != 0) {
				m_instructionsPointer ++;
				break;
			}

			int loopsOpened = 1;
			unsigned char nextInstruction;

			do {
				m_instructionsPointer ++;

				try {
					nextInstruction = m_instructions.at(m_instructionsPointer);
				}
				catch(std::out_of_range) {
					throw "Missing loop backward operator.";
				}

				if(nextInstruction == Brainfuck::I_LOOP_FORWARD) {
					loopsOpened ++;
				}
				else if(nextInstruction == Brainfuck::I_LOOP_BACKWARD) {
					loopsOpened --;
				}
			} while(loopsOpened > 0);
			m_instructionsPointer ++;
			break;
		}

		// Jump the instruction pointer to the corresponding loop
		// forward operation, unless the current memory segment
		// equals zero.
		case Brainfuck::I_LOOP_BACKWARD:
		{
			if(m_memory[m_memoryPointer] == 0) {
				m_instructionsPointer ++;
				break;
			}

			int loopsOpened = 1;
			unsigned char previousInstruction;

			do {
				m_instructionsPointer --;
				
				try {
					previousInstruction = m_instructions.at(m_instructionsPointer);
				}
				catch(std::out_of_range) {
					throw "Missing loop forward operator.";
				}
				
				if(previousInstruction == Brainfuck::I_LOOP_FORWARD) {
					loopsOpened --;
				}
				else if(previousInstruction == Brainfuck::I_LOOP_BACKWARD) {
					loopsOpened ++;
				}
			} while(loopsOpened > 0);
			m_instructionsPointer ++;
			break;
		}
	}
}