#include <iostream>
#include <tulip/Graph.h>

using namespace std;
using namespace tlp;

int main(int argc, char **argv)
{
  if(argc != 2)
    exit(-1);
  node n;
  tlp::Graph* g = tlp::loadGraph(argv[1]);
  cout << g  << endl;
  // forEach(n, g->getNodes())
  //   {
  //     cout << n  << endl;
  //   }

  return 0;
}
