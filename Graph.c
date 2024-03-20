// ---------------------------------------------------------
// Name: Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa3
// ---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Graph.h"
#include "List.h"

int time;

/*** Constructors-Destructors ***/

typedef struct GraphObj* Graph;

typedef struct GraphObj {
	int order;
	int size;
	List* neighbors;
	char* colors;
	int* parents;
	int* discover;
	int* finish;
} GraphObj;

Graph newGraph(int n) {
	if (n <= 0) {
		fprintf(stderr, "Error: Graph must contain at least one vertex.\n");
		exit(EXIT_FAILURE);
	}

	// ALLOCATE memory for Graph object.
	Graph G = malloc(sizeof(GraphObj));

	assert(G != NULL);

	// ASSIGN default values to Graph.
	G->order = n;
	G->size = 0;

	G->neighbors = (List *) malloc((n + 1) * sizeof(List));
	G->colors = calloc((n + 1), sizeof(char));
	G->parents = calloc((n + 1), sizeof(int));
	G->discover = calloc((n + 1), sizeof(int));
	G->finish = calloc((n + 1), sizeof(int));

	// INITIALIZE pointers to NULL.
	for (int i = 0; i <= n; i++) {
		G->neighbors[i] = NULL;
	}

	// INITIALIZE the dynamically allocated arrays.
	for (int i = 1; i <= n; i++) {
		G->neighbors[i] = newList();
		G->colors[i] = 'w';
		G->parents[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	return G;
}

void freeGraph(Graph *pG) {
	if (pG != NULL && *pG != NULL) {

		// FREE neighbors array.
		for (int i = 1; i <= (*pG)->order; i++) {
			freeList(&((*pG)->neighbors[i]));
		}

		free((*pG)->neighbors);

		// FREE colors array.
		free((*pG)->colors);

		// FREE parents array.
		free((*pG)->parents);

		// FREE discover array.
		free((*pG)->discover);

		// FREE finish array.
		free((*pG)->finish);

		// FREE Graph object.
		free(*pG);
		*pG = NULL;
	}
}

Graph transpose(Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling copyGraph() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	Graph transpose = newGraph(G->order);

	// REVERSE direction of edges of G.
	for (int u = 1; u <= G->order; u++) {
		List adj = G->neighbors[u];

		for (moveFront(adj); index(adj) >= 0; moveNext(adj)) {
			addArc(transpose, get(adj), u);
		}
	}

	return transpose;
}

Graph copyGraph(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Error: Calling copyGraph() on NULL Graph.\n");
		exit(EXIT_FAILURE);
	}

	Graph outGraph = newGraph(G->order);

	outGraph->size = G->size;

	// COPY arrays in G to new Graph.
	for (int i = 1; i <= G->order; i++) {
		outGraph->neighbors[i] = copyList(G->neighbors[i]);
		outGraph->colors[i] = G->colors[i];
		outGraph->parents[i] = G->parents[i];
		outGraph->discover[i] = G->discover[i];
		outGraph->finish[i] = G->finish[i];
	}

	return outGraph;
}

/*** Access functions ***/

int getOrder(Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getOrder() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }
        
	return G->order;
}

int getSize(Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getSize() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	return G->size;
}

int getParent(Graph G, int u) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getParent() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: Vertex argument not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

	return G->parents[u];
}

int getDiscover(Graph G, int u) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getDiscover() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

        if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: Vertex argument not in the range [1, %d]\n", G->order);
                exit(EXIT_FAILURE);
        }

        return G->discover[u];
}

int getFinish(Graph G, int u) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling getFinish() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

        if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: Vertex argument not in the range [1, %d]\n", G->order);
                exit(EXIT_FAILURE);
        }

        return G->finish[u];
}

/*** Helper functions ***/

void sortAppend(List L, int x) { // APPEND in increasing order.
	if (length(L) <= 0) {
		append(L, x);
		moveFront(L);
	} else {
		moveBack(L);

		while (x < get(L) && index(L) > 0) {
			movePrev(L);
		}
		
		if (x < get(L)) {
                        insertBefore(L, x);
                } else {
                        insertAfter(L, x);
                }
	}
}

/*** Manipulation procedures ***/

void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling addEdge() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
		fprintf(stderr, "Error: First vertex argument not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
	}

	if (v < 1 || v > G->order) {
                fprintf(stderr, "Error: Second vertex argument  not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

	sortAppend(G->neighbors[u], v);
	sortAppend(G->neighbors[v], u);

	G->size += 1;
}

void addArc(Graph G, int u, int v) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling addArc() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (u < 1 || u > G->order) {
                fprintf(stderr, "Error: First vertex argument not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

        if (v < 1 || v > G->order) {
                fprintf(stderr, "Error: Second vertex argument  not in the range [1, %d]\n", G->order);
		exit(EXIT_FAILURE);
        }

	List adj = G->neighbors[u];

	// CHECK for duplicate arcs.
	for (moveFront(adj); index(adj) >= 0; moveNext(adj)) {
		if (get(adj) == v) {
			return;
		}
	}

	sortAppend(G->neighbors[u], v);

	G->size += 1;
}

void visit(Graph G, int x, List S) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling visit() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

        G->discover[x] = (++time);
        G->colors[x] = 'g';

        List adj = G->neighbors[x];

        for (moveFront(adj); index(adj) >= 0; moveNext(adj)) {
                int y = get(adj);

                if (G->colors[y] == 'w') {
                        G->parents[y] = x;
                        visit(G, y, S);
                }
        }
	
	G->colors[x] = 'b';
	G->finish[x] = (++time);
	
	prepend(S, x);
}

void DFS(Graph G, List S) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling DFS() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (S == NULL) {
                fprintf(stderr, "Error: Calling DFS() on NULL List.\n");
                exit(EXIT_FAILURE);
	}

	if (length(S) != G->order) {
		fprintf(stderr, "Error: Length of List not equal to Graph order: %d\n", G->order);
		exit(EXIT_FAILURE);
	}

	for (int x = 1; x <= G->order; x++) {
		G->colors[x] = 'w';
		G->parents[x] = NIL;
	}

	time = 0;

	for (moveFront(S); index(S) >= 0; moveNext(S)) {
		int x = get(S);
		
		if (G->colors[x] == 'w') {
			visit(G, x, S);
		}
	}

	for (int i = 0; i < G->order; i++) {
		deleteBack(S);
	}
}

/*** Other operations ***/

void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
                fprintf(stderr, "Error: Calling printGraph() on NULL Graph.\n");
                exit(EXIT_FAILURE);
        }

	if (out == NULL) {
		fprintf(stderr, "Error: Could not access output file.\n");
		exit(EXIT_FAILURE);
	}

	// PRINT adjacency lists.
	for (int i = 1; i <= G->order; i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "%s", i==G->order?"\n":"");
	}
}
