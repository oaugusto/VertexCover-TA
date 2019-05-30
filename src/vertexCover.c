#include "vertexCover.h"

int min(int x, int y) {
    return (x < y) ? x : y;
}

int vertexCoverTreeHelper(graph* tree, V_t vertex, int isVertexCover, V_t dp[][2], int parent[]) {

    V_t sum = 0;
    V_t nChildren = 0;
    pointer next = NULL;

    //count the number of children for a node
    for (next = tree->edges[vertex]; next != NULL; next = next->next) {
        if (next->id != parent[vertex]) {
            nChildren++;
        }
    }

    if (nChildren == 0) {

        return isVertexCover;

    } else if (dp[vertex][isVertexCover] != -1) {

        return dp[vertex][isVertexCover];

    }

    for (next = tree->edges[vertex]; next != NULL; next = next->next) {
        V_t v = next->id;

        if (v != parent[vertex]) {
            parent[v] = vertex;

            if (isVertexCover == 0) {
                sum += vertexCoverTreeHelper(tree, v, 1, dp, parent);
            } else {
                sum += min(vertexCoverTreeHelper(tree, v, 1, dp, parent), \
                                vertexCoverTreeHelper(tree, v, 0, dp, parent));
            }
        }
    }
    
    dp[vertex][isVertexCover] = sum + isVertexCover;
    return dp[vertex][isVertexCover];
}

int vertexCoverTreeSolver(graph *tree, V_t root) {

    V_t i = 0; //index
    V_t min_value = 0;

    //array to store the values if the node in the solution or not
    V_t (*dp)[2] = malloc(sizeof(V_t) * tree->nNodes * 2);

    //parent array
    V_t* parent = (V_t*) malloc(sizeof(V_t) * tree->nNodes);

    //set all values and parent to -1
    for (i = 0; i < tree->nNodes; i++) {
        dp[i][0] = -1;
        dp[i][1] = -1;
        parent[i] = -1;
    }

    //this function will check if it is optimal to set 1 or 0
    min_value = min(vertexCoverTreeHelper(tree, root, 1, dp, parent), \
                        vertexCoverTreeHelper(tree, root, 0, dp, parent));
    
    free(dp);
    free(parent);

    return min_value;
}