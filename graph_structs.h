#ifndef GRAPH_STRUCT_H
#define GRAPH_STRUCT_H

typedef struct {
	int id;
	int pos;
	//may be useful to add edgelist
} vertex;

typedef struct {
	vertex *u, *v;
} edge;

int edgeLength(edge *e);

#endif
