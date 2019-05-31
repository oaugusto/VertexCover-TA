#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "vertexCover.h"

int main(int argc, char **argv) {
    int n, m, u, v, i;
    graph* g = NULL;
    int *dp;

    FILE *fp = NULL;
    if (argc < 2) {
        printf("erro: missing parameters\n");
        return 0;
    }
    fp = fopen(argv[1], "r");

    fscanf(fp, "%d %d", &n, &m);

    dp = (int *)malloc(n * sizeof(int *));
    memset(dp, 0, n*sizeof(int));

    g = makeGraph(n);

    for (i = 0; i < m; i++) {
        fscanf(fp, "%d %d", &u, &v);
        insertEdge(g, u, v, 1);
        // insertEdge(g, v, u, 1);
    }

    printf("%d\n", vertexCoverTreeSolver(g, 0));

//     int n = 6;
//     graph* tree1 = NULL;
//     graph* tree2 = NULL;
//     graph* tree3 = NULL;
//     graph* tree4 = NULL;

// /*
//             0
//           /   \
//         1*     2*
//       /   \    |
//      3     4   5
  
// */
//     tree1 = makeGraph(n);

//     insertEdge(tree1, 0, 1, 1);
//     insertEdge(tree1, 0, 2, 1);
    
//     insertEdge(tree1, 1, 3, 1);
//     insertEdge(tree1, 1, 4, 1);

//     insertEdge(tree1, 2, 5, 1);

//     printGraph(tree1);

//     printf("solution: %d\n\n", vertexCoverTreeSolver(tree1, 0));

// /*
//             0
//          /    \
//         1*     2*
//       /   \     \
//     3      4*    5
//            / \
//           6   7
// */

//     tree2 = makeGraph(8);

//     insertEdge(tree2, 0, 1, 1);
//     insertEdge(tree2, 0, 2, 1);

//     insertEdge(tree2, 1, 3, 1);
//     insertEdge(tree2, 1, 4, 1);

//     insertEdge(tree2, 2, 5, 1);

//     insertEdge(tree2, 4, 6, 1);
//     insertEdge(tree2, 4, 7, 1);  

//     printGraph(tree2);

//     printf("solution: %d\n\n", vertexCoverTreeSolver(tree2, 0));

// /*
//         3*
//       / | \
//      0  1  2
// */

//     tree3 = makeGraph(4);

//     insertEdge(tree3, 3, 0, 1);
//     insertEdge(tree3, 3, 1, 1);
//     insertEdge(tree3, 3, 2, 1);

//     printGraph(tree3);

//     printf("solution: %d\n\n", vertexCoverTreeSolver(tree3, 3));


// /*
//         Tree: null
//  */

//     tree4 = makeGraph(1);

//     printGraph(tree4);

//     printf("solution: %d\n\n", vertexCoverTreeSolver(tree4, 0));

    return 0;
}