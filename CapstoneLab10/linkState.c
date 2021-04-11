/*
Name: Matias Sebastian Murgui Orsucci
Date: 11//18
Title: Lab 10
Description: Link State algorithm (Dijkstra's algorithm for shortest path problem)
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pathCosts.h"

#define INF 10000
#define NODES 6

int findMinPos(int *a, int b[2][NODES]){
	int min = INF;	
	int node;
	int i;
	
	for(i = 0; i < NODES; i++){
		if(a[i] < min && b[1][i] == 0){
			min = a[i];
			node = i;
		}
	}

	return node;	
}


int min(int a, int b, int *update){
	if(a <= b){
		*update	= 0;	
		return a;
	}
	
	*update = 1;
	return b;
}


void OSPF(int D[NODES], char P[NODES], int sourceNode){
//Defining Data
	//{'u', 'v', 'w', 'x', 'y', 'z'};
	// 0 if it's not visited, 1 if it is.
	int auxNodes[2][NODES] ={
		{0, 1, 2, 3, 4, 5},
		{0, 0, 0, 0, 0, 0}
	}; 
	int auxP[NODES];


	//Source node (u)
	const int sNode = sourceNode; 
		
	int i, j;
	char node;
	int update;

//Initialization
	for(i = 0; i < NODES; i++){
		if(C[0][i] > 0 && C[0][i] < INF){
			D[i] = C[0][i]; 
			auxP[i] = sNode;		
		}else
			D[i] = INF; //Define path weight to not neighbor nodes =10000
	}

	D[0] = 0; // Define path weight from source to source = 0.
	auxP[0] = sNode; //Define predecesor of source as source.
	auxNodes[1][0] = 1; // Define source node already visited.
	
//Loop
	j = 1; //Start from 1 because source node has already been visited (Initialization)
	while(j < NODES){
		
		//Find the next node that's not been visited
		//and that has the shortest path
		node = findMinPos(D, auxNodes);	

		//Note that the selected node has been visited	
		auxNodes[1][node] = 1;
		

		for(i = 0; i < NODES; i++){
			//For every node that's neighbor and that hasn't been visited yet
			if(C[node][i] > 0 && C[node][i] < INF && auxNodes[1][i] == 0){
				//Update path to each neighbor. 
				//If path from selected node is smaller than
				//older path, update == 1 --> update predecesor.
				D[i] = min(D[i], D[node]+C[node][i], &update);
				if(update == 1)	
					auxP[i] = node;
			}
		}
		j++;	
	}
	for(i = 0; i < NODES; i++){
		P[i] = N[auxP[i]];
	}	

	//Result
		for(i = 0; i < NODES; i++){
		printf("D: %d, P: %c\n", D[i], P[i]);
	}


}
