// The author disclaims copyright to this source code.
#ifndef COMPONENT_H
#define COMPONENT_H

/**
 * Components are the building blocks of the application.
 * Every component is setup at least once before first use.
 */
class Component {
public:
	virtual ~Component() {};
	virtual void setup() = 0;
};

/**
 * A component is an input if it needs to read once every loop.
 * The read operation is performed before the Process and Output operations.
 */
class Input {
public:
	virtual ~Input() {};
	virtual void read() = 0;
};

/**
 * A component is an output if it needs to write once every loop.
 * The write operation is performed after the Input and Process operations.
 */
class Output {
public:
	virtual ~Output() {};
	virtual void write() = 0;
};

/**
 * A component is a process if needs to perform processing once every loop.
 * The process operation is performed after the Input and before the Output operation.
 */
class Process {
public:
	virtual ~Process() {};
	virtual void process() = 0;
};

#endif

