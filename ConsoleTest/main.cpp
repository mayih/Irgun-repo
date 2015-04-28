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
int chooseOption(int maxOption){
	int selected;
	do
	{
		cin >> selected;
	} while (selected < 1 || selected > maxOption);
	return selected;
}

int main()
{
	char a[2] = { 'a', 'b' };

	try{
		checkFlagValues('C', a);
	}
	catch (string e){
		cout << e << endl;
		system("pause");
	}

	//int option = 0;
	//TrieSite trie;
	//bool rightToWrite;
	//string path;

	//// STEP ONE ------------------
	//// Display the menu
	//string menu = "Choose an option:\n";
	//		menu += "1- Create a TrieSite\n";
	//		menu += "2- Open an existing TrieSite?\n";
	//cout << menu;

	//// Read an option
	//option = chooseOption(2);

	//// Read the TrieSite's path
	//cout << "Please enter the TrieSite's path (absolute/relative):" << endl;
	//cin >> path;

	//// Asking the opening method
	//cout << "Do you wish to be able to modify it? (y/n) : ";
	//rightToWrite = yesOrNo();

	//// Create/load the TrieSite
	//trie = TrieSite(path, (option == 1 ? 'c' : 'm'), (rightToWrite ? 'm' : 'q'));
	//// -----------------------------

	//// STEP TWO ----------------------
	//bool exit = false;
	//do
	//{
	//	cout << endl;
	//	menu = "Choose an option:\n";
	//	menu += "1- Load a .stop file\n";
	//	menu += "2- Add a file as a document\n";
	//	menu += "3- Exit";
	//	cout << menu;

	//	option = chooseOption(3);

	//	switch (option)
	//	{
	//	case 1:
	//		cout << "Enter the .stop file's path:\n";
	//		cin >> path;
	//		trie.putstopfl(path);
	//		break;
	//	case 2:
	//		break;
	//	default:
	//		exit = true;
	//	}

	//} while (!exit);

	return 0;
}
