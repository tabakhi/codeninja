https://practice.geeksforgeeks.org/problems/bipartite-graph/1
/*
   Please note that it's Function problem i.e.
   you need to write your solution in the form of Function(s) only.
   Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*The function takes an adjacency matrix representation of the graph (g)
  and an integer(v) denoting the no of vertices as its arguments.
  You are required to complete below method */
bool isBipartite(int G[][MAX],int V)
{
  std::unordered_map<int, bool> added;
  std::queue<int> q;

  q.push(0);
  added[0] = false; // false -> left, true -> right

  int visited = 0;

  //for (int i = 0; i < V; i++)
  while (q.empty() == false || visited < V)
  {
    int vertex = -1;
    if (!q.empty())
    {
      vertex = q.front();
      q.pop();
    }
    else
    {
      vertex = visited;
    }

    ++visited;

    // walk all the edges starting at this vertex
    for (int v = 0; v < V; v++)
    {
      int u = G[vertex][v];

      if (!u)
      {
        // There is no edge, 
        continue;
      }

      // Has this vertex been traversed yet?
      if (added.find(v) == added.end())
      {
        q.push(v);
        added[v] = !added[vertex];
      } // if added
      // Otherwise, verify they have been added to different sets
      else if (vertex == v)
      {
        return false;
      }
      else if (added[v] == added[vertex])
      {
        return false;
      }
    } // for
  } // while

  return true;
  //Your code here
}
