#include "utils.h"

int main(int argc, char **argv)
{
    node *root = readTree(argv[1]);
    cout << "Printing tree breadth first" << endl;
    printTreeBF(root);

    cout << "Printing tree pre order" << endl;
    printTreePreOrder(root, true);
    return 0;
}
