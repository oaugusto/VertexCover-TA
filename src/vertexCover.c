#include <stdlib.h>
#include "vertexCover.h"

V_t min(V_t x, V_t y) {
    return (x < y) ? x : y;
}

V_t vertexCoverTreeHelper(graph* tree, V_t vertex, int isVertexCover, \
                                            V_t dp[][2], int parent[]) {
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
    } else if (dp[vertex][isVertexCover] != -1) {   //Memoization
        return dp[vertex][isVertexCover];
    }

    for (next = tree->edges[vertex]; next != NULL; next = next->next) {
        V_t v = next->id;

        if (v != parent[vertex]) {
            parent[v] = vertex;     //not a parent

            if (isVertexCover == 0) {   //not vertex cover, must set children as vertex cover
                sum += vertexCoverTreeHelper(tree, v, 1, dp, parent);
            } else {                    //vertex cover, check both
                sum += min(vertexCoverTreeHelper(tree, v, 1, dp, parent), \
                                vertexCoverTreeHelper(tree, v, 0, dp, parent));
            }
        }
    }
    
    dp[vertex][isVertexCover] = sum + isVertexCover;
    return dp[vertex][isVertexCover];
}

V_t vertexCoverTreeSolver(graph *tree, V_t root) {

    V_t i = 0; //index
    V_t min_value = 0;

    //array to store the values if the node in cover set and if not in cover set
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

typedef struct pair {
    V_t a;
    V_t b;
    int valid;
} pair;

V_t vertexCoverHeuristic(graph* tree) {
    int i = 0, j = 0; //index
    pointer next = NULL;

    int vertexCoverSize = 0;
    int edgeSetSize = tree->nEdges;
    int *vertexCoverSet = NULL;
    pair *edgeSet = NULL;

    vertexCoverSet = malloc(sizeof(int) * tree->nNodes); //vertexCoverSet
    edgeSet = malloc(sizeof(pair) * tree->nEdges); //Set of edges

    //get all edges from the graph
    for (int i = 0; i < tree->nNodes; i++) {
        for (next = tree->edges[i]; next != NULL; next = next->next) {
            if (next->id < i) { //in order to not repeat edge
                edgeSet[j].a = i;
                edgeSet[j].b = next->id;
                edgeSet[j].valid = 1;

                j++;
            }
        }
    }
 
    //select edge and remove all other edges with its vertex a and b
    while (edgeSetSize != 0) {
        int i = 0, j = 0; //index
        int rand_value = rand();
        int index = rand_value % edgeSetSize; //get a random index

        pair edge;

        //select one edge from the set
        while (1) {
            if (edgeSet[i].valid) {
                if (index == 0) {
                    edge = edgeSet[i];
                    edgeSet[i].valid = 0;
                    edgeSetSize--;
                    break;
                }
                index--;
            }
            i++;
        }

        //edge nodes to cover set
        vertexCoverSet[vertexCoverSize] = edge.a;
        vertexCoverSet[vertexCoverSize + 1] = edge.b;

        vertexCoverSize += 2; //increment set size

        //remove from the vertexCoverSet
        for (j = 0; j < tree->nEdges; j++) {
            if (edgeSet[j].valid) {
                if (edgeSet[j].a == edge.a \
                        || edgeSet[j].b == edge.a) {
                    edgeSet[j].valid = 0;
                    edgeSetSize--;
                }
                if (edgeSet[j].a == edge.b \
                        || edgeSet[j].b == edge.b) {
                    edgeSet[j].valid = 0;
                    edgeSetSize--;
                }
            }
        }
    }

    free(vertexCoverSet);
    free(edgeSet);

    return vertexCoverSize; 
}