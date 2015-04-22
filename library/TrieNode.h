namespace Trie
{
	class TrieNode
	{
		class Data
		{
		public:
			long int _nodeSerialNr;
			long int _firstOffset;
			long int _nrOfOccurrences;
			unsigned char _letter;
			bool _wordEnd;
		};

	public:
		Data _data;
		int _links[256];

		TrieNode();
		TrieNode(long int nodeSerialNr, long int firstOffset, long int nrOfOccurrences, unsigned char letter, bool wordEnd);
	};

}