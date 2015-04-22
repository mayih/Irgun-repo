#include "TrieDoc.h"

using namespace Trie;
using namespace std;

TrieDoc::TrieDoc(){ 
	_docName = "";
}


TrieDoc::TrieDoc(string docName){
	_docName = docName;
}