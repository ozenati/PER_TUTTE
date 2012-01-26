#ifndef TUTTE_H
#define TUTTE_H

#include "toolkit.h"

void tutte(vector<MyNode> * MyNodes, double eps, bool silent);

void tutte_parallel_asynchrone(vector<vector<MyNode *> *> *vectors, double eps, bool silent);

void tutte_2(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
	     vector<Vec2f> * coords, double eps, bool silent);

void tutte_2_bis(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
	     vector<Vec2f> * coords, double eps, bool silent);

void tutte_2_openmp(vector<MyNode_ver2> * MyNodes_2, vector<int> * Neighbourhoods, 
		    vector<Vec2f> * coords, double eps, bool silent);

void tutte_seq_3(vector<Data>* datas, vector<vector<int> >* matrix, double eps, bool silent);

#endif
