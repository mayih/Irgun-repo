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
		TrieDoc(std::string docName);
    };
    
}