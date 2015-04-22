#include"TrieNode.h"

using namespace Trie;
using namespace std;

TrieNode::TrieNode(){

}
TrieNode::TrieNode(long int nodeSerialNr, long int firstOffset, long int nrOfOccurrences, unsigned char letter, bool wordEnd = false){

	_data._nodeSerialNr = nodeSerialNr;
	_data._firstOffset = firstOffset;
	_data._nrOfOccurrences = nrOfOccurrences;
	_data._letter = letter;
	_data._wordEnd = wordEnd;

	for (int i = 0; i < 256; i++)
		_links[i] = -1;
}