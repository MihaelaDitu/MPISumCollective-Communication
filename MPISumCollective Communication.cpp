#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>


#define SIZE 12
int main(int argc, char *argv[]) {
	int rank;
	int myResult = 0, result;
	float sendbuf[SIZE] = { 10, 12, 8, 6, 3, 9 , 16, 9, 5, 8 , 5, 10 };
	float recvbuf[3];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	
	MPI_Scatter(sendbuf, 3, MPI_FLOAT, recvbuf, 3, MPI_FLOAT, 0, MPI_COMM_WORLD);
	

	for (int i = 0; i < SIZE / 4; i++) {
		myResult += recvbuf[i];
	}

	MPI_Reduce(&myResult, &result, SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (0 == rank) {
		printf("The sum is %d.\n", result);
	}

	MPI_Finalize();
}