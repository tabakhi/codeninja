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

// Post order traversal without recursion
// Second argument decides whether we will traverse 
// left side before right side

struct nodeVisitor
{
    nodeVisitor(node *e1, bool left, bool right)
    :
    e(e1),
    lvisited(left),
    rvisited(right)
    {
    }

    node *e;
    bool lvisited; // whether we visited left child
    bool rvisited; // whether we visited right child
};

void printTreePostOrder(node *root, bool leftFirst)
{
    stack<nodeVisitor> s;

    if (root)
    {
        s.push(nodeVisitor(root, false, false));
    }

    while (s.empty() == false)
    {
        nodeVisitor n = s.top();
        s.pop();
        
        if (n.e->left == NULL && n.e->right == NULL)
        {
            cout << n.e->val << endl;
        }
        else if (n.lvisited == false)
        {
            s.push(nodeVisitor(n.e, true, false));
            if (n.e->left)
            {
                s.push(nodeVisitor(n.e->left, false, false));
            }
        }
        else if (n.rvisited == false)
        {
            s.push(nodeVisitor(n.e, true, true));
            if (n.e->right)
            {
                s.push(nodeVisitor(n.e->right, false, false));
            }
        }
        else
        {
            cout << n.e->val << endl;
        }

    }



}

