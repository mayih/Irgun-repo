#pragma once
#include <windows.h>
#include <iostream>
#include <list>
#include <fstream>
#include <stdlib.h>
#include <direct.h>
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
//#include <sys/types.h>

using namespace std;

/* -------------- directory/files helper functions -------------- */
/*************************************************
* FUNCTION
*	getFileNameList
* PARAMETERS
*	string rootPath - 
* RETURN VALUE
*	list<string>
* MEANING
*	receive all file names in a specific folder
* SEE ALSO
*	
**************************************************/
list<string> getFileNameList(string rootPath);
/*************************************************
* FUNCTION
*	getSubDirectoryNameList
* PARAMETERS
*	string rootPath - 
* RETURN VALUE
*	list<string>
* MEANING
*	receive all sub-deirectory names in a specific folder
* SEE ALSO
*	
**************************************************/
list<string> getSubDirectoryNameList(string rootPath);
/*************************************************
* FUNCTION
*	pathContainsDirectory
* PARAMETERS
*	string path - a path
*	string dirName - directory name
* RETURN VALUE
*	bool
* MEANING
*	check if a path contains a specific directory.
* SEE ALSO
*	list<string> getSubDirectoryNameList(string rootPath)
**************************************************/
bool pathContainsDirectory(string path, string dirName);
/*************************************************
* FUNCTION
*	pathContainsFile
* PARAMETERS
*	string path - a path
*	string fileName - file name
* RETURN VALUE
*	bool
* MEANING
*	check if a path contains a specific file
* SEE ALSO
*	list<string> getFileNameList(string rootPath)
**************************************************/
bool pathContainsFile(string path, string fileName);
/*************************************************
* FUNCTION
*	fileHasStopFileBrother
* PARAMETERS
*	string fileWithFullPath - file full path
* RETURN VALUE
*	bool
* MEANING
*	check if a file has "stop" file brother.
* SEE ALSO
*	string filePathToDirectoryPath(string filePath)
*	string cutExtension(string fileNameWithExtension)
*	string getFileName(string path)
*	bool pathContainsFile(string path, string fileName)
**************************************************/
bool fileHasStopFileBrother(string fileWithFullPath);
/*************************************************
* FUNCTION
*	fileHasTrieFileBrother
* PARAMETERS
*	string fileWithFullPath - file full path
* RETURN VALUE
*	bool
* MEANING
*	check if a file has "trie" file brother.
* SEE ALSO
*	string filePathToDirectoryPath(string filePath)
*	string cutExtension(string fileNameWithExtension)
*	string getFileName(string path)
*	bool pathContainsFile(string path, string fileName)
**************************************************/
bool fileHasTrieFileBrother(string fileWithFullPath);
/*************************************************
* FUNCTION
*	createDirectory
* PARAMETERS
*	string dirName - directory full path
* RETURN VALUE
*	void
* MEANING
*	create a new dirctory
* SEE ALSO
*	
**************************************************/
void createDirectory(string dirName);
/*************************************************
* FUNCTION
*	removeDirectory
* PARAMETERS
*	string dirName - directory full path
* RETURN VALUE
*	void
* MEANING
*	remove a directory
* SEE ALSO
*	
**************************************************/
void removeDirectory(string dirName);
/*************************************************
* FUNCTION
*	removeAllFilesInside
* PARAMETERS
*	string dirName - directory full path
* RETURN VALUE
*	void
* MEANING
*	remove all files within a specific directory
* SEE ALSO
*	
**************************************************/
void removeAllFilesInside(string dirName);
/*************************************************
* FUNCTION
*	removeDirectoryHard
* PARAMETERS
*	string dirName - directory full path
* RETURN VALUE
*	void
* MEANING
*	Remove a directory with all the files inside
* SEE ALSO
*	void removeAllFilesInside(string dirName)
*	void removeDirectory(string dirName)
**************************************************/
void removeDirectoryHard(string dirName);
/*************************************************
* FUNCTION
*	copyFile
* PARAMETERS
*	string fileName - original file full path
*	string newLocation - destination path without file name
*	string newName - new file name
* RETURN VALUE
*	void
* MEANING
*	copy a file to a new destination
* SEE ALSO
*	
**************************************************/
void copyFile(string fileName, string newLocation, string newName = "");
/*************************************************
* FUNCTION
*	copyFile
* PARAMETERS
*	string fileName - original file full path
*	string newLocation - destination path without file name
*	string newName - new file name
* RETURN VALUE
*	void
* MEANING
*	move a file to a new destination
* SEE ALSO
*	
**************************************************/
void moveFile(string fileName, string newLocation, string newName = "");
/*************************************************
* FUNCTION
*	fileExist
* PARAMETERS
*	string path - file full path
* RETURN VALUE
*	bool
* MEANING
*	check if a file exists
* SEE ALSO
*	bool pathContainsFile(string path, string fileName)
**************************************************/
bool fileExist(string path);
/*************************************************
* FUNCTION
*	dirExist
* PARAMETERS
*	string path - directory full path
* RETURN VALUE
*	bool
* MEANING
*	check if a directory exists
* SEE ALSO
*	
**************************************************/
bool dirExist(string path);
/*************************************************
* FUNCTION
*	RelativePath
* PARAMETERS
*	string & path - directory full path
* RETURN VALUE
*	bool
* MEANING
*	determine if a path is absolute or relative
* SEE ALSO
*	
**************************************************/
bool relativePath(string & path);
/*************************************************
* FUNCTION
*	removeSlash
* PARAMETERS
*	string & path - directory full path
* RETURN VALUE
*	void
* MEANING
*	cut path last slash "c:\\dir1\\text\\" ==> "c:\\dir1\\text".
* SEE ALSO
*	
**************************************************/
void removeSlash(string & path);
/*************************************************
* FUNCTION
*	getCurrentPath
* PARAMETERS
* RETURN VALUE
*	std::string
* MEANING
*	Returns the current folder.
*	Folder from which you run the project executable file...
* SEE ALSO
*	
**************************************************/
string getCurrentPath();
/*************************************************
* Modified by Moshe Uzan & Yair Behar
* FUNCTION
*	getFileName
* PARAMETERS
*	string path - file full path
* RETURN VALUE
*	std::string
* MEANING
*	 receive file name without path  "c:\\dir1\\subdir2\\text.txt" ==> "text.txt".
* SEE ALSO
*	
**************************************************/
string getFileName(string path);
/*************************************************
* FUNCTION
*	cutExtension
* PARAMETERS
*	string fileNameWithExtension - file name with extension
* RETURN VALUE
*	std::string
* MEANING
*	receive a file name without extension  "text.txt" ==> "text".
* SEE ALSO
*	
**************************************************/
string cutExtension(string fileNameWithExtension);
/*************************************************
* FUNCTION
*	getExtension
* PARAMETERS
*	string fileNameWithExtension - file name with extension
* RETURN VALUE
*	std::string
* MEANING
*	receive file extension "text.txt" ==> "txt".
* SEE ALSO
*	
**************************************************/
string getExtension(string fileNameWithExtension);
/*************************************************
* FUNCTION
*	addExtension
* PARAMETERS
*	string & fileWithoutExtension - file name without extension
*	string path - file path
* RETURN VALUE
*	void
* MEANING
*	receive file name with its extension  "text" ==> "text.txt".
* SEE ALSO
*	list<string> getFileNameList(string rootPath)
*	string getExtension(string fileNameWithExtension)
**************************************************/
void addExtension(string & fileWithoutExtension, string path);
/*************************************************
* FUNCTION
*	modifyExtensionLogical
* PARAMETERS
*	string & fileName - file with extension
*	string extension - a desired extension
* RETURN VALUE
*	void
* MEANING
*	modify file name with a new extension  "text.old" ==> "text.new".
* SEE ALSO
*	string cutExtension(string fileNameWithExtension)
**************************************************/
void modifyExtensionLogical(string & fileName, string extension);
/*************************************************
* FUNCTION
*	getTopLevelFolder
* PARAMETERS
*	string path - directory full path
* RETURN VALUE
*	std::string
* MEANING
*	receive top-level directory "dir1\\subdir2\\text.txt" ==> "dir1".
* SEE ALSO
*	
**************************************************/
string getTopLevelFolder(string path);
/*************************************************
* FUNCTION
*	getBottomLevelFolder
* PARAMETERS
*	string pathWithoutFile - directory full path
* RETURN VALUE
*	std::string
* MEANING
*	receive bottom-level directory "c:\\dir1\\subdir2" ==> "subdir2".
* SEE ALSO
*	
**************************************************/
string getBottomLevelFolder(string pathWithoutFile);
/*************************************************
* FUNCTION
*	filePathToDirectoryPath
* PARAMETERS
*	string filePath - file full path
* RETURN VALUE
*	std::string
* MEANING
*	receive file's directory path "c:\\dir1\\subdir2\\text.txt" ==> "c:\\dir1\\subdir2".
* SEE ALSO
*	
**************************************************/
string filePathToDirectoryPath(string filePath);
/*************************************************
* FUNCTION
*	getSiteFromFilePath
* PARAMETERS
*	string filePath - file full path
* RETURN VALUE
*	std::string
* MEANING
*	receive file's site path "c:\\dir1\\text\\text.txt" ==> "c:\\dir1".
* SEE ALSO
*	
**************************************************/
string getSiteFromFilePath(string filePath);
/*************************************************
* Added by Moshe Uzan & Yair Behar
* FUNCTION
*	resultCommand
* PARAMETERS
*	string command - command to execute on the shell
* RETURN VALUE
*	std::string
* MEANING
*	Execute a command and return what's printed on the screen "echo hello" ==> "hello".
* SEE ALSO
*
**************************************************/
string resultCommand(std::string command);
/*************************************************
* Added by Moshe Uzan & Yair Behar
* FUNCTION
*	resultCommand
* PARAMETERS
*	string path - Relative path.
* RETURN VALUE
*	std::string
* MEANING
*	Convert a relative path to an absolute one "myDir" ==> "C:\\path\\to\\myDir".
* SEE ALSO
*
**************************************************/
string relativePathToAbsolute(std::string path);
/* -------------------------------------------------------------- */
