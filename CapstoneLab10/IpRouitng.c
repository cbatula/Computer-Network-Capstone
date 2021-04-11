#include "linkState.c"
#include "distanceVector.c"
#include "pathCosts.h"

//Given an array p[] of predecessor nodes, it determines what the correct
//path of nodes is to reach node t. (Still on development).
void shortestPath(char *p, char t, char *path, char *nodes, int n, int s){
    int i;
    for(i = 0; i < n; i++){
        if(nodes[i] == t)
            break;
    }

    path[s] = p[i];

    if(p[i] == 's')
        printf("%s\n", path);
    else
        shortestPath(p, p[i], path, nodes, n, ++s);
}

int main(int argc, char **argv){
    char P[NODES];
    int Drip[2*NODES][NODES];
    int Dospf[NODES];
    int i;

    //char t = 'v';

    OSPF(Dospf, P, atoi(argv[1]));

    RIP(Drip);

    //shortestPath(P, t, path, nodes, NODES, 0);

    return 0;
}