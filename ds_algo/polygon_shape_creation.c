#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct point2D {
	int x, y;
}point2D;

typedef struct line2D {
	point2D *start;
	point2D *end;
}line2D;

typedef struct polygon2D {
	int edge_count;
	int available;
	line2D** lines;
}polygon2D;

point2D* createPoint(int x, int y) {
	point2D* point = (point2D*)malloc(sizeof(point2D));
	point->x = x;
	point->y = y;
	return point;
}

line2D* createLine(point2D* p1, point2D* p2) {
	line2D * line = (line2D*)malloc(sizeof(line2D));
	line->start = p1;
	line->end = p2;
	return line;
}

polygon2D* createEmptyPolygon(int edge_count) {
	polygon2D* polygon = (polygon2D*)malloc(sizeof(polygon2D));
	polygon->edge_count = edge_count;
	polygon->lines = (line2D**)malloc(polygon->edge_count * sizeof(line2D*));
	return polygon;
}

int checkLinesCrossing(line2D * l1, line2D * l2) {
	//Line-1
	int x1 = l1->start->x;
	int y1 = l1->start->y;
	int x2 = l1->end->x;
	int y2 = l1->end->y;
	//Line-2
	int x3 = l2->start->x;
	int y3 = l2->start->y;
	int x4 = l2->end->x;
	int y4 = l2->end->y;

	//Slopes
	int A1 = (y1 - y2) / (x1 - x2);
	int A2 = (y3 - y4) / (x3 - x4);

	//intersection points
	int b1 = y1 - (A1 * x1);
	int b2 = y3 - (A2 * x3);

	//intersection point 
	int Xa = (b2 - b1) / (A1 - A2);

	//basic non-intersection
	if (max(x1, x2) < min(x3, x4)) {
		return 0;
	}
	//lines parallel
	else if (A1 == A2) {
		return 0;
	}
	//intersection out of bounds
	else if((Xa < max(min(x1, x2), min(x3, x4))) || (Xa < min(max(x1,x2), max(x3,x4)))){
		return 0;
	}

	return 1;
}

void checkPolygonRules(polygon2D* polygon) {

	if (polygon->lines[0]->start->x != polygon->lines[polygon->edge_count - 1]->end->x &&
		polygon->lines[0]->start->y != polygon->lines[polygon->edge_count - 1]->end->y) {
		printf("Start and End aren't same point !!! \n");
	}
	else {
		for (int i = 0; i < polygon->edge_count - 1, polygon->available; i++) {
			for (int j = i; j < polygon->edge_count; j++) {
				int isCrossingLines = checkLinesCrossing(polygon->lines[i], polygon->lines[j]);
				if (isCrossingLines) {
					printf("%d. and %d. lines are crossing eachother!!! \n", i, j);
					polygon->available = 0;
					break;
				}
			}
		}
	}
	
	if (polygon->available) {
		printf("This points means a closed polygon!!! \n");
	}
}

int main(void) {
	int vertex_count;

	point2D* target_point = (point2D*)malloc(sizeof(point2D));
	target_point->x = 2;
	target_point->y = 3;

	printf("Total Vertex Count : ");
	scanf("%d", &vertex_count);
	
	point2D** points = (point2D**)malloc(vertex_count*sizeof(point2D*));
	for (int i = 0; i < vertex_count; i++) {
		points[i] = (point2D*)malloc(sizeof(point2D));
	}

	polygon2D * polygon = createEmptyPolygon(vertex_count - 1);
	
	for (int i = 0; i < vertex_count; i++) {
		printf("x : ");
		scanf("%d", &points[i]->x);
		printf("y : ");
		scanf("%d", &points[i]->y);
	}

	for (int i = 0; i < vertex_count; i++) {
		printf("%d - %d\n", i, ((i + 1) % vertex_count));
		line2D * line = createLine(points[i], points[(i+1) % vertex_count]);
		polygon->lines[i] = line;
		getchar();
	}

	checkPolygonRules(polygon);

	getchar();
	return 0;
}
