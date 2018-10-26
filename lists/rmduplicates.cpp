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

node*
removeSubList(node *start, node *end)
{
  node *curr = start;
  while (curr != end)
  {
    node *next1 = curr->next;
    delete curr;
    curr = next1;
  }

  node *successor = end->next;
  delete end;
  return successor;
}

node *
rmDuplicates(node *head)
{
  node *curr = head;
  node *newhead = head;
  node *prev = nullptr;
  node *start = nullptr;
  node *end = nullptr;
  node *prevstart = nullptr;

  while (curr)
  {
    if (curr->next && curr->val == curr->next->val)
    {
      if (start == nullptr)
      {
        prevstart = prev;
        start = curr;
        end = curr->next;
      }
      else
      {
        end = curr->next;
      }
      prev = curr;
      curr = curr->next;
    }
    else if (start && end && curr->next == nullptr)
    {
      node *successor = removeSubList(start, curr);
      if (start == head || prevstart == nullptr)
        newhead = nullptr;
      else
        prevstart->next = nullptr;

      break;
    }
    else if (start)
    {
      node *successor = end->next;
      removeSubList(start, end);
      if (start == head || prevstart == nullptr)
        newhead = successor;
      else
        prevstart->next = successor;

      start = nullptr;
      end = nullptr;
      prev = prevstart;
      prevstart = nullptr;
      curr = successor;
    }
    else
    {
      prev = curr;
      curr = curr->next;
    }

  } // while

  return newhead;
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
  cout << "Removing duplicates" << endl;
  head = rmDuplicates(head);
  printList(head);

  return 0;
}
