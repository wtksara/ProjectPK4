
#include "strategy.h"
#include "employeebase.h"
#include "companybase.h"
#include "intcompany.h"
#include "companybase.h" 
#include "payment.h" 

void Contex::method()
{
		bool option = strategy->help();
		while (option != false)
		{
			cout << endl << endl;
			option = strategy->help();

		}
}

void Contex::setstrategy(Strategy* pstrategy)
{
	this->strategy = pstrategy;
}

void Contex::loadbase(vector <string> elements)
{
	strategy->loadbase(elements);
}

void Contex::savebase(std::ostream& outfile)
{
	strategy->savebase(outfile);
}

void Contex::deletebase()
{
	strategy->deletebase();
}

bool loaddatabase(vector <Strategy*> vec, Contex* contex)
{
	std::ifstream infile;
	string line;
	char path[200];

	cout << endl;
	cout << "                            ENTERING THE DATEBASE FROM INPUT .TXT FILE \n";
	cout << "                            ENTER THE PATH TO THE INPUT .TXT FILE \n";
	cin >> path;

	infile.open(path);

	if (infile.good()) // Check if the file has been opened correct
	{
		infile.seekg(0, std::ios::end); // Set indicator on the end of the file 
		if (infile.tellg()) { // Check the length of the file to check if the file is empty 
			infile.seekg(0, std::ios::beg);  // Set indicator on the beggining of the file 
			do
			{
				int i = 0;
				while (getline(infile, line, '#')) {
					std::stringstream sfile(line);

					contex->setstrategy(vec[i]);

					while (getline(sfile, line, '\n')) {
						std::stringstream pfile(line); 
						if (!line.empty()) {
							while (getline(pfile, line, ';')) { // Get a line and save in string 

								contex->elements.push_back(line); // Seperate the elements
							};
							// Save elements to relevant variables
							contex->loadbase(contex->elements);
							contex->elements.clear();
						}
					}
					i++;
				}
				

			} while (!infile.eof()); // Perform until end of the file 

			infile.close(); // Close input file 

			return true;
		}
		else {
			cout << "                            THE FILE IS EMPTY \n";
			return false;
		}
	}
	else {
		cout << "                            THE FILE COULD NOT BE OPENED \n";
		return false;
	}
}

bool savedatabase(vector<Strategy*> vec, Contex* contex)
{
	std::ofstream outfile;
	char path[200];
	cout << endl;
	cout << "                            SAVE THE EMPLOYEE DATEBASE IN OUTPUT .TXT FILE " << endl;
	cout << "                            ENTER THE PATH TO THE OUTPUT .TXT FILE " << endl;
	cin >> path;
	outfile.open(path, std::ios::trunc);

	if (outfile.good()) // Check if the file has been opened correctly
	{
		for (int i = 0; i < vec.size(); i++) {
			contex->setstrategy(vec[i]);
			contex->savebase(outfile);
			contex->elements.clear();
		}
		outfile << "#";
		outfile.close(); // Close input file 
		return true;
	}
	else {
		cout << "                            THE FILE COULD NOT BE OPENED \n";
		return false;
	}
}
