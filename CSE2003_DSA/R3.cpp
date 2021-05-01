
#include<iostream> 
#include<string.h>
#include<conio.h>
using namespace std; 
#define ALPHABET_SIZE (26) 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 
	bool isWordEnd;
	string meaning; 
}; 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 
	pNode->isWordEnd = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 
void insert(struct TrieNode *root, const string key,const string mean) 
{ 
	struct TrieNode *pCrawl = root; 

	for (int level = 0; level < key.length(); level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 
	pCrawl->isWordEnd = true; 
	pCrawl->meaning=mean;
} 
bool search(struct TrieNode *root, const string key) 
{ 
	int length = key.length(); 
	struct TrieNode *pCrawl = root; 
	for (int level = 0; level < length; level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 

		if (!pCrawl->children[index]) 
			return false; 

		pCrawl = pCrawl->children[index]; 
	} 

	return (pCrawl != NULL && pCrawl->isWordEnd); 
}  
bool isLastNode(struct TrieNode* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 
void suggestionsRec(struct TrieNode* root, string currPrefix) 
{ 
	if (root->isWordEnd) 
	{ 
		cout << currPrefix; 
		cout << endl; 
	} 
	if (isLastNode(root)) 
		return; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ 
		if (root->children[i]) 
		{ 
			currPrefix.push_back(97 + i); 
			suggestionsRec(root->children[i], currPrefix); 
			currPrefix.pop_back(); 
		} 
	} 
} 
int printAutoSuggestions(TrieNode* root, const string query) 
{ 
	struct TrieNode* pCrawl = root; 
	int level; 
	int n = query.length(); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 
		if (!pCrawl->children[index]) 
			return 0; 

		pCrawl = pCrawl->children[index]; 
	} 
	bool isWord = (pCrawl->isWordEnd == true); 
	bool isLast = isLastNode(pCrawl); 
	if (isWord && isLast) 
	{ 
		cout << query << endl; 
		cout <<"meaning is "<<pCrawl->meaning;
		return -1; 
	} 
	if (!isLast) 
	{ 
		string prefix = query; 
		cout<<query<<" not found did you mean \n";
		suggestionsRec(pCrawl, prefix); 
		return 1; 
	} 
} 
int main() 
{ 
	string check;
	struct TrieNode* root = getNode(); 
	insert(root, "hello","gsrgr"); 
	insert(root, "dog","gsrgr"); 
	insert(root, "doof","gsrgr"); 
	insert(root, "doon","gsrgr"); 
	cout<<"Enter the word ";
	cin>>check;
	int comp = printAutoSuggestions(root, check); 

	if (comp == 0) 
		cout << "No string found with this prefix\n"; 
		check.pop_back();
		int c=printAutoSuggestions(root, check); 
		if(c==0){
			cout<<"\nWord not found ";
		}
    getch();
	
	return 0; 
} 
