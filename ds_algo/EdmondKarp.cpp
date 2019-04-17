/*
Computing maximum flow in flow network . Implementation of Edmonds-Karp Algorithm C++ .
*/
#include <iostream>
#include <stdio.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAXVERTICES 1000

using namespace std;

typedef struct Vertex {
	int id;
}Vertex;

typedef struct Edgenode
{
	int capacity;
	int flow;
	int reverseFlow;
	struct Vertex source;
	struct Vertex sink;
}Edgenode;


typedef struct Graph {
	Edgenode *edges[MAXVERTICES];
	int edge_count;
	bool directed;
}Graph;

typedef struct Queue
{
	Vertex *vertices;
	int count;
	int front;
	int rear;
}Queue;


void initQueue(Queue *q) {
	q->count = 0;
	q->front = 0;
	q->rear = 0;
	q->vertices = (Vertex*)malloc(MAXVERTICES*sizeof(Vertex));
}

void enqueue(Queue *q, Vertex e) {

	q->vertices[q->rear] = e;
	q->rear = (++q->rear) % MAXVERTICES;
	q->count++;

}

bool isEmpty(Queue *q) {

	return q->count == 0;
}

Vertex dequeue(Queue *q) {

	Vertex item;

	if (!isEmpty(q)) {
		item = q->vertices[q->front];
		q->front = (++q->front) % MAXVERTICES;
		q->count--;
	}
	return item;
}

Queue * createQueue() {
	Queue *q = (Queue*)malloc(sizeof(Queue));
	initQueue(q);
	return q;
}

Graph * createGraph(bool directed, int edge_count) {

	Graph *g = (Graph*)malloc(sizeof(Graph));
	g->edge_count = edge_count;
	g->directed = directed;
	for (int i = 0; i <edge_count; i++) {
		g->edges[i] = NULL;
	}

	return g;
}

void initEdgesFromVertex(Graph** g, Vertex *vertices, int index) {
	if (g[index]->edge_count != 0){

		for (int i = 0; i < g[index]->edge_count; i++) {

			cout << i << ".Edge Coming out of vertex " << index << endl;

			Edgenode *e = (Edgenode*)malloc(sizeof(Edgenode));

			cout << "SinkVertex      Capacity       ReverseEdgeFlow" << endl;

			cin >> e->sink.id >> e->capacity >> e->reverseFlow;

			e->sink = vertices[e->sink.id];

			e->source = vertices[index];

			e->flow = 0;

			g[index]->edges[i] = e;
		}
	}
}

void printAllEdgesInfoFromVertex(Graph ** graph , int index) {
	for (int i = 0; i < graph[index]->edge_count; i++) {
		cout << "Capacity : " << graph[index]->edges[i]->capacity << endl;
		cout << "Flow : " << graph[index]->edges[i]->flow << endl;
		cout << "Sink : " << graph[index]->edges[i]->sink.id << endl;
		cout << "Source : " << graph[index]->edges[i]->source.id << endl;
		cout << "ReverseFlow : " << graph[index]->edges[i]->reverseFlow << endl;
	}
}

int EdmondsKarp(Graph **graph, Queue * queue, Vertex sourceVertex, Vertex sinkVertex, int vertices_count)
{
	int flow = 0;

	while (1) {
		enqueue(queue, sourceVertex);

		Edgenode **pred = (Edgenode**)malloc(sizeof(Edgenode*) * vertices_count);

		for (int i = 0; i < vertices_count; i++) {
			pred[i] = NULL;
		}

		while (!isEmpty(queue))
		{

			Vertex currentVertex = dequeue(queue);

			for (int i = 0; i < graph[currentVertex.id]->edge_count; i++) {

				Edgenode *edge = graph[currentVertex.id]->edges[i];

				if ((pred[edge->sink.id] == NULL) && (edge->sink.id != sourceVertex.id) && (edge->capacity > edge->flow)) {
					pred[edge->sink.id] = edge;
					enqueue(queue, edge->sink);
				}
			}
		}

		if (pred[sinkVertex.id] == NULL) {
			break;
		}

		int df = INT_MAX;
		for (Edgenode *edge = pred[sinkVertex.id]; edge != NULL; edge = pred[edge->source.id]) {
			df = MIN(df, edge->capacity - edge->flow);
		}

		for (Edgenode *edge = pred[sinkVertex.id]; edge != NULL; edge = pred[edge->source.id]) {
			edge->flow += df;
			edge->reverseFlow -= df;
		}

		flow = flow + df;

		free(pred);
	}
	return flow;
}

int main() {

	fseek(stdin, 0, SEEK_END);
	int vertices_count = 4;
	//Source
	Vertex sourceVertex;	sourceVertex.id = 0;
	//Sink
	Vertex sinkVertex;	 	sinkVertex.id = 3;
	//Vertices
	Vertex *vertices = (Vertex*)malloc(vertices_count * sizeof(Vertex));
	//Graph array per vertices
	Graph **graph = (Graph**)malloc(vertices_count * sizeof(Graph*));
	//Queue
	Queue *queue = createQueue();
	//Init Vertices with their ID
	for (int i = 0; i < vertices_count; i++) {

		vertices[i].id = i;
	
	}
	//Init all graph per vertex
	for (int currentVertex = 0; currentVertex < vertices_count; currentVertex++) {
	
		int edgeCountFromCurrentVertex;
		cout << "Enter how much edges coming out of vertex " << currentVertex << " -> ";
		cin >> edgeCountFromCurrentVertex;
		//Creating graph
		graph[currentVertex] = createGraph(true, edgeCountFromCurrentVertex);
		cout << "Current Vertex : " << currentVertex << endl << "Edge Count : " << graph[currentVertex]->edge_count << endl;
	
	}
	//Init all edges per coming out vertex
	for (int index = 0; index < vertices_count; index++) {

		initEdgesFromVertex(graph, vertices, index);
		printAllEdgesInfoFromVertex(graph, index);
	}
	//Compute total flow 
	int flow = EdmondsKarp(graph, queue, sourceVertex, sinkVertex, vertices_count);

	system("cls");

	cout << endl << "Total Flow : " << flow << endl << endl;;
	
	fflush(stdin);
	getchar();

	cout << "Network Info" << endl;
	for (int index = 0; index < vertices_count; index++) {
		printAllEdgesInfoFromVertex(graph, index);
		cout << endl;
	}

	fflush(stdin);
	getchar();

	free(graph);
	free(queue);
	free(vertices);

}
