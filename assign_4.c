#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
typedef struct NODE {
	struct NODE* next;
	struct edge* ed;
}NODE;
typedef struct vertice {
	struct vertice* next;
	struct NODE* inc;
	int index;
	int label;
}vertice;
typedef struct edge {
	struct edge* next;
	struct vertice* ver1;
	struct vertice* ver2;
	int label;
}edge;
int addvertice(vertice* v, int i) {
	vertice* New;
	New = (vertice*)malloc(sizeof(vertice));
	New->next = NULL;
	New->index = i;
	New->inc = (NODE*)malloc(sizeof(NODE));
	New->inc->next = NULL;
	vertice* x = v;
	while (x->next != NULL) {
		x = x->next;
	}
	x->next = New;
}
int addedge(vertice* v, edge* e, int a, int b) {
	vertice* x = v, * y = v;
	while (x->index != a) {
		x = x->next;
	}
	while (y->index != b) {
		y = y->next;
	}
	edge* tmp = e;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	edge* New;
	New = (edge*)malloc(sizeof(edge));
	New->ver1 = x;
	New->ver2 = y;
	New->next = NULL;
	tmp->next = New;
	NODE* xx = x->inc, * yy = y->inc, * incx, * incy;
	while (xx->next != NULL) {
		xx = xx->next;
	}
	incx = (NODE*)malloc(sizeof(NODE));
	incx->ed = New;
	incx->next = NULL;
	xx->next = incx;
	if (a != b) {
		while (yy->next != NULL) {
			yy = yy->next;
		}
		incy = (NODE*)malloc(sizeof(NODE));
		incy->ed = New;
		incy->next = NULL;
		yy->next = incy;
	}
}
int rDFS(vertice* v, edge* e, vertice* s,vertice *origin) {
	int tmp = 0;
	s->label = 1;
	NODE* x = s->inc->next;
	while (x != NULL) {
		if (tmp == 1) return 1;
		if (x->ed->ver1 == s && x->ed->label == 0) {
			if (x->ed->ver2->label == 0) {
				x->ed->label = 1;
				tmp = rDFS(v, e, x->ed->ver2,origin);
				x->ed->ver2->label = 0;
				x->ed->label = 0;
			}
			if (x->ed->ver2==origin) return 1;
		}
		if (x->ed->ver2 == s && x->ed->label == 0) {
			if (x->ed->ver1->label == 0) {
				x->ed->ver1->label = 1;
				x->ed->label = 1;
				tmp = rDFS(v, e, x->ed->ver2,origin);
				x->ed->ver1->label = 0;
				x->ed->label = 0;
			}
			if (x->ed->ver1 == origin) return 1;
		}
		x = x->next;
	}
	return tmp;
}
int DFS(vertice* v, edge* e,int n) {
	vertice* x = v;
	edge* y = e;
	while (x != NULL) {
		x->label = 0;
		x = x->next;
	}
	while (y != NULL) {
		y->label = 0;
		y = y->next;
	}
	x = v;
	for (int i = 1; i < n; i++) {
		int w=rDFS(v, e, x,x);
		if (w == 1) return 1;
		x = x->next;
	}
	return 0;
}
int main() {
	vertice* v;
	edge* e;
	v = (vertice*)malloc(sizeof(vertice));
	e = (edge*)malloc(sizeof(edge));
	v->next = NULL;
	e->next = NULL;
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		if (i == 1) {
			v->inc = (NODE*)malloc(sizeof(NODE));
			v->inc->next = NULL;
			v->index = i;
		}
		addvertice(v, i);
	}
	int a, b;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		addedge(v, e, a, b);
	}
	printf("%d",DFS(v, e, n));
}