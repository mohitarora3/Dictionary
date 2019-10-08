#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<unistd.h>
#include<conio.h>
#define ALPHABETS 26
using namespace std;
class TrieNode
{
	//It represents single alphabet of a word and also tells whether meaningful word ends at this alphabet
	string meaning;
	TrieNode *children[ALPHABETS];
	friend class Dictionary;
	public:
		TrieNode();
};

class Dictionary
{
	TrieNode *root;
	
	public:
		Dictionary();
		bool isEmpty(TrieNode*);
		TrieNode*removeUtil(TrieNode*,string,int);
		TrieNode* clearDictionary(TrieNode*);
		void remove(string);
		void insert(string,string);
		void search(string);
		void autoComplete(TrieNode*,string,vector<string>&);
		~Dictionary();
};
