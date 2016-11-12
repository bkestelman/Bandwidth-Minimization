#ifndef GRAPH_STRUCT_H
#define GRAPH_STRUCT_H

typedef struct vertex vertex;

struct vertex {
	vertex *prevPos_v;
	vertex *nextPos_v;
	int id;
	int pos;
	//may be useful to add edgelist
};

typedef struct {
	vertex *u, *v;
} edge;

int edgeLength(edge *e);

#endif
