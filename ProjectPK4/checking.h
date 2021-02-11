#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <cstddef>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Friendship functions, which are helpful to check the inserted details 

bool stringcheck (string & line);  // Check if the written string is correct (contains only letters)
int datecheck(string & line); // Check if the written date is correct and contais only digits
bool numbercheck(string & line, int amount);  // Check if the written string is correct (contains only digits and check if the lenght is correct)
string optioncheck (int option); // Show a list of option depends of the variable
string truecheck(string & line, int amount); // Check if the bool answer
bool choice (int & choice); // Check if the choice is a number
bool choiceforemp(int& number, int index); // Check if the choice is a number and if it is lower
void kindofwork(); // Show kind of work