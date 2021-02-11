#pragma once


#include <iostream>
#include <vector>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Abstract function for changing the interface
class Strategy { 
public:
	bool virtual loadbase (vector <string> elements) = 0; // Load a base from txt file
	bool virtual savebase(std::ostream& outfile) = 0; // Save a base to txt file
	void virtual deletebase() = 0; // Load a base to txt file
    bool virtual help() = 0; // Show help information

	// Deconstructor
	virtual ~Strategy() {};
};

class Contex {
protected:
	 Strategy * strategy; // Strategy
	 vector <string> elements;
public:
	// Constructor
	Contex() :strategy(nullptr) {};
	// Deconstructor
	~Contex() { strategy = nullptr; };

	void method(); // Function, which turns a help interface
	void setstrategy(Strategy* pstrategy); // Set a strategy
	void loadbase(vector <string> elements); // Load a base to txt file
	void savebase(std::ostream& outfile); // Save a base from txt file
	void deletebase(); // Deleting the existing base data

	// Friend funtions
	// Load a base to txt file
	friend bool loaddatabase(vector <Strategy*> vec, Contex * contex);
	// Save a base from txt file
	friend bool savedatabase(vector <Strategy*> vec, Contex* contex);
};

