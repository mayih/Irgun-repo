#ifndef __Projet__TrieSite__
#define __Projet__TrieSite__

#include <string>
#include <vector>
#include "TrieDoc.h"
#include <iostream>
#include "DirectoryFunctions.h"

namespace Trie {
    
    class TrieSite {
        
        std::string _siteName;
        std::vector<TrieDoc> _docList;
        bool _mounted;
        char _mountedType;

		// Added functions  -----
		void setMountedType(char mountedType);

		/*************************************************
		* FUNCTION
		*	throwIfUnmount
		* PARAMETERS
		*	exception - string to print in case od exception.
		* RETURN VALUE
		*	void
		* MEANING
		*	Throw an exception if the actual TrieSite is unmount.
		* SEE ALSO
		**************************************************/
		void throwIfNotMount(std::string exception);
		/*************************************************
		* FUNCTION
		*	throwIfNotMaintenance
		* PARAMETERS
		*	exception - string to print in case od exception.
		* RETURN VALUE
		*	void
		* MEANING
		*	Throw an exception if the actual TrieSite is not opened for maintenance.
		* SEE ALSO
		**************************************************/
		void throwIfNotMaintenance(std::string exception);
        

    public:
        
		// Default constructor
        TrieSite();

		/*************************************************
		* FUNCTION
		*	TrieSite
		* PARAMETERS
		*	string path	- directory full path
		*	char flag	- c: Create OR m: Mounted
		*	char rightFlag	- q: Query (read) OR m: Maintenance (Write)
		* RETURN VALUE
		* MEANING
		*	Constructor for a TrieSite.
		* SEE ALSO
		**************************************************/
        TrieSite(std::string path, char flag, char rightFlag = 'q');

		/*************************************************
		* FUNCTION
		*	create
		* PARAMETERS
		*	string fileName - directory full path
		* RETURN VALUE
		*	void
		* MEANING
		*	Create the directory for this TrieSite and clear the docList.
		* SEE ALSO
		**************************************************/
        void create(std::string fullPath);
		/*************************************************
		* FUNCTION
		*	mount
		* PARAMETERS
		*	string fullPath - full path of the directory to mount from.
		*	char flag - indicates the rights of the TrieSite (Read = q / Write = m).
		* RETURN VALUE
		*	void
		* MEANING
		*	It mounts a TrieSite from an existant directory, and loads all the documents inside.
		* SEE ALSO
		**************************************************/
		void mount(std::string fullPath, char flag = 'q');
		/*************************************************
		* FUNCTION
		*	unmount
		* PARAMETERS
		* RETURN VALUE
		*	void
		* MEANING
		*	Unmount the TrieSite (_mounted = false).
		* SEE ALSO
		**************************************************/
        void unmount();
		/*************************************************
		* FUNCTION
		*	putstopfl
		* PARAMETERS
		*	string filePath - path to the file .stop. It can be absolute or relative.
		* RETURN VALUE
		*	void
		* MEANING
		*	Change the stop.lst's content by the given file's content.
		* SEE ALSO
		**************************************************/
		void putstopfl(std::string filePath);
		/*************************************************
		* FUNCTION
		*	docExists
		* PARAMETERS
		*	string name - TrieDoc's name.
		* RETURN VALUE
		*	TrieDoc which its name matchs with the string parameter name .
		* MEANING
		*	Return a TrieDoc if found by its name. Otherwise return NULL.
		* SEE ALSO
		**************************************************/
		TrieDoc* docExists(std::string name);
		/*************************************************
		* FUNCTION
		*	docUpload
		* PARAMETERS
		*	string name - TrieDoc's name.
		*	char copyOrMove - Indicates if the document will be copied ('c') or moved ('m').
		* RETURN VALUE
		*	void
		* MEANING
		*	Upload a document to the Triesite's docList.
		* SEE ALSO
		**************************************************/
		void docUpload(std::string name, char copyOrMove);
    };
}
#endif /* defined(__Projet__TrieSite__) */
