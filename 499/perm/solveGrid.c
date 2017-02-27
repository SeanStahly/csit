 // required MPI include file
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <string.h>
#include <cstddef>
#define N 5
typedef struct cell {
        int value;
        int constraint;
		char c;
} cell;
typedef struct Grid{
	cell cells [N][N];
	int size;
}Grid;

typedef struct Password{
	char *list;
	int size;
	int offset;
}Password;

using namespace std;
Grid * recGrid(MPI_Datatype type);
void sendGrid(Grid* g, int who, MPI_Datatype type);
void sendPassword(Password * p, int who);
Password * recPassword();
void printGrid(Grid * g);
Grid * cloneGrid(Grid * g);
void printPass(Password * p);
int main(int argc, char *argv[])
	{
	char hostname[MPI_MAX_PROCESSOR_NAME];
   	// Find out rank, size
	int  numtasks, len, rc;
	int world_rank;
	   // initialize MPI
   	MPI_Init(&argc,&argv);
	MPI_Get_processor_name(hostname, &len);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	//define the cell type for MPI
    const int    nitems=3;
    int          blocklengths[3] = {1,1,1};
    MPI_Datatype types[3] = {MPI_INT, MPI_INT,MPI_CHAR};
    MPI_Datatype mpi_cell_type;
    MPI_Aint     offsets[3];

    offsets[0] = offsetof(cell, value);
    offsets[1] = offsetof(cell, constraint);
    offsets[2] = offsetof(cell, c);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_cell_type);
    MPI_Type_commit(&mpi_cell_type);
	
	int init;
	int number = N;
	int * array;
	int size;

	if (world_rank == 0)
		{
			Password * p = (Password *)malloc(sizeof(Password));
			p->size = 4;
			p->list = (char *) malloc(p->size);
			p->offset = -1;
			strcpy(p->list, "yoyo");
			Grid * g = (Grid *) malloc(sizeof(Grid));
			for(int i =0; i < N; i++)
			{
				for(int j = 0; j < N; j++)
				{
					g->cells[i][j].value = -1;
				}
			}
			g->size = N;
			for(int i = 1; i < world_size; i++)
			{
				g->cells[1][2].value = i;
				//cout << "Sending " << i << endl;
				sendGrid(g,i,mpi_cell_type);
				sendPassword(p, i);
			}
		}
	else if (world_rank != 0) 
		{
			Grid * g = (Grid *) recGrid(mpi_cell_type);
			Password * p = recPassword();
			cout << "Got pass" << endl;
			printPass(p);
/*			float workers = world_size-1.0;
			float rank = world_rank -1.0;
			float percent = 1.0/workers;
			
			int min = percent * rank * size;
			int max = percent * (rank+1)  * size -1.0;
			printf("RANK --- %d min %d max %d", world_rank, min, max);
			*/
		}
	//printf ("Number of tasks= %d My rank= %d Running on %s\n", world_size,world_rank,hostname);

   // done with MPI
   MPI_Finalize();
   }
void getGrids(Grid * g, Password * p)
{
	
	
	
}
void sendGrid(Grid* g, int who,MPI_Datatype type)
   	{
	  	MPI_Send(&g->cells, g->size * g->size, type, who, 0, MPI_COMM_WORLD);
   	}

void sendPassword(Password * p, int who)
   	{
	  	MPI_Send(&p->size,1, MPI_INT, who, 0, MPI_COMM_WORLD);
	  	MPI_Send(&p->offset,1, MPI_INT, who, 0, MPI_COMM_WORLD);
	  	MPI_Send(p->list, p->size, MPI_CHAR, who, 0, MPI_COMM_WORLD);
   	}

Password * recPassword()
		{
		  	Password * p = (Password *)malloc(sizeof(Password));
	   	  	MPI_Recv(&p->size, 1, MPI_INT, MPI_ANY_SOURCE,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			p->list = (char *)malloc(p->size);
			MPI_Recv(&p->offset, 1, MPI_INT, MPI_ANY_SOURCE,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	   	  	MPI_Recv(p->list, p->size,MPI_CHAR, MPI_ANY_SOURCE,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		   	return p;
		} 
	
Grid * recGrid(MPI_Datatype type)
	{
	  	Grid * g = (Grid *)malloc(sizeof(Grid));
		g->size = N;
   	  	MPI_Recv(&g->cells, g->size *g->size, type, MPI_ANY_SOURCE,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printGrid(g);
	   	return g;
	} 
	
Grid * cloneGrid(Grid * g)
	{
	  	Grid * res = (Grid *)malloc(sizeof(Grid));
		res->size = N;
		for(int i =0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				res->cells[i][j].value = g->cells[i][j].value;
				res->cells[i][j].constraint = g->cells[i][j].constraint;
				res->cells[i][j].c = g->cells[i][j].c;
			}
			cout << endl;
		}
	}	

void printPass(Password * p)
		{
						cout << "Pass Size =" << p->size << endl;
			for(int i =0; i < p->size; i+=4)
			{
				//printf("C=%c",p->list[i]);
				printf("%c->%c%c%c",p->list[i], p->list[i+1],p->list[i+2], p->list[i+3]);
//				cout << i << endl;
			}
		} 

	
void printGrid(Grid * g)
	{
		for(int i =0; i < N; i++)
		{
			cout << "XX";
			for(int j = 0; j < N; j++)
			{
				cout << g->cells[i][j].value << " ";
			}
			cout << endl;
		}
	} 
   


int getIndex(int row, int col, int size)
{
	int result = (row * size)+ col;
	return result;
}
