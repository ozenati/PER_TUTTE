#ifndef TUTTE_H
#define TUTTE_H

#include "toolkit.h"

void tutte_parallel_asynchrone(vector<vector<MyNode *> *> *vectors, double eps);

void tutte_2(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
	     vector<Vec2f> * coords, double eps);

void tutte_2_bis(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
	     vector<Vec2f> * coords, double eps);

#endif
