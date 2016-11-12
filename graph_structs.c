#include "graph_structs.h"

int edgeLength(edge *e) {
	if(e->u->pos - e->v->pos > 0) return e->u->pos - e->v->pos;
	else return e->v->pos - e->u->pos;
}
