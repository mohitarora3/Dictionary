#include"Trie.h"
Dictionary::Dictionary()
{
	root=new TrieNode();
}
TrieNode::TrieNode():meaning("")  
{
				for(int i=0;i<ALPHABETS;i++)
				children[i]=NULL;
	
}
void Dictionary::insert(string word, string meaning)
{
	int i,index;
	TrieNode *temp=root;
	for(i=0;i<word.length();i++)
	{
		index=word[i]-'a';
		if(temp->children[index]==NULL)
			temp->children[index]=new TrieNode();
		temp=temp->children[index];
	}
	temp->meaning=meaning;
	
}
void Dictionary::autoComplete(TrieNode *root, string word,vector< string> &similarWords)
{
	/*   			
	objective: autosuggest words which are close to the entered word which isn't found in the dictionary 
	
	input parameters: none
				
	output value: none
	
	approach: a susbtring of the unfound word is received as a parameter to the function by the search 
			  function and that substring is successively permuted with the 26 alphabets to check whether
			  any word exists corresponding to that alphabet and appended to the word and printed as a 
			  suggestion to the user
	*/
	TrieNode *temp=root;
	if(root->meaning!="")
		{
			similarWords.push_back(word);
		}
	for(int i=0;i<ALPHABETS;i++)
	{
			if(temp->children[i])
				autoComplete(temp->children[i],word+(char)(i+'a'),similarWords);
	}
}
void Dictionary::search(string word)
{
	/*   			
	objective: gives the meaning of the word entered, and if the entered word is not present in the 
			   dictionary the application will say that the word is not found 
	
	input parameters: word to be searched
			  
	output value: none
	
	approach: the input word is send as a parameter to the search function which displays the word with its 
			  meaning (when found)
	*/
	int i,index;
	TrieNode* temp=root;
	vector <string> similarWords;
	for(i=0;i<word.length();i++)
	{
		index=word[i]-'a';
		if(temp->children[index]==NULL)
			{
				autoComplete(temp,word.substr(0,i),similarWords);
				break;
			}
		temp=temp->children[index];
	}
	if(temp->meaning=="")
		autoComplete(temp,word,similarWords);
	
	if(temp->meaning!="")
	cout<<"\n\tThe word \""<<word<<"\" was found with meaning \""<<temp->meaning<<"\"";
	else
	{
		cout<<"\n\tThe word \""<<word<<"\" was not found";
		if(similarWords.size()==0)
			return;
		cout<<"\n\tDid you mean? ";
		for(i=0;i<similarWords.size() && i<10;i++)
			{
				cout<<similarWords[i];
				(i==similarWords.size()-1 || i==9)?:cout<<" or ";
			}
	}
	
}
bool Dictionary:: isEmpty(TrieNode* temp)
{
	int i;
	for(i=0;i<ALPHABETS;i++)
		if(temp->children[i])
			return 0;
	return 1;
}
TrieNode* Dictionary::removeUtil(TrieNode*temp,string word,int depth=0)
{
	if(depth==word.size())
	{
		temp->meaning="";
		if(isEmpty(temp))
			{
				delete(temp);
				temp=NULL;
			}
		return temp;
			
	}
	int index=word[depth]-'a';
	temp->children[index]=removeUtil(temp->children[index],word, depth+1);
	if(isEmpty(temp) && temp->meaning=="")
	{
		delete temp;
		temp=NULL;
	}
	return temp;
}

void Dictionary::remove(string word)
{
	/*   			
	objective: to remove/delete a word and its meaning from the dictionary
	
	input parameters: word to be deleted
			  
	output value: none
	
	*/
	removeUtil(root,word);
	cout<<"\n\tThe word \""<<word<<" has been successfully removed. ";
	
}

TrieNode* Dictionary::clearDictionary(TrieNode *temp)
{
	for(int i=0;i<ALPHABETS;i++)
	{
		if(temp->children[i])
			temp->children[i]=clearDictionary(temp->children[i]);
	}
	delete temp;
	temp=NULL;
	return temp;
}
Dictionary ::~Dictionary()
{
	clearDictionary(root);
}

int main()
{
	/*   			
	objective: to implement a dictionary which gives the meaning of the word entered, and if the entered word
			   is not present in the dictionary the application will say that the word is not found, and then
			   will autosuggest words which are close to the entered word 
	
	input parameters: 
			   word: the word whose meaning the user wants to find
				
	output value: none
	
	approach: the input word is send as a parameter to the search function which displays the word with its 
			  meaning (when found)
	*/
	Dictionary obj;
	string word,meaning;
	ifstream fin;
	int n,ch;
	char c;
	cout<<"\n\tDICTIONARY";
	cout<<"\n\t1.EXTRACTING DATA FROM FILE";
	cout<<"\n\t2.PREDEFINED DATA";
	cout<<"\n\tEnter your choice: ";
	cin>>ch;
	switch(ch)
	{
	case 1:	fin.open("Dictionary.txt");
			while(!fin.eof())
			{
				fin>>word;
				fin>>meaning;
				obj.insert(word,meaning);
			}
			fin.close();
			break;
	case 2:	string words[]={"prodigious","potent","sway","corrosive","propaganda","drag","cart","card","carrot","carrom","carton"};
			string meanings[]={"very large in size","very strong in chemical or medicinal way","control","having the ability to wear down or destroy","information","pass slowly and tediously","a strong open vehicle with two or four wheels, typically used for carrying loads and pulled by a horse","a piece of thick, stiff paper or thin pasteboard, in particular one used for writing or printing on","a tapering orange-coloured root eaten as a vegetable","any strike and rebound, as a ball striking a wall and glancing off","a box"};
			n=sizeof(words)/sizeof(words[0]);
			for(int i=0;i<n;i++)
				obj.insert(words[i],meanings[i]);
			break;
	}
	cout<<"\n\tAdding words to the dictionary...";
	sleep(3);
	cout<<"\n\tAll the words have been suceesfully added to the dictionary.";		
	do
	{
		system("cls");
		cout<<"\n\t1.Search Word";
		cout<<"\n\t2.Remove Word";
		cout<<"\n\tEnter your choice: ";
		cin>>ch;
		cout<<"\n\tENTER WORD: ";
		cin>>word;
		
		switch(ch)
		{
			case 1:obj.search(word);
					break;
			case 2:obj.remove(word);
					break;
				
		}
		cout<<"\n\n\twant to continue (enter 'y' or 'Y') ";
		cin>>c;
	}while(c=='y'||c=='Y');
	return 0;

}
