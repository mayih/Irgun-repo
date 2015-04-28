//
//  TrieSite.cpp
//  Projet
//
//  Created by Moshe Uzan & Jeremy Behar on 25/03/2015.
//  Copyright (c) 2015 Moshe Uzan & Jeremy Behar. All rights reserved.
//

#include "TrieSite.h"

using namespace Trie;
using namespace std;

TrieSite::TrieSite(): _mounted(false), _mountedType('q'), _siteName(""){}
TrieSite::TrieSite(std::string path, char flag, char mountedType)
{
	_siteName = relativePathToAbsolute(path);

	// Create
	if (flag == 'c' || flag == 'C')
	{
		create(_siteName);
	}
	// Mount
	else if (flag == 'm' || flag == 'M') {
		mount(_siteName, mountedType);
	}
}

void TrieSite::create(std::string fullPath)
{
	createDirectory(fullPath);
	_docList.clear();

	// create stop.lst file
	string stopFilePath = fullPath + "/stop.lst";
	ofstream flux(stopFilePath);

	_mounted = true;
}

void TrieSite::mount(std::string fullPath, char mountedType)
{
    // Check if the directory exists
	if (!dirExist(fullPath))
	{
		throw "Directory not found.";
	}

	// Fill doclist
	TrieDoc current;
	for each (std::string dir in getSubDirectoryNameList(fullPath))
	{
		//current = TrieDoc(); // NEED TO FILL THE TRIEDOC
		//_docList.push_back(current);
	}

	_mounted = true;
	setMountedType(mountedType);
}

void TrieSite::unmount()
{
	_mounted = false;
}

void TrieSite::putstopfl(std::string filePath){
	// Check if mounted and its rights
	throwIfNotMount("Trying to modify the stop.lst file of a non mounted TrieSite.");
	throwIfNotMaintenance("Trying to write in a TriSite's stop.lst without having the right to modify it.");

	copyFile(filePath, _siteName, "stop.lst");
}

TrieDoc* TrieSite::docExists(string name){
	// Check if TrieSite mounted
	throwIfNotMount("Trying to read a docList of an unmount Triesite.");

	for each (TrieDoc doc in _docList)
	{
		if (doc._docName == name)
		{
			return &doc;
		}
	}

	return NULL;
}

void TrieSite::docUpload(std::string path, char copyOrMove){
	// Check if mounted and its rights
	throwIfNotMount("Can't upload a document to an unmount TrieSite.");
	throwIfNotMaintenance("Can't upload a document to a reading TrieSite.");



	// Check if not existant
	if (docExists(path) != NULL)
		throw "This document already exists.";

	//TrieDoc newComer = TrieDoc(path);
	// newComer.putDoc();
	//_docList.push_back(newComer);

	// ...
}

string TrieSite::docdownload(string docName, string outPath = ""){
	TrieDoc *selected = docExists(docName);

	// Check if file exists
	if (selected == NULL)
		throw "Download failed. This file is inexistant.";

	// Copy
	string path = _siteName + "/" + selected->_docName;
	//selected->getDoc(path, outPath);
}

// Private functions ----
void TrieSite::setMountedType(char mountedType){
	// Check mountedType value
	if (mountedType != 'q' && mountedType != 'Q' && mountedType != 'm' && mountedType != 'M')
		throw "Incorrect mountedType value";

	_mountedType = mountedType;
}
void TrieSite::throwIfNotMount(string exception){
	if (!_mounted)
	{
		throw exception;
	}
}
void TrieSite::throwIfNotMaintenance(string exception){
	if (_mountedType != 'm' && _mountedType != 'M')
	{
		throw exception;
	}
}
