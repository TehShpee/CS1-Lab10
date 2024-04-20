#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct trie* next[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int wordLen = strlen(word);
    struct Trie* node = pTrie;
    struct Trie* temp;
    for (int i=0;i<wordLen;i++){
        if (node->next[((int)word[i]-97)] == NULL){
        node->next[((int)word[i]-97)] = (struct Trie*)malloc(sizeof(struct Trie));
        temp = node->next[((int)word[i]-97)];
        temp->count=0;
        for (int j=0; j<26; j++)
        temp->next[j] = NULL; 
        }
        node = node->next[((int)word[i]-97)];
    }
    node->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int wordLen = strlen(word);
    struct Trie* node = pTrie;
    for (int i=0;i<wordLen;i++){
        if(node->next[((int)word[i]-97)] == NULL){
            return 0;
        }
        node = node->next[((int)word[i]-97)];
    }
    return node->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* pointer = (struct Trie*)malloc(sizeof(struct Trie));
    pointer->count = 0;
    for (int i=0; i<26; i++)
    pointer->next[i] = NULL;
    return pointer;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* fp = fopen(filename,"r");
    int numWords;
    fscanf(fp,"%d",&numWords);
    int i;
    for(i=0;i<numWords;i++){
        pInWords[i] = (char*)malloc(sizeof(char)*256);
        fscanf(fp,"%s",pInWords[i]);
    }
    fclose(fp);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}