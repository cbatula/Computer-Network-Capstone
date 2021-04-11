#ifndef PATHCOSTS_H
#define PATHCOSTS_H

#define INF 10000
#define NODES 7

const char N[NODES] = {'t', 'u', 'v', 'w', 'x', 'y', 'z'};

const int C[7][7] = {
	{0, 7, 1, INF, INF, INF, 1},
	{7, 0, INF, 5, 4, INF, INF},
	{1, INF, 0, 11, 2, INF, INF},
	{INF, 5, 11, 0, 5, INF, INF},
	{INF, INF, 2, 5, 0, 4, INF},
	{INF, INF, INF, INF, 4, 0, 8},
	{1, INF, INF, INF, INF, 8, 0}
};

const char ipAddresses[NODES][NODES]={
    "ip1",
    "ip2",
    "ip3",
    "ip4"
};

#endif //PATHCOSTS_H
