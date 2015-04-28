#include "TrieDoc.h"
#include "DirectoryFunctions.h"

using namespace Trie;
using namespace std;

TrieDoc::TrieDoc(){ 
	_docName = "";
}

TrieDoc::TrieDoc(std::string triePath, std::string filePath){
	putDoc(triePath, filePath);
}

void TrieDoc::putDoc(std::string triePath, string filePath, char copyOrMove){
	char values[2] = { 'm', 'c' };
	checkFlagValues(copyOrMove, values); // check if copyOrMove value is correct (throw exception)

	bool move = (copyOrMove == 'm') || (copyOrMove == 'M');
	if (!fileExist(filePath)) // check if file exists
		throw "Inexistant file.";

	_docName = cutExtension(cutFileNameWithExtension(filePath)); // cut extension

	triePath = addSlashToDirPath(triePath); // Add '/' to the TrieSite's path if it doesn't have one.

	// Create TrieDoc directory and add the file into
	string destinationDir = triePath + _docName + "/";
	createDirectory(destinationDir);
	if (move)
		moveFile(filePath, destinationDir);
	else
		copyFile(filePath, destinationDir);

	if (fileHasStopFileBrother(filePath)) // check if it exist
	{
		string stopFilePath = filePathToDirectoryPath(filePath) + "/" + _docName + ".stop"; // Build the .stop file's path
		if (move)
			moveFile(stopFilePath, destinationDir);
		else
			copyFile(stopFilePath, destinationDir);
	}
	else // I still don't know what to do here
	{
		// ....
		//ofstream flux(directory + _docName + ".stop"); // create a document's stop file
		//flux.close();
	}
}

void TrieDoc::getdoc(std::string triePath, std::string destination){
	if (destination == "") // check if destination is by default
		destination = getCurrentPath();

	if (triePath[triePath.size() - 1] != '/') // check if triePath has "/" at the end
		triePath += "/";

	string fileName = _docName;
	addExtension(fileName, triePath + _docName); // get the file's name with its extension

	copyFile(triePath + _docName + "/" + fileName, destination); // copy
}

void TrieDoc::del(std::string triePath, char wayToDelete){
	char values[2] = { 'l', 'p' };
	checkFlagValues(wayToDelete, values); // check if wayToDelete value is correct (throw exception)

	string docDir = addSlashToDirPath(triePath) + _docName + "/";

	if ((wayToDelete == 'p') || (wayToDelete == 'P')) // hard delete
	{
		removeDirectoryHard(docDir);
	}
	else { // logical delete
		string trieFilePath = docDir + _docName + ".trie";
		if (fileExist(trieFilePath)) // delete .trie file
		{
			remove((char*)trieFilePath.c_str());
		}
		else { // Reinitialize all values
			_docName = "";
			_trieRootNode = TrieNode();
			_trieNodesArray.clear();
		}
	}
}

// FLUSH TO DO!