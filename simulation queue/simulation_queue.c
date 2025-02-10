/*
Petrogiannopoulos Georgios
2022201900182
dit19182@uop.gr

Drakopoulos Theodoros
2022201900052
dit19052@uop.gr
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef double Item;

typedef struct node *link;	

double genrand(double rate);

struct node              //komvos
{
	Item arr_time;
	Item end_time;
	link next; 
};

typedef struct          // queue
{
	link head, tail;	
} QUEUE;	


void QUEUEinit(QUEUE *q);     // create

void QUEUEput(QUEUE *q, Item arr , Item end);  // add node at the end of queue

Item QUEUEget(QUEUE *q);


int QUEUEempty(QUEUE *q);

void QUEUEfree(QUEUE *q);

void QUEUEprint(QUEUE *q);

int main()
{
	srand(time(NULL));
	QUEUE q;
	QUEUEinit(&q);  // create queue

	double arr_time;
	double prev_arr = 0;  // afiksi proigoumenou

	double end_time;
	double prev_end = 0;  // oloklirosi proigoumenou

	double service_time = 1; // gia to m/d/1
	double wait, average_wait_time, p=0;
	int i, count = 100000;
	char answer;
	
	printf("type 'm' for m/m/1 or type 'd' for m/d/1\n");
	do
	{
		scanf("%c",&answer);
	} while (answer!='m' && answer!='d');
	

	if(answer=='m')   // m/m/1 sistima
	{
		for(i=0;i<count;i++)
		{ 
			// vima 1
			arr_time = prev_arr + genrand(1);   //stathero panta
			prev_arr = arr_time;

			// vima 2
			if(i!=0)
			{
				link z = q.head->next;
		
				while(z != q.tail)
				{
					if(z->end_time < arr_time)
					{
						printf("GET: \n");	
						if(!QUEUEempty(&q))
						{
							wait = QUEUEget(&q); 
						}
					}
					z = z->next;
				}
			}

			// vima 3
			if(i==0)      //an einai adio
			{
				end_time = arr_time + service_time;
			}
			else
			{
				if(arr_time - prev_end >=0)
				{
					end_time = arr_time + service_time;
				}
				else
				{
					end_time = prev_end + service_time;
				}
			}
			prev_end = end_time;

			// vima 4
			printf("PUT %d : \narr: %f\nend: %f \n",i+1,arr_time,end_time);
			QUEUEput( &q , arr_time , end_time);


			link z = q.head->next;
			while(z != q.tail)
			{
				if(z->end_time < arr_time)
				{
					printf("GET: \n");	
					if(!QUEUEempty(&q))
					{
						wait = QUEUEget(&q); 
					}
				}
				z = z->next;
			}
		}

		printf("GET: \n");	// get gia ton teleftaio pelati
		if(!QUEUEempty(&q))
		{
			wait = QUEUEget(&q); 
		}
						
		printf("---------- QUEUE ----------\n");
		QUEUEprint(&q);
		printf("---------------------------\n");

		QUEUEfree(&q);

		p = p + wait;	   // athroisma xronon anamonis
	
		average_wait_time = p/count;
		printf("average wait time: %f\n",average_wait_time);
	}
	else    // m/d/1 sistima
	{
		for(i=0;i<count;i++)
		{ 
			// vima 1
			arr_time = prev_arr + genrand(0.1);  // xeirokinita vazoume to rate dioti evgaine provlima(atermon vroxos) an vazame mia for apo 0.1 eos 0.9 me vima 0.1
			prev_arr = arr_time;

			// vima 2
			if(i!=0)
			{
				link z = q.head->next;
		
				while(z != q.tail)
				{
					if(z->end_time < arr_time)
					{
						printf("GET: \n");	
						if(!QUEUEempty(&q))
						{
							wait = QUEUEget(&q); 
						}
					}
					z = z->next;
				}
			}

			// vima 3
			if(i==0)      //an einai adio
			{
				end_time = arr_time + service_time;
			}
			else
			{
				if(arr_time - prev_end >=0)
				{
					end_time = arr_time + service_time;
				}
				else
				{
					end_time = prev_end + service_time;
				}
			}
			prev_end = end_time;

			// vima 4
			printf("PUT %d : \narr: %f\nend: %f \n",i+1,arr_time,end_time);
			QUEUEput( &q , arr_time , end_time);

			link z = q.head->next;
			while(z != q.tail)
			{
				if(z->end_time < arr_time)
				{
					printf("GET: \n");	
					if(!QUEUEempty(&q))
					{
						wait = QUEUEget(&q); 
					}
				}
				z = z->next;
			}
		}

		printf("GET: \n");	// get gia ton teleftaio pelati
		if(!QUEUEempty(&q))
		{
			wait = QUEUEget(&q); 
		}
						
		printf("---------- QUEUE ----------\n");
		QUEUEprint(&q);
		printf("---------------------------\n");

		QUEUEfree(&q);

		p = p + wait;	      // athroisma xronon anamonis

		average_wait_time = p/count;
		printf("average wait time: %f\n",average_wait_time);
	}
}

void QUEUEinit(QUEUE *q)             //create queue
{
	q->head = (link)malloc(sizeof(struct node)); 
	
	q->tail = q->head; 
	
	q->head->next = NULL;
}

void QUEUEfree(QUEUE *q)
{
	while(!QUEUEempty(q))
		QUEUEget(q);
		
	free(q->head);
}

int QUEUEempty(QUEUE *q)
{
	return q->head == q->tail;
}

void QUEUEput(QUEUE *q, Item arr , Item end)       // add node at the end of the queue
{
	link t = (link)malloc(sizeof *t);
	
	t->arr_time = arr;
	t->end_time = end;
	
	t->next = q->tail->next;
	
	q->tail->next = t;
	
	q->tail = t; 
}

Item QUEUEget(QUEUE *q)       // remove item from queue
{
	link t = q->head->next;
	
	Item a = q->head->next->arr_time;
	Item e = q->head->next->end_time;
	
	q->head->next = t->next;
	
	if(q->tail == t)             // The tail contains the only item
		
		q->tail = q->head;
		
	free(t);
		
	return e-a;          // end time - arrival time 
}

void QUEUEprint(QUEUE *q)
{
	link z = q->head->next;
	
	while(z != NULL)
	{
		printf("QUEUE_arr: %f \n",z->arr_time);
		printf("QUEUE_end: %f \n\n",z->end_time);

		z = z->next;
	}
}

double genrand(double rate)
{
	int y;
	double p;
	
	while ((y = rand()) == RAND_MAX);

	p = (double) y / RAND_MAX;
			
	return -log(1-p) / rate;
}
