#pragma once

#include "DirectoryFunctions.h"
#include <string>
using namespace std;

list<string> getFileNameList(string rootPath)
{

	if(rootPath.compare("")!=0)
		rootPath.append("\\");
	rootPath.append("*");

	list<string> myList;
	void*  hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA ffd;

	hFind = FindFirstFileA(rootPath.c_str(), &ffd);//finds first file in directory

	if (INVALID_HANDLE_VALUE == hFind)
	{
		FindClose(hFind);
		return myList;
	}

	do
	{
		// 
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			myList.push_back(ffd.cFileName);		
	}
	while (FindNextFileA(hFind, &ffd) != 0);
	FindClose(hFind);
	return myList;
}
list<string> getSubDirectoryNameList(string rootPath)
{
	if(rootPath.compare("")!=0)
		rootPath.append("\\");
	rootPath.append("*");

	list<string> result;

	void*  hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA ffd;


	hFind = FindFirstFileA(rootPath.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind) 
	{
		FindClose(hFind);
		return result;
	}

	do
	{
		// 
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			result.push_back(ffd.cFileName);		
	}
	while (FindNextFileA(hFind, &ffd) != 0);
	if(result.front().compare(".")==0)
		result.pop_front(); // remove '.' 
	if(result.front().compare("..")==0)
		result.pop_front(); // remove '..'
	FindClose(hFind);
	return result;
}
bool pathContainsDirectory(string path ,string dirName)
{
	list<string> directories = getSubDirectoryNameList(path);
	for(list<string>::iterator it = directories.begin(); it != directories.end() ; it++)
	{
		if( *it == dirName )
			return true;
	}
	return false;
}
bool pathContainsFile(string path, string fileName)
{
	list<string> files = getFileNameList(path);
	for(list<string>::iterator it = files.begin(); it != files.end() ; it++)
	{
		if( *it == fileName )
			return true;
	}
	return false;
}
bool fileHasStopFileBrother(string fileWithFullPath)
{
	string path = filePathToDirectoryPath(fileWithFullPath);
	string file = cutExtension(getFileName(fileWithFullPath));
	return pathContainsFile(path, file + ".stop");
}
bool fileHasTrieFileBrother(string fileWithFullPath)
{
	string path = filePathToDirectoryPath(fileWithFullPath);
	string file = cutExtension(getFileName(fileWithFullPath));
	return pathContainsFile(path, file + ".trie");
}
void createDirectory(string dirName)
{
	#ifdef _WIN32
		// Windows
		_mkdir(dirName.c_str());
	#elif __APPLE__
		// Mac OS
		mkdir(dirName.c_str());
	#endif

	if(errno ==	EEXIST)
		throw "can not create directory with name of an existing file or directory\n"; 
	if(errno ==	ENOENT)
		throw "can not create directory, Path was not found\n"; 
}
void removeDirectory(string dirName)
{
	#ifdef _WIN32
		// Windows
		_rmdir(dirName.c_str());
	#elif __APPLE__
		// Mac OS
		rmdir(dirName.c_str());
	#endif

	if(errno ==	ENOTEMPTY)
		throw "not a directory, the directory is not empty";
	if(errno ==	ENOENT)
		throw "path is invalid"; 
	if(errno ==	EACCES)
		throw "A program has an open handle to the directory"; 
}
void removeAllFilesInside(string dirName)
{
	try
	{
		list<string> fileList = getFileNameList(dirName);
		for (list<string>::iterator it = fileList.begin(); it != fileList.end(); it++)
		{
			remove( (dirName + '\\' + *it).c_str() );
		}
	}
	catch(char * ex)
	{
		throw ex;
	}
}
void removeDirectoryHard(string dirName)
{
	try
	{
		removeAllFilesInside(dirName);
		removeDirectory(dirName);
	}
	catch(char * ex)
	{
		throw ex;
	}
}
void copyFile(string fileName, string newLocation, string newName)
{
	int pos=fileName.find_last_of("\\");
	newLocation += "\\";
	if( newName == "")
	{
		newLocation += fileName.substr(pos+1, fileName.length() - pos);
	}
	else
	{
		newLocation += newName;
	}
	int result = CopyFileA(fileName.c_str(), newLocation.c_str(), false);
	if (result == 0)
		throw "Copy file failed\n";
}
void moveFile(string fileName, string newLocation, string newName)
{
	int pos = fileName.find_last_of("\\");
	newLocation += "\\";
	if( newName == "")
	{
		newLocation += fileName.substr(pos+1, fileName.length() - pos);
	}
	else
	{
		newLocation += newName;
	}
	int result = MoveFileA(fileName.c_str(), newLocation.c_str());
	if (result == 0)
		throw "Move file failed";			//file does not exist, file already exists
}
bool fileExist( string path )
{
	string fileName = getFileName(path);
	string folderPath = filePathToDirectoryPath(path);
	if (pathContainsFile(folderPath, fileName))
		return true;
	return false;
}
bool dirExist(string path)
{
	int access;
	#ifdef _WIN32
		// Windows
		access = _access(path.c_str(), 0);
	#elif __APPLE__
		// Mac OS
		access = access(path.c_str(), 0);
	#endif

	if (access == 0)
	{
		struct stat status;
		stat( path.c_str(), &status );

		if ( status.st_mode & S_IFDIR )
			return true;
		else
			return false;
	}
	else
		return false;
}
bool isRelativePath(string & path)
{
	size_t found;
	found = path.rfind(":");
	if (found != string::npos)
	{
		return false;
	}
	return true;
}
void removeSlash(string & path)
{
	if(path.length() == 0 )
		return;
	if(path.at(path.length() - 1) == '\\')
	{
		path = path.substr(0,path.length() - 1);
	}
}

// Modified by Moshe Uzan & Yair Behar
string getCurrentPath() 
{
	string currentPath;

	#ifdef _WIN32
		// Windows
		currentPath = resultCommand("echo %cd%");
	#elif __APPLE__
		// Mac OS
		currentPath = resultCommand("pwd");
	#elif __unix__ // all unices
		// Unix
		currentPath = resultCommand("pwd");
	#elif __linux__
		// linux
		currentPath = resultCommand("pwd");
	#endif

	// Remove the '\n' from the end of the string
	return currentPath.substr(0, currentPath.size() - 1);
}

string getFileName(string path)
{
	int start = path.find_last_of('\\')+1;
	int end = path.length();
	if(start == -1)
		return path;
	return path.substr(start,end-start);
}
string cutExtension(string fileNameWithExtension)
{
	int pos = fileNameWithExtension.find_last_of('.');
	return fileNameWithExtension.substr(0,pos);
}
string getExtension(string fileNameWithExtension)
{
	int start = fileNameWithExtension.find_last_of('.') + 1;
	int end = fileNameWithExtension.length();
	return fileNameWithExtension.substr(start,end-start);
}
void addExtension(string & fileWithoutExtension, string path)
{
	list<string> files = getFileNameList(path);
	for(list<string>::iterator it = files.begin(); it != files.end() ; it++)
	{
		if( (getExtension(*it) != "stop") && (getExtension(*it) != "trie") )
		{
			fileWithoutExtension = *it;
		}
	}
}
void modifyExtensionLogical(string & fileName, string extension)
{
	fileName = cutExtension(fileName) + "." + extension;
}
string getTopLevelFolder(string path)
{
	int pos = path.find_first_of('\\');
	return path.substr(0,pos);
}
string getBottomLevelFolder(string pathWithoutFile)
{
	int start = pathWithoutFile.find_last_of('\\') + 1;
	int end = pathWithoutFile.length();
	if(start == -1)
		return pathWithoutFile;
	return pathWithoutFile.substr(start,end-start);
}
string filePathToDirectoryPath(string filePath)
{
	int pos = filePath.find_last_of('\\');
	return filePath.substr(0,pos);
}
string getSiteFromFilePath(string filePath)
{
	int pos = filePath.find_last_of('\\');
	string str = filePath.substr(0,pos);
	pos = str.find_last_of('\\');
	return str.substr(0,pos);
}

// Added by Moshe Uzan & Yair Behar
std::string resultCommand(std::string command){
	FILE *f;
	char buffer[BUFSIZ];
	if ((f = _popen((char*)command.c_str(), "r")) == NULL)
		exit(1);
	while (fgets(buffer, BUFSIZ, f) != NULL)
		_pclose(f);
	return buffer;
}
// Added by Moshe Uzan & Yair Behar
std::string relativePathToAbsolute(std::string path)
{
	std::string tag;
	std::string currentPath;
	char separator;

	#ifdef _WIN32
		// Windows
		tag = "..\\";
		separator = '\\';
		currentPath = resultCommand("echo %cd%");
		char full[_MAX_PATH];
		return _fullpath( full, (char*)path.c_str(), _MAX_PATH );

	#elif __APPLE__ // MOSHE TU DEVRA ADAPTER avec realpath()
		// Mac OS
		tag = "../";
		separator = '/';
		currentPath = resultCommand("pwd");
	#elif __unix__ // all unices
		// Unix
		tag = "../";
		separator = '/';
		currentPath = resultCommand("pwd");
	#elif __linux__
		// linux
		tag = "../";
		separator = '/';
		currentPath = resultCommand("pwd");
	#endif

	// Remove the '\n' from the end of the string
	currentPath = currentPath.substr(0, currentPath.size() - 1);

	long int j = currentPath.length(), w = path.length(), k = 0;// j cursor in currentPath, k cursor in path
	bool tagAfterRep = false;

	for (int i = 0; i < path.length(); i++) {

		if (path.substr(i, 3) == tag) // if tag
		{
			k = i + 3; // move cursor in path
			w = path.length() - k;
			if (j > 0 && !tagAfterRep)
			{
				j--;
				while (currentPath[j] != separator)
				{
					j--; // move cursor in currentPath
				}
				tagAfterRep = false;
			}
		}
		else if (path[i] != separator && path[i] != '.')
		{
			tagAfterRep = true;
		}

	}
	if (w != path.length())
		path = currentPath.substr(0, j) + "/" + path.substr(k, w);

	return path;
}

vector<string> splitString(string str, string spliter) {
	vector<string> result;

	size_t pos = 0;
	std::string token;
	str += spliter;
	while ((pos = str.find(spliter)) != std::string::npos) {
		token = str.substr(0, pos);
		result.push_back(token);
		str.erase(0, pos + spliter.length());
	}
	return result;
}

string cutFileNameWithExtension(string pathToFile){
		string spliter = getPathSpliter(pathToFile);

		vector<string> splited = splitString(pathToFile, spliter);
		return splited[splited.size() - 1];
}

string getPathSpliter(std::string path){
	if (path.find("/") != std::string::npos)
		return "/";
	else
		return "\\";
}

void checkFlagValues(char param, char* values, int nbrOfValues){
	bool ok = false;
	int diff = 'a' - 'A';
	string ex = "Incorrect parameter. This parameter can't be equal to " + string(1, param) + ", it can only be equal to one of the following values:";


	for (int i = 0; i < nbrOfValues; i++)
	{
		ex += " " + string(1, values[i]);
		ok = (param == values[i]) || (param == values[i] - diff) || (param == values[i] + diff);
		if (ok)
			i = nbrOfValues;
	}

	if (!ok) 
		throw ex;
}

string addSlashToDirPath(string path){
	if (path[path.length() - 1] != '/') // Add '/' to the TrieSite's path if it doesn't have one.
		path += "/";
	return path;
}