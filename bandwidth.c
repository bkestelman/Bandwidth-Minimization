#include "graph_structs.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

//global arrays of all vertices and all edges (stored as contiguous arrays of pointers to vertices and edges)
vertex **vertices;
edge **edges;

int num_v; //number of vertices
int num_e; //number of edges

int max_g; //global max edge length (run maxEdgeIndex() to set max_g)

char *testfile = "testfile";
FILE *file;

int main() {
	if((file = fopen(testfile, "r")) == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}

	readGraph(file);
	printf("Initial graph:\n");
	printGraph();
	//printf("Maximum edge index: %d\n", maxEdgeIndex());
	maxEdgeIndex(); //set the global max_g
	int maxIndex = maxEdgeIndexFrom(0);
	printf("DEBUG: maxIndex: %d\n", maxIndex);
	printf("DEBUG: max_g: %d\n", max_g);
	while((maxIndex = maxEdgeIndexFrom(maxIndex)) != -1) {
		printf("Next maximum edge index: %d\n", maxIndex);
	}

	fclose(file);
}

//same as read, but prints to stderr on error 
ssize_t Read(int fd, void *buf, size_t bytes) {
	int ret;
	if((ret = read(fd, buf, bytes)) == -1) {
		fprintf(stderr, "Error reading file\n");
	}
	return ret;
}

void readGraph(FILE *file) {
	fscanf(file, "%d", &num_v);
	fscanf(file, "%d", &num_e);
	vertices = malloc(num_v * sizeof(vertex *));
	edges = malloc(num_e * sizeof(edge *));

	//populate vertices and edges arrays
	int i;
	for(i = 0; i < num_v; i++) {
		vertices[i] = malloc(sizeof(vertex));
		vertices[i]->id = i + 1;
		vertices[i]->pos = i + 1;
	}
	for(i = 0; i < num_e; i++) {
		edges[i] = malloc(sizeof(edge));
	}

	//get edge data
	int u, v; //vertices in edge 
	for(i = 0; i < num_e; i++) {
		fscanf(file, "%d %d", &u, &v);
		edges[i]->u = vertices[u - 1]; //remember the file contains vertex ids (from 1 to num_v), not the position of a vertex in the vertices array (which is one less, from 0 to num_v-1)
		edges[i]->v = vertices[v - 1];
	}
}

void printGraph() {
	int i;
	for(i = 0; i < num_v; i++) {
		printf("%d ", vertices[i]->id);
	}
	printf("\n\nEdges:\n");
	for(i = 0; i < num_e; i++) {
		printf("%d %d (length: %d)\n", edges[i]->u->id, edges[i]->v->id, edgeLength(edges[i]));
	}
}

//returns the index in the edges array of the edge with the maximum length
int maxEdgeIndex() {
	int i, len, max = 0, ret = -1;
	for(i = 0; i < num_e; i++) {
		len = edgeLength(edges[i]);
		if(len > max) {
			ret = i;
			max = len;
		}
	}
	max_g = max;
	return ret;
}

int maxEdgeIndexFrom(int prevMaxIndex) {
	int i, len;
	for(i = prevMaxIndex + 1; i < num_e; i++) {
		len = edgeLength(edges[i]);
		if(len == max_g) {
			return i;
		}
	}
	return -1;
}
