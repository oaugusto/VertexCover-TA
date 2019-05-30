#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graph.h"
#include "../include/vertexCover.h"

int main(int argc, char **argv) {

    int n = 6;
    graph* tree = NULL;

/*
            0
          /   \
        1      2
      /   \    |
     3     4   5
  
*/
    tree = makeGraph(n);

    insertEdge(tree, 0, 1, 1);
    insertEdge(tree, 0, 2, 1);
    
    insertEdge(tree, 1, 3, 1);
    insertEdge(tree, 1, 4, 1);

    insertEdge(tree, 2, 5, 1);

    //printGraph(tree);

    printf("solution: %d\n", vertexCoverTreeSolver(tree, 1));

    return 0;
}