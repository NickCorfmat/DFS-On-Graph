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

void printComponents(FILE* out, Graph G, List L) {
	if (L == NULL) {
		fprintf(stderr, "Error: Calling printComponents() on NULL List object.\n");
		exit(EXIT_FAILURE);
	}

	int numOfComponents = 0;

	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		if (getParent(G, get(L)) == NIL) {
			numOfComponents += 1;
		}
	}

	fprintf(out, "G contains %d strongly connected component%s:\n", numOfComponents, numOfComponents==1?"":"s");

	int i = 0, comp = 1;

	for (moveBack(L); index(L) >= 0; movePrev(L)) {

		int parent = getParent(G, get(L));

		if (parent == NIL) {
			fprintf(out, "Component %d: ", comp);

			for (int j = 0; j < i; j++) {
				fprintf(out, "%d ", get(L));
				moveNext(L);
			}

			fprintf(out, "%d\n", get(L));

			for (int j = 0; j < i; j++) {
				movePrev(L);
			}

			i = 0;
			comp++;
		}

		if (parent == NIL) {
			i = 0;
		} else {
			i++;
		}
        }
}

int main(int argc, char * argv[]) {

	FILE *in, *out;

	// CHECK that there are exactly two command line arguments.

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// OPEN files for reading and writing.

	in = fopen(argv[1], "r");

	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");

        if (out == NULL) {
                fprintf(stderr, "Unable to open file %s for writing.\n", argv[2]);
                exit(EXIT_FAILURE);
        }

	// SCAN first line, representing number of vertices.

	int numOfVertices;

	fscanf(in, "%d", &numOfVertices);

	// CREATE List of vertices.
	
	List S = newList();

	for (int v = 1; v <= numOfVertices; v++) {
		append(S, v);
	}

	// CREATE a new Graph object.	

	Graph G = newGraph(numOfVertices);

	// READ each vertex pair and store them in the List array.

	int v1, v2;

	fscanf(in, "%d %d", &v1, &v2);

	while (v1 != 0 || v2 != 0) {

		// ADD arcs from pairs of vertices.
		addArc(G, v1, v2);

		// READ next pair of vertices.
		fscanf(in, "%d %d", &v1, &v2);
	}

	// PRINT the adjacency list representation.
	
	fprintf(out, "Adjacency list representation of G:\n");

	printGraph(out, G);

	// RUN Depth First Search on G and the transpose of G.

	DFS(G, S);

	Graph Gt = transpose(G);

	DFS(Gt, S);

	// PRINT the strongly connected components of G.

	printComponents(out, Gt, S);

	// CLOSE files and DEALLOCATE memory.

	fclose(in);
	fclose(out);

	freeGraph(&G);
	freeGraph(&Gt);

	freeList(&S);

	return EXIT_SUCCESS;
}
