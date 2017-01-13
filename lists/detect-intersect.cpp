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

int getListSize(node *head)
{
  int sz = 0;
  node *curr = head;
  while (curr)
  {
    ++sz;
    curr = curr->next;
  }

  return sz;
}

node * descend(node *head, int len)
{
  if (len == 0)
  {
    return head;
  }

  node *curr = head;
  while (len-- > 0)
  {
    curr = curr->next;
  }

  return curr;
}

node * check(node *head1, node *head2)
{
  if (head1 == NULL || head2 == NULL)
  {
    return NULL;
  }

  int sz1 = getListSize(head1);
  int sz2 = getListSize(head2);

  cout << "size of lists are " << sz1 << " and " << sz2 << endl;

  node *curr1 = head1;
  node *curr2 = head2;

  if (sz1 < sz2)
  {
    curr2 = descend(head2, sz2 - sz1);
    cout << "Now curr2 is " << curr2->val << endl;
  }
  else if (sz2 < sz1)
  {
    curr1 = descend(head1, sz1 - sz2);
    cout << "Now curr1 is " << curr1->val << endl;
  }

  while (curr1 && curr2)
  {
    if (curr1 == curr2)
    {
      return curr1;
    }

    curr1 = curr1->next;
    curr2 = curr2->next;
  }

  return NULL;

}


int main(int argc, char **argv)
{
  node *head = NULL;
  node *head1 = NULL;
  node *head2 = NULL;
  node *prev = NULL;

  int firstListSize = atoi(argv[1]);

  for (int i = 2; i < firstListSize + 2; i++)
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

  head1 = head;
  printList(head1);

  head = NULL;
  prev = NULL;

  int secondListSize = atoi(argv[firstListSize + 2]);

  for (int i = firstListSize + 3; i < firstListSize + secondListSize + 3; i++)
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

  head2 = head;
  printList(head2);

  bool bIntersect = strcmp("yes", argv[firstListSize + secondListSize + 3]) == 0;
  if (bIntersect)
  {
    // index in the 1st list where the 2nd list will terminate
    int index = atoi(argv[firstListSize + secondListSize + 4]);

    node *curr = head1;
    prev = head1;
    for (int i = 1; i < index; i++)
    {
      curr = curr->next;
    }

    node *mergePoint = curr;

    curr = head2;
    prev = head2;
    while (curr)
    {
      prev = curr;
      curr = curr->next;
    }

    if (prev)
    {
      prev->next = mergePoint;
      cout << "node " << prev->val << " intersects at " << mergePoint->val <<
        endl;
    }
  }

  node *found = check(head1, head2);
  if (found)
  {
    cout << "Lists intersect at " << found->val << endl;
  }
  else
  {
    cout << "Lists don't intersect" << endl;
  }

  return 0;
}
