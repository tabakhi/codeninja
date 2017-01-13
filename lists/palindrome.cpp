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
  node *curr = head;
  while (curr)
  {
    cout << curr->val << " ";
    curr = curr->next;
  }

  cout << endl;
}

bool check2(node *head, node *&head2, int i, int &len)
{

  if (head->next)
  {
    if (check2(head->next, head2, i+1, ++len) == true)
    {
      if (i >= len/2)
      {
        int &val1 = head->val;
        int &val2 = head2->val;

        head2 = head2->next;
        return (val1 == val2);
      }
      else
      {
        return true;
      }
    }
    else 
    {
      return false;
    }
  }
  else
  {
    // base case of recursion we have reached end of list
    // compare contents of head and head2 (original head)
    int &val1 = head->val;
    int &val2 = head2->val;

    head2 = head2->next;
    return (val1 == val2);
  }
}

bool check(node *head)
{
  if (head == NULL)
    return true;

  int len = 1;
  int i = 1;
  return check2(head, head, i, len);
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

  cout << "List is a palindrome " << (check(head) ? "yes" : "no") << endl;

  return 0;
}

static void __attribute__ ((destructor)) destroyYnetdblib( void ) 
{                       /* completes or after exit() is called. */
   cout << "I am the destructor hahahaha" << endl;
}
