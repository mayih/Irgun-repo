#include<string>
#include"TrieNode.h"
#include<vector>
namespace Trie
{
    class TrieDoc
    {
    public:
        std::string _docName;
        TrieNode _trieRootNode;
        TrieNode _trieBuff[10];
        std::vector<TrieNode> _trieNodesArray;
        
        TrieDoc();

		/*************************************************
		* FUNCTION
		*	TrieDoc
		* PARAMETERS
		*	string triePath - Full path to the TrieSite
		*	string filePath - Document's path.
		* RETURN VALUE
		*	Void
		* MEANING
		*	Create a TrieDoc from the given file.
		* SEE ALSO
		**************************************************/
		TrieDoc(std::string triePath, std::string filePath);

		/*************************************************
		* FUNCTION
		*	putDoc
		* PARAMETERS
		*	string triePath - Full path to the TrieSite
		*	string filePath - Document's path.
		*	char copyOrMove - Flag which indicates to copyy (c) or to move (m) the document to ou TrieSite.
		* RETURN VALUE
		*	Void
		* MEANING
		*	Add a document to a TrieSite's folder (create document's folder, add files .stop & .trie and copy/move the file) without indexing.
		* SEE ALSO
		**************************************************/
		void putDoc(std::string triePath, std::string filePath, char copyOrMove = 'c');
		/*************************************************
		* FUNCTION
		*	getdoc
		* PARAMETERS
		*	string triePath - Full path to the TrieSite
		*	string destination - Destination's path (absolute/relative).
		* RETURN VALUE
		*	Void
		* MEANING
		*	Copy the TrieDoc's file to the destination path (default: current folder).
		* SEE ALSO
		**************************************************/
		void getdoc(std::string triePath, std::string destination = "");
		/*************************************************
		* FUNCTION
		*	del
		* PARAMETERS
		*	string triePath - Full path to the TrieSite
		*	char wayToDelete - Indicates the way to delete: l/L = logical, or p/P = physic.
		* RETURN VALUE
		*	Void
		* MEANING
		*	Delete a document from the Trie.
		* SEE ALSO
		**************************************************/
		void del(std::string triePath, char wayToDelete = 'l');
		/*************************************************
		* FUNCTION
		*	flush
		* PARAMETERS
		*	string triePath - Full path to the TrieSite
		* RETURN VALUE
		*	Void
		* MEANING
		*	Save the trieNodeArray into the TrieDoc's .trie file, using the _trieBuff attribut as a blocking factor.
		* SEE ALSO
		**************************************************/
		void flush(std::string triePath);
    };
    
}