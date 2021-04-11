#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pathCosts.h"

void RIP(int D[2*NODES][NODES]){
//Defining Data	
	//Converged distance matrix
	//even rows -> current state of distance vector
	//odd rows -> future updated state of distance vector
	// row 0 : current distance vector for u
	// row 1 : updated (or not) distance vector for u
	// row 2 : current distance vector for v
	// row 3 : updated (or not) distance vector for v
	// (...)
	
	int i, j, k;
	int update[NODES];
	int updateFlag = 1;
	int iterations = 0;

//Initialization
	//Start with duplicate rows for current 
	//and future distance vectors
	for(i = 0; i < 2*NODES; i += 2){
		update[i/2] = 1;
		for(j = 0; j < NODES; j++){
			D[i][j] = C[i/2][j];	
			D[i+1][j] = C[i/2][j];	
		}
	}
	
	
	//Print initial state
	printf("Initial state of node's forwarding table.\n");
	printf(" \tu\t\tv\t\tw\t\tx\t\ty\t\tz\n");
	for(i = 0; i < 2*NODES; i += 2){
		printf("%c\t", N[i/2]);
		for(j = 0; j < NODES; j++){
			if(D[i][j] == INF)
				printf("Infinite\t");
			else
				printf("%d\t\t", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("********************\n");

	
	while(updateFlag == 1){
		
		//mod to Bellman-Ford algorithm
		for(i = 0; i < 2*NODES; i += 2){
			//As well as using updateFlag to see if an update
			//has occured, update[] will inform if we need to 
			//perform update computations for each distance vector - [i]
			// 0: no update; 1: update
			if(update[i/2] == 1){
				update[i/2] = 0;
				for(j = 0; j < NODES; j++){
					//Check if its a neighbor
					if(D[i][j] > 0 && D[i][j] < INF){
						//Check for possible updates
						for(k = 0; k < NODES; k++){
							//j*2 is because matrix D has repeated rows
							if((D[j*2][k] + D[i][j]) < D[i][k]){
								//Store the update in the adjacent row to keep using
								//current state for other computations.
								D[i+1][k] = D[j*2][k] + D[i][j];	
								update[i/2] = 1;		
							}
						}				
					}	
				}
			}	
		}
		
		//As this iteration has completed its updates
		//we update our current states to be our updated states.
		//On next possible iteration these will be current states.
		for(i = 0; i < 2*NODES; i += 2){
			for(j = 0; j < NODES; j++){
				D[i][j] = D[i+1][j];			
			}
		}
		
		//If there's any element in updateFlag = to 1,
		//update, meaning go through another iteration.
		updateFlag = 0;			
		for(i = 0; i < NODES; i++){
			if(update[i] == 1){
				updateFlag = 1;
				break;
			}
		}

		iterations++;
		printf("Iterations= %d\n", iterations);	
	}
	printf("********************\n");

	//Print updated table.
	printf(" \tu\t\tv\t\tw\t\tx\t\ty\t\tz\n");
	for(i = 0; i < 2*NODES; i += 2){
		printf("%c\t", N[i/2]);
		for(j = 0; j < NODES; j++){
			printf("%d\t\t", D[i][j]);
		}
		printf("\n");
	}
}
