#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

int min(int x, int y) { return (x < y)? x: y; }

/*
 * https://www.geeksforgeeks.org/vertex-cover-problem-set-2-dynamic-programming-solution-tree/
 * Adaptando esse algoritmo
 */
int vCover(int node, int n, int m, graph *g, int *dp) {
    int i;

    // if node null return 0
    // if there is no child return 0

    // Calculate size of vertex cover when root is part of it 
    int size_incl = 0;
    // size_incl = 1 + vCover(root->left) + vCover(root->right); 
    
    // Calculate size of vertex cover when root is not part of it 
    int size_excl = 0; 
    // if (root->left) 
    //   size_excl += 1 + vCover(root->left->left) + vCover(root->left->right); 
    // if (root->right) 
    //   size_excl += 1 + vCover(root->right->left) + vCover(root->right->right); 
  
    // Minimum of two values is vertex cover, store it before returning 
    // root->vc =  min(size_incl, size_excl); 
    dp[node] = min(size_incl, size_excl);

    return dp[node];
}

int main(int argc, char **argv) {

    int n, m, u, v, i;
    graph* g = NULL;
    int *dp;

    scanf("%d %d", &n, &m);

    dp = (int *)malloc(n * sizeof(int *));
    memset(dp, 0, n*sizeof(int));
    
    g = makeGraph(n);

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        insertEdge(g, u, v, 1);
        insertEdge(g, v, u, 1);
    }

    printf("%d\n", vCover(0, n, m, g, dp));

    return 0;
}