 // required MPI include file
#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <cstddef>
typedef struct cell {
        int value;
        int constraint;
		char c;
} cell;

using namespace std;
void permute(list<list<int>> *result, list<int> current, list<int> left);
list<list<int>> permutations;
int algorithm(int number);
cell * genLists(int number, int * size);

list<list<list<int>>> getLatinSquares(list<int> startingLine);
list<list<list<int>>> addLines(list<list<int>> setLines, list<list<int>> possibilities);
list<list<int>> filterPossibilities(list<list<int>> setLines, list<list<int>> possibilites);
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


	list<int> temp1;
	temp1.push_back(0);
	temp1.push_back(1);
	temp1.push_back(2);
	list<int> temp2;
	temp2.push_back(0);
	temp2.push_back(2);
	temp2.push_back(1);
	list<int> temp3;
	temp3.push_back(1);
	temp3.push_back(0);
	temp3.push_back(2);
	list<int> temp4;
	temp4.push_back(1);
	temp4.push_back(2);
	temp4.push_back(0);
	list<int> temp5;
	temp5.push_back(2);
	temp5.push_back(0);
	temp5.push_back(1);
	list<int> temp6;
	temp6.push_back(2);
	temp6.push_back(1);
	temp6.push_back(0);
	permutations.push_back(temp1);
	permutations.push_back(temp2);
	permutations.push_back(temp3);
	permutations.push_back(temp4);
	permutations.push_back(temp5);
	permutations.push_back(temp6);

	list<list<list<int>>> latinSquares = getLatinSquares(temp1);

	for(list<list<int>> ls: latinSquares) {
		for(list<int> line: ls) {
			for (int i: line) {
				printf("%d,",i);
			}
			cout << endl;
		}
		cout << endl;
	}

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
	int number = 4;
	int * array;
	int size;
	cell * cellArray;
	if(world_rank == 0)
		{
			cellArray = genLists(number, &size);
		}

	MPI_Bcast(&size,  1,    MPI_INT,0,MPI_COMM_WORLD);
	cout << "The size " << size << endl;
	if(world_rank != 0)
	{
		cellArray = (cell*)malloc(size * sizeof(cell));
	}
	MPI_Bcast(cellArray, size, mpi_cell_type, 0, MPI_COMM_WORLD);
	if (world_rank == 0)
		{
			init = 1; //send the size first
			for(int i= 1; i < world_size; i++)
			{
    		//		MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
			array = (int *) malloc(sizeof(int) * number * number);
			for(int i= 1; i < world_size; i++)
			{
			//	MPI_Recv(array,number*number, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				char del = ' ';
				for(int i = 0; i < number*number; i++)
				{
					del = ',';
				}
			}
		}
	else if (world_rank != 0)
		{

			float workers = world_size-1.0;
			float rank = world_rank -1.0;
    		//MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			float percent = 1.0/workers;

			int min = percent * rank * size;
			int max = percent * (rank+1)  * size -1.0;
			printf("RANK --- %d min %d max %d", world_rank, min, max);
			for(int i = min ;i < max; i++)
			{
				//printf("[%04d] %08X ", i, cellArray[i].value);
				//cout << cellArray[i].value << " ";
				if(i % number == 4)
				{
					//	cout << endl;
					//printf("OFFSET %04d ", i-4);
				}
			}
		}
	printf ("Number of tasks= %d My rank= %d Running on %s\n", world_size,world_rank,hostname);

   // done with MPI
   MPI_Finalize();
   }



cell * genLists(int number, int * size)
	{
		cell * cellArray;
		int gridsize = number * number;
		int *array = (int *)malloc(sizeof(int) * gridsize);
		list<int> l;
		for(int i = 0; i < number; i++)
		{
			l.push_back(i);
		}
		for(int i = 1; i < number * number;i++)
		{
			array[i] = -1;
		}
		//an algorithm goes here!!
		//algorithm(number);
		list<list<int>> result;
		list<int> empty;
		permute(&result,empty, l);
		*size = result.size() * number;
		cellArray = (cell *)malloc(sizeof(cell) * number * result.size());
		int index = 0;
		for(list<int> l : result)
		{
			for(int lvalue: l)
			{
					cellArray[index].value = lvalue;
					index++;
					//cout<<index << " " << lvalue << endl;
			}
		}

		cout <<"Size = "<< result.size()<< endl;
		return cellArray;
	}

/* print permutations of string */
void permute(list<list<int>> *result, list<int> current, list<int> left)
{
	if(left.empty())
	{
//		cout <<"Size = "<< result->size()<< endl;
		result->push_front(current);
//		cout <<"Size = "<< result->size()<< endl;
		for(int j: current)
		{
			//cout << j << ",";
		}
		//cout << endl;
	}
	else
	{
		list<int> left2(left);
		for(int i : left2)
		{
			list<int> newCurrent (current);
			list<int> newleft (left);
			newleft.remove(i);
			newCurrent.push_back(i);
			permute(result,newCurrent,newleft);
		}
	}
}

int getIndex(int row, int col, int size)
{
	int result = (row * size)+ col;
	return result;
}

list<list<list<int>>> getLatinSquares(list<int> startingLine) {
	//list<list<list<int>>> latinSquares;
	list<list<int>> possibleLines (permutations);
	list<list<int>> setLines;
	setLines.push_back(startingLine);
	return addLines(setLines, possibleLines);
}

list<list<list<int>>> addLines(list<list<int>> setLines, list<list<int>> possibilities) {
	list<list<int>> filteredPossibilities = filterPossibilities(setLines, possibilities);

	list<list<list<int>>> latinSquares;

	if (filteredPossibilities.size() == 1) {
		setLines.push_back(filteredPossibilities.front());
		latinSquares.push_back(setLines);
	} else {
		for(list<int> line: filteredPossibilities) {
			list<list<int>> newSetLines (setLines);
			newSetLines.push_back(line);
			list<list<list<int>>> newSets = addLines(newSetLines, filteredPossibilities);
			latinSquares.splice(latinSquares.end(), newSets);
		}
	}

	return latinSquares;
}

list<list<int>> filterPossibilities(list<list<int>> setLines, list<list<int>> possibilities) {
	list<list<int>> fList;
	for(list<int> pLine: possibilities) {
		bool conflict = false;
		for(list<int> sLine: setLines) {
			for(int i =0; i < sLine.size(); i++) {
				if (sLine.front() == pLine.front()) {
					conflict = true;
				}
				int temp = sLine.front();
				sLine.pop_front();
				sLine.push_back(temp);
				temp = pLine.front();
				pLine.pop_front();
				pLine.push_back(temp);
			}
			if (conflict) {
				break;
			}
		}
		if (!conflict) {
			fList.push_back(pLine);
		}
	}
	return fList;
}
