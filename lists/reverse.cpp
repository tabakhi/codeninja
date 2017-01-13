// Detect whether two linked lists intersect and at what node
// Source: http://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

class node
{
 public:
  node(int aval = 0, node *anext = NULL) :
    next(anext),
    val(aval)
  {}

  node *next;
  int val;
};

void printList(node *head)
{
  node *curr = head;
  while (curr)
  {
    cout << curr->val << " ";
    curr = curr->next;
  }

  cout << endl;
}

node *reverse(node *head)
{
  if (head == NULL)
  {
    return head;
  }

  node *curr = head;
  node *prev = NULL;
  node *next = NULL;

  while (curr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  return prev;
}

int main(int argc, char **argv)
{
  node *head = NULL;
  node *prev = NULL;

  for (int i = 1; i < argc; i++)
  {
    node *n = new node(atoi(argv[i]), NULL);
    if (head == NULL)
    {
      head = n;
    }

    if (prev)
    {
      prev->next = n;
    }

    prev = n;
  }

  printList(head);
  head = reverse(head);
  printList(head);

  return 0;
}
