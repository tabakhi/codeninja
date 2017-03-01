#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <map>

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
  } while (curr != NULL);

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

node *fix(node *head, node *point)
{
  node *curr = head;

  while (curr && point)
  {
    if (curr->next == point)
    {
      cout << "Resetting " << curr->val << " to pont to NULL" << endl;
      curr->next = NULL;
      break;
    }
    curr = curr->next;
  }
}

void join(node *head, node *head2)
{
  node *prev = NULL;
  node *curr = head;

  while (curr)
  {
    prev = curr;
    curr = curr->next;
  }

  if (prev)
  {
    prev->next = head2;
    cout << "Joined " << prev->val << " to " << head2->val << endl;
  }

}

bool detectAndFix(node *head)
{
  node *h = head;
  node *t = head;

  while (1)
  {
    if (h->next == NULL || h->next->next == NULL)
    {
      cout << "No loop detected" << endl;
      return false;
    }

    h = h->next->next;
    t = t->next;

    if (h == t)
    {
      node *x = h;

      cout << "Loop detected at " << h->val << endl;

      // Breaking the loop
      // Save pointer to next node
      node *t2 = t->next;
      // Now reverse the list from head to where loop was detected
      // First make it a non loop though
      h->next = NULL;
      cout << "Reversing the list from hare to head" << endl;
      node *hr = reverse(head);

      node *found = check(hr, t2);
      assert(found);
      cout << "Loop occurs at " << found->val << endl;

      // Now restore the reversed list
      cout << "Restoring the reversed list from hare to head" << endl;
      node *head2 = reverse(hr);

      // Join the two disjoint lists back
      cout << "Joining the two disjoint lists back" << endl;
      join(head2, t2);

      // Now that we know where the list is looping 
      // break the loop
      cout << "Breaking the loop now" << endl;
      fix(t2, found);
      return true;
    }
  }
}

int main(int argc, char **argv)
{
  node *head = NULL;
  node *prev = NULL;

  std::map<int, node *> nodes;
  for (int i = 1; i < argc - 2; i++)
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
    nodes[atoi(argv[i])] = n;
  }

  const string strLoop = "yes";
  if (argv[argc-2] == strLoop)
  {
    prev->next = nodes[atoi(argv[argc - 1])];
  }

  detectAndFix(head);
  printList(head);
  return 0;
}
