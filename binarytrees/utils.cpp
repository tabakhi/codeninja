// Compile with -std=c++11
#include "utils.h"

using namespace std;

// Node is of the form 45,0 e.g. node 0 has value 45
node *parseNode(const string &str, uint32_t &rank)
{
    char *str2 = strdup(str.c_str());
    
    char *saveptr = NULL;

    char * strVal = strtok_r(str2, ",", &saveptr);
    char * strRank = strtok_r(NULL, ",", &saveptr);

    assert(strVal);
    assert(strRank);

    node *x = new node(strVal);

    istringstream iss(strRank);
    iss >> rank;

    free(str2);
    return x;
}

void setChild(unordered_map<uint32_t, node *>& nodes, 
        node *curr,
        uint32_t rank)
{
    // E.g. parent of 1 and 2 is 0 and so on...
    uint32_t parentRank = (rank-1) / 2;

    if (rank & 1)
    {
        nodes[parentRank]->left = curr;
        cout << "Assigning # " << rank << " node as left child of "
            << parentRank << endl;
    }
    else
    {
        nodes[parentRank]->right = curr;
        cout << "Assigning # " << rank << " node as right child of "
            << parentRank << endl;
    }

    curr->parent = nodes[parentRank];

}


node * readTree(const string &file)
{
    unordered_map<uint32_t, node *> nodes;
    ifstream inFile(file.c_str());

    cout << "Creating binary tree from " << file << endl;

    node *root = NULL;

    uint32_t height = 0;

    while (inFile.good())
    {
        string str;
        getline(inFile, str);

        cout << "Parsing nodes at height " << height++ << endl;
        cout << str << endl;

        char *str2 = strdup(str.c_str());

        char *saveptr = NULL;
        char *elem = strtok_r(str2, " ", &saveptr);

        if (elem == NULL)
        {
            continue;
        }

        uint32_t rank;
        node *curr = parseNode(elem, rank);
        nodes[rank] = curr;

        if (rank == 0)
        {
            cout << "Assigning root " << curr->val << endl;
            root = curr;
            continue;
        }

        setChild(nodes, curr, rank);

        while (char *elem2 = strtok_r(NULL, " ", &saveptr))
        {
            curr = parseNode(elem2, rank);
            nodes[rank] = curr;

            setChild(nodes, curr, rank);
        }

        free(str2);
    }

    return root;
}

// Print the tree breadth first
void printTreeBF(node *root)
{
    queue<node *> nodes;

    if (root)
    {
        nodes.push(root);
    }

    while (nodes.empty() == false)
    {
        node *curr = nodes.front();
        nodes.pop();

        cout << curr->val << endl;

        if (curr->left)
        {
            nodes.push(curr->left);
        }
        if (curr->right)
        {
            nodes.push(curr->right);
        }
    }
}

// Pre order traversal without recursion
// Second argument decides whether we will traverse 
// left side before right side
void printTreePreOrder(node *root, bool leftFirst)
{
    stack<node *> nodes;

    if (root)
    {
        nodes.push(root);       
    }

    while (nodes.empty() == false)
    {
        node *curr = nodes.top();
        nodes.pop();

        cout << curr->val << endl;

        if (leftFirst)
        {
            if (curr->right)
            {
                nodes.push(curr->right);
            }
            if (curr->left)
            {
                nodes.push(curr->left);
            }
        }
        else
        {
            if (curr->left)
            {
                nodes.push(curr->left);
            }
            if (curr->right)
            {
                nodes.push(curr->right);
            }
        }
    }

}

// In order traversal without recursion
// Second argument decides whether we will traverse 
// left side before right side
void printTreeInOrder(node *root, bool leftFirst)
{
    stack<node *> nodes;

    while (root || !nodes.empty())
    {
        if (root)
        {
            nodes.push(root);
            root = root->left;
        }
        else
        {
            root = nodes.top();
            nodes.pop();
            cout << root->val << endl;
            root = root->right;
        }
    }

}

// Post order traversal without recursion
// Second argument decides whether we will traverse 
// left side before right side

// To do a postorder traversal we do a reverse pre order traversal
// where we print right child before left child.
// I.e. Parent, Right, Left
// Instead of printing preorder traversal nodes we push them on
// stack and then after visiting all the nodes we just print the 
// stack
// http://www.geeksforgeeks.org/iterative-postorder-traversal/
void printTreePostOrder(node *root, bool leftFirst)
{
    stack<node *> s1, s2;

    if (root)
    {
        s1.push(root);
    }

    while (s1.empty() == false)
    {
        node *curr = s1.top();
        s1.pop();

        s2.push(curr);

        if (curr->left)
        {
            s1.push(curr->left);
        }
        if (curr->right)
        {
            s1.push(curr->right);
        }
    }

    while (s2.empty() == false)
    {
        node *curr = s2.top();
        s2.pop();

        cout << curr->val << endl;
    }
}

void insertSmart(node *n, int val)
{
  if (val > n->ival) 
  {
    if (n->right == NULL)
    {
      ostringstream oss;
      oss << val;
      string strVal = oss.str();
      node *r = new node(strVal);
      n->right = r;

      cout << "Inserted " << val << " into right node of " << n->val 
        << endl;
    }
    else 
    {
      insertSmart(n->right, val);
    }
  }
  else if (val < n->ival)
  {
    if (n->left == NULL)
    {
      ostringstream oss;
      oss << val;
      string strVal = oss.str();
      node *l = new node(strVal);
      n->left = l;

      cout << "Inserted " << val << " into left node of " << n->val 
        << endl;
    }
    else 
    {
      insertSmart(n->left, val);
    }
  }
  else
  {
    cout << "Duplicate entry cannot be inserted into the node" << endl;
    assert(0);
  }
}

