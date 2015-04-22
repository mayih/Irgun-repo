#include <iostream>
#include<string>
#include "DirectoryFunctions.h"
#include "TrieSite.h"
#include <stdlib.h>

using namespace std;
using namespace Trie;

// Ask the user "yes"(y) or "no"(n).
bool yesOrNo(){
	char key;
	do {
		cin >> key;
	} while (key != 'y' && key != 'Y' && key != 'n' && key != 'N');

	return (key == 'y' || key == 'Y');
}
// Execute for the 1st option
TrieSite createATrieSite(){
	string path;
	bool isLoaded;

	cout << "\nLoad an existant TrieSite?(y/n) : ";
	isLoaded = yesOrNo();

	cout << "Please enter the path (absolute/relative):" << endl;
	cin >> path;

	if (isLoaded) // Load
	{
		bool rightToWrite;
		cout << "Do you wish to be able to modify it? (y/n) : ";
		rightToWrite = yesOrNo();
		return TrieSite(path, 'm', (rightToWrite ? 'm' : 'q'));

	}
	else{ // Create
		return TrieSite(path, 'c', 0);
	}
}

int main()
{
	bool again = true;
	int option = 0;
	TrieSite* allTrieSites = new TrieSite();
	int numberOfTrieSite = 0;
	do
	{
		// Display the menu
		string menu = "Choose an option from the menu:\n";
				menu += "1- Create a TrieSite\n";
				menu += "2- Load a stop.fl to one of your Trisite\n";
		cout << menu;

		// Read an option
		do
		{
			cin >> option;
		} while (option < 1 && option > 1 /*To increase*/ );

		// Execute the option
		switch (option)
		{

		case 1:
			allTrieSites[numberOfTrieSite] = createATrieSite();
			numberOfTrieSite++;
			break;

		case 2:
			int selected = 0;
			string path;

			// If there's no TrieSite
			if (numberOfTrieSite < 1) {
				cout << "You still have no TrieSite created." << endl
					<< "Please create one by selecting 1 from the menu." << endl;
				break;
			}

			// If there's more than 1 TrieSite
			if (numberOfTrieSite > 1)
			{
				cout << "You've got " << numberOfTrieSite << " TrieSites availaible." << endl
					<< "Which one do you wanna load the stop file to? (1->" << numberOfTrieSite << ")" << endl;
				do
				{
					cin >> selected;
					if (selected < 1 || selected > numberOfTrieSite) // if wrong on the choice
						cout << "Please choose a correct Triesite: ";
				} while (selected < 1 || selected > numberOfTrieSite);
			}

			cout << "Please enter the file's path you wish to load:" << endl;
			cin >> path;
			allTrieSites[selected].putstopfl(path);

		}

		// Ask the user if he wanna continu.
		cout << "Done." << endl;
		cout << "Return to Menu? (y/n) : ";
		again = yesOrNo();
		cout << endl;
	} while (again);

	// Clear memory
	delete allTrieSites;
	allTrieSites = 0;

	return 0;
}
