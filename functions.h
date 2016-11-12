#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H

#include <sys/types.h>
#include <stdio.h>

ssize_t Read(int file, void *buf, size_t count);

void readGraph(FILE *file);
void printGraph();

int maxEdgeIndex();
int maxEdgeIndexFrom(int prevMaxIndex);

#endif
