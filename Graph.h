// ---------------------------------------------------------
// Name: Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa3
// ---------------------------------------------------------

#ifndef GRAPH_H_
#define GRAPH_H_

#pragma once

#define UNDEF -1 // Negative int to represent infinity
#define NIL 0 // Non-positive int to represent an undefined vertex label

#include <stdlib.h>
#include <stdio.h>

#include "List.h"

/*** Constructors-Destructors ***/

typedef struct GraphObj* Graph;

Graph newGraph(int n);

void freeGraph(Graph *pG);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

/*** Access functions ***/

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

/*** Manipulation procedures ***/

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

/*** Other operations ***/

void printGraph(FILE* out, Graph G);

#endif
