// Compile with -std=c++11
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <sstream>      // std::istringstream

using namespace std;

typedef struct node
{
    node(const string &str)
    : left(NULL),
    right(NULL),
    parent(NULL),
    val(str)
    {
      ival = atoi(val.c_str());
    };

    node(const int i)
    : left(NULL),
    right(NULL),
    parent(NULL),
    ival(i)
    {
      ostringstream oss;
      oss << ival;
      val = oss.str();
    };

    node *left;
    node *right;
    node *parent;
    string val;
    int ival;
} node;

node * readTree(const string &file);
void printTreeBF(node *root);
void printTreePreOrder(node *root, bool leftFirst);
void printTreeInOrder(node *root, bool leftFirst);
void printTreePostOrder(node *root, bool leftFirst);

void insertSmart(node *root, int val);
