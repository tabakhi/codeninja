// 8.15: Check whether a singly linked list is palindromic
#include <stdlib.h>
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
  if (head == NULL)
  {
    return;
  }
  
  node *curr = head;

  do
  {
    cout << curr->val << " ";
    curr = curr->next;
  } while (curr != head);

  cout << endl;
}

int median(node *head)
{
  // This should return an error or throw exception etc.
  if (head == NULL)
  {
    return -1;
  }

  node *prev = NULL;
  node *curr = head;

  int i = 0;

  do
  {
    curr = curr->next;

    if (++i % 2 == 0)
    {
      if (i == 2)
      {
        cout << "Setting prev to head" << endl;
        prev = head;
      }
      else
      {
        cout << "Moving prev forward" << endl;
        prev = prev->next;
      }
    }

  } while (curr != head);

  if (prev == NULL)
  {
    return head->val;
  }
  else
  {
    if (i % 2 == 0)
    {
      return prev->val;
    }
    else
    {
      return prev->next->val;
    }
  }
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

  // IF head is there, prev is also there (i.e. not an empty list)
  if (head)
  {
    prev->next = head;
  }

  printList(head);
  cout << "The median of the sorted circular list is " << median(head)
    << endl;

  return 0;
}
