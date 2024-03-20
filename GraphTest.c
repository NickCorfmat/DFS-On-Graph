// ---------------------------------------------------------
// Name: Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa3
// ---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Graph.h"
#include "List.h"

int main() {
    Graph G = newGraph(7);
    fprintf(stdout, "Order: %d\n\n", getOrder(G));
    fprintf(stdout, "Size before calling addArc(): %d\n", getSize(G));
    
    addEdge(G, 1, 2);
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 1);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    addEdge(G, 6, 4);
    addEdge(G, 7, 3);
    addEdge(G, 7, 2);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 2);
    addEdge(G, 3, 4);
    addEdge(G, 5, 5);
    addEdge(G, 6, 2);
    addEdge(G, 6, 7);
    addEdge(G, 7, 4);
    addEdge(G, 7, 5);
    addEdge(G, 7, 7);
    addEdge(G, 4, 2);
    addEdge(G, 4, 1);
    
    fprintf(stdout, "Size after calling addArc(): %d\n\n", getSize(G));
    
    fprintf(stdout, "Running DFS\n\n");

    List S = newList();

    for (int i = 1; i <= getOrder(G); i++) {
        append(S, i);
    }

    // Graph G Tests

    DFS(G, S);

    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(stdout, "G - Discover vertex %d: %d\n", i, getDiscover(G, i));
    }

    fprintf(stdout, "\n");

    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(stdout, "G - Finish vertex %d: %d\n", i, getFinish(G, i));
    }

    fprintf(stdout, "\n");

    fprintf(stdout, "Graph Parents:\n");

    for (int i = 1; i <= getOrder(G); i++) {
            fprintf(stdout, "Vertex %d: %d\n", i, getParent(G, i));
    }

    fprintf(stdout, "\n");

    // Transpose G Tests
    
    Graph T = transpose(G);
    fprintf(stdout, "Transpose:\n");
    printGraph(stdout, T);

    DFS(T, S);

    fprintf(stdout, "Size of transpose: %d\n\n", getSize(T));

    for (int i = 1; i <= getOrder(T); i++) {
        fprintf(stdout, "Transpose - Discover vertex %d: %d\n", i, getDiscover(T, i));
    }

    fprintf(stdout, "\n");

    for (int i = 1; i <= getOrder(T); i++) {
        fprintf(stdout, "Transpose - Finish vertex %d: %d\n", i, getFinish(T, i));
    }

    fprintf(stdout, "\n");

    fprintf(stdout, "Transpose Parents:\n");

    for (int i = 1; i <= getOrder(T); i++) {
            fprintf(stdout, "Vertex %d: %d\n", i, getParent(T, i));
    }

    fprintf(stdout, "\n");

    fprintf(stdout, "List S:\n");
    printList(stdout, S);

    fprintf(stdout, "\n");

    // Copy of G Tests
    
    Graph C = copyGraph(G);
    fprintf(stdout, "Copy:\n");
    printGraph(stdout, C);

    fprintf(stdout, "Size of copy Graph: %d\n\n", getSize(C));

    for (int i = 1; i <= getOrder(C); i++) {
        fprintf(stdout, "Copy Graph - Discover vertex %d: %d\n", i, getDiscover(C, i));
    }

    fprintf(stdout, "\n");

    for (int i = 1; i <= getOrder(C); i++) {
        fprintf(stdout, "Copy Graph - Finish vertex %d: %d\n", i, getFinish(C, i));
    }

    fprintf(stdout, "\n");

    fprintf(stdout, "Copy Graph Parents:\n");

    for (int i = 1; i <= getOrder(C); i++) {
	    fprintf(stdout, "Vertex %d: %d\n", i, getParent(C, i));
    }

    fprintf(stdout, "\n");

    fprintf(stdout, "List S:\n");
    printList(stdout, S);
    
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    
    freeList(&S);
    
    return 0;
}
