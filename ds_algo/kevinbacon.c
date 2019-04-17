/*
Computes Kevin Bacon distances for hollywood stars , connections associated with films,
you can download cast.rated.txt from -> https://www.dropbox.com/s/srbpl084ymhy5yz/cast.rated.txt?dl=0 . 
Also, you can get information about Kevin Bacon Number from this site :
https://en.wikipedia.org/wiki/Six_Degrees_of_Kevin_Bacon
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_ACTOR_COUNT 124434
#define MAX_MOVIE_COUNT 4535
#define BUFFER_SIZE 20000
#define TRUE 1
#define FALSE 0

struct Movie;
struct Actor;

typedef struct Movie {
	char *name;
	int actorStarred;//Actor Count in movie 
	int isVisited;
	int index;
	struct Actor **actorArray;
}Movie;

typedef struct Actor {
	char *name;
	int movieStarred;//Movie Count actor played
	int isVisited;
	int KBNumber;
	int index;
	struct Movie **movieArray;
	struct Actor *parent;
}Actor;

typedef struct Queue
{
	struct Actor **actors;
	int count;
	int front;
	int rear;
}Queue;

void initQueue(Queue *q) {
	q->count = 0;
	q->front = 0;
	q->rear = 0;
	q->actors = (Actor**)malloc(MAX_ACTOR_COUNT*sizeof(Actor*));
}

void enqueue(Queue *q, Actor *p) {

	q->actors[q->rear] = p;
	q->rear = (++q->rear) % MAX_ACTOR_COUNT;
	q->count++;

}

int isEmpty(Queue *q) {

	return q->count == 0;
}

Actor* dequeue(Queue *q) {

	Actor *item = NULL;

	if (!isEmpty(q)) {
		item = q->actors[q->front];
		q->front = (++q->front) % MAX_ACTOR_COUNT;
		q->count--;
	}

	return item;
}

Actor *initActor(char *name)	
{
	Actor *actor = (Actor*)malloc(sizeof(Actor));

	actor->movieStarred = 0;
	
	actor->name = (char*)malloc(sizeof(char) * strlen(name));
	
	strcpy(actor->name, name);
	
	actor->movieArray = (Movie**)malloc(sizeof(Movie*) * 200);
	
	actor->KBNumber = 0;
	
	actor->isVisited = FALSE;

	return actor;
}

Movie *initMovie(char *name)
{
	Movie *movie = (Movie*)malloc(sizeof(Movie));
	
	movie->actorStarred = 0;
	
	movie->name = (char*)malloc(sizeof(char) * strlen(name));
	
	strcpy(movie->name, name);
	
	movie->actorArray = (Actor**)malloc(sizeof(Actor*) * 200);
	
	movie->isVisited = FALSE;

	return movie;
}


Actor *findActor(Actor **actors, int totalActors, char *actorName)
{

	for (int i = 0; i < totalActors; i++)
	{
		if (strcmp(actorName, actors[i]->name) == 0)
		{
			return actors[i];
		}
	}

	return NULL;
}

int IsInQueue(Queue *q, Actor *actor) {

	for (int i = 0; i < q->count; i++) {
		if (strcmp(q->actors[i]->name, actor->name) == 0) {
			return TRUE;
		}
	}

	return FALSE;
}

void BFS_KB(Queue *q, Actor** actors, Movie** movies, int totalActors, int totalMovies, char* name) {

	char * target = "Bacon, Kevin";
	
	int found = FALSE;

	Actor* tempActor = findActor(actors, totalActors, name);

	printf("actor : %s\n", actors[tempActor->index]->name);
	
	enqueue(q, actors[tempActor->index]);
	
	actors[tempActor->index]->parent = NULL;
	
	printf("\nStart Search\n");
	
	getchar();	

	do {
		
		tempActor = dequeue(q);
		
		actors[tempActor->index]->isVisited = TRUE;

		if (strcmp(tempActor->name, target) == 0) {
			found = TRUE;
		}
		

		for (int i = 0; i < tempActor->movieStarred; i++) {
		
			Movie * mov = movies[tempActor->movieArray[i]->index];
	
			if (!mov->isVisited) {
				
				movies[mov->index]->isVisited = TRUE;
				
				for (int j = 0; j < mov->actorStarred; j++) {
					
					Actor * act = actors[mov->actorArray[j]->index];

					if (!actors[act->index]->isVisited) {
						
						if (!IsInQueue(q, act)) {
							
							actors[act->index]->KBNumber = tempActor->KBNumber + 1;
	
							actors[act->index]->parent = actors[tempActor->index];
							
							enqueue(q, actors[act->index]);
						}
					}
				}
			}
		}


	} while (tempActor->KBNumber <= 6 && !found);

	Actor* kevin = tempActor;

	if (kevin->KBNumber <= 6) {
	
		while (tempActor->parent != NULL) {
		
			printf("%s-", actors[tempActor->index]->name);
			
			tempActor = actors[tempActor->parent->index];
		
		}
		
		printf("%s", findActor(actors, totalActors, name)->name);
		
		printf("\nKevin Bacon number : %d", kevin->KBNumber);
	}
	else {
		printf("\nKevin Bacon number bigger than 6");
	}

	
}

int main()
{
	printf("READING FILE!\n");


	Movie *movies[MAX_MOVIE_COUNT];
	Actor *actors[MAX_ACTOR_COUNT];
	Queue *q = (Queue*)malloc(sizeof(Queue));

	initQueue(q);

	FILE* file = fopen("cast.rated.txt", "r"); /* should check the result */

	if (file == NULL) {
		printf("Couldn't find file");
		return -1;
	}

	char line[BUFFER_SIZE];
	char *ch;
	int totalMovie = 0;
	int totalActors = 0;

	while (fgets(line, sizeof(line), file)) {
		/* note that fgets don't strip the terminating \n, checking its
		presence would allow to handle lines longer that sizeof(line) */
		ch = strtok(line, "/");
		
		Movie *newMovie = initMovie(ch);

		newMovie->index = totalMovie;
		
		while (ch = strtok(NULL, "/"))
		{
			char *newlinePos;
		
			if (newlinePos = strchr(ch, '\n'))
			{
				ch[newlinePos - ch] = '\0';
			}

			Actor *movieActor = findActor(actors, totalActors, ch);

			if (movieActor == NULL)
			{
				movieActor = initActor(ch);
			
				movieActor->index = totalActors;
				
				actors[totalActors] = movieActor;
				
				totalActors++;
			}
	
			movieActor->movieArray[movieActor->movieStarred] = newMovie;
			
			actors[movieActor->index]->movieArray[movieActor->movieStarred] = newMovie;
			
			newMovie->actorArray[(newMovie->actorStarred)++] = movieActor;
			
			movieActor->movieStarred++;
			
		}
		movies[totalMovie] = newMovie;
		
		totalMovie++;
		
		free(ch);
	}
	printf("\nDONE\n");
	
	getchar();
	/* may check feof here to make a difference between eof and io failure -- network
	timeout for instance */

	fclose(file);

	char* name = "Schwarzenegger, Arnold";

	BFS_KB(q, actors, movies, totalActors, totalMovie, name);
	
	getchar();

	return 0;
}
