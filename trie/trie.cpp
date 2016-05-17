#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

const size_t ALPHABET_SIZE = 26;

typedef struct trie
{
    trie()
    : eow(false)
    {
        for (size_t i = 0; i < ALPHABET_SIZE; i++)
        {
            nodes[i] = NULL;
        }
    };

    bool eow; // this marks end of a word
    trie *nodes[ALPHABET_SIZE];
} trie_t;

bool insert(trie_t *root, const string &word)
{
    trie_t *curr = root;

    for (size_t i = 0; i < word.size(); i++)
    {
        cout << "Inserting " << word[i] << endl;
        size_t index = word[i] - 'a';
        if (curr->nodes[index])
        {
            cout << "Following curr node for " << word[i] << endl;
            curr = curr->nodes[index];
        }
        else
        {
            cout << "Adding new node for " << word[i] << endl;
            trie_t *node = new trie_t();
            curr->nodes[index] = node;
            curr = node;
        }
    }

    curr->eow = true;
}

bool search(trie_t *root, const string &word)
{
    trie_t *curr = root;

    for (size_t i = 0; i < word.size(); i++)
    {
        size_t index = word[i] - 'a';
        if (curr->nodes[index])
        {
            cout << "Found node " << word[i] << endl;
            curr = curr->nodes[index];
        }
        else
        {
            return false;
        }
    }

    return (curr->eow);
}

void traverse(trie_t *start, string word, int depth, vector<string> & suggestions)
{
    trie_t *curr = start;
    cout << "Traversing at " << curr << " prefix = " << word << 
    " depth = " << depth << endl;

    if (curr->eow)
    {
        cout << "suggesting word " << word << endl;
        suggestions.push_back(word);
    }
    if (!depth)
    {
        return;
    }

    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        if (curr->nodes[i])
        {
            string word2 = word;
            word2.push_back(i + 'a');
            traverse(curr->nodes[i], word2, depth-1, suggestions);
        }
    }

    return;
}

// Suggest the passed in prefix + atmost 2 character words
int suggestPlusN(trie_t *root, const string &prefix, int depth)
{
    trie_t *curr = root;

    for (size_t i = 0; i < prefix.size(); i++)
    {
        size_t index = prefix[i] - 'a';
        if (curr->nodes[index])
        {
            cout << "Found node " << prefix[i] << endl;
            curr = curr->nodes[index];
        }
        else
        {
            return false;
        }
    }

    cout << "Checking for words starting with " << prefix << endl;

    vector<string> suggestions;
    string word = prefix;
    traverse(curr, word, depth, suggestions);

    cout << "Suggested words of length " << prefix.size() + depth << 
        " or less are:" << endl;
    for (size_t i = 0; i < suggestions.size(); i++)
    {
        cout << suggestions[i] << endl;
    }

    return (suggestions.size()) ? 1 : 0;
}

int main(int argc, char **argv)
{
    trie_t *root = new trie_t();

    insert(root, "artist");
    insert(root, "area");
    insert(root, "artisan");
    insert(root, "arts");
    insert(root, "arms");
    insert(root, "arsenal");
    insert(root, "array");
    insert(root, "armageddon");
    insert(root, "arid");

    string strNeedle = argv[1];
    int plusLen = atoi(argv[2]);

#if 0
    cout << "search for " << strNeedle << " returned " << 
        search(root, strNeedle) << endl;
#endif
    cout << "suggestions for " << strNeedle << " returned " << 
        suggestPlusN(root, strNeedle, plusLen) << endl;

    return 0;
}
