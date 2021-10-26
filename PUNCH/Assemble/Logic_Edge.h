#ifndef LOGIC_EDGE_H
#define LOGIC_EDGE_H

#include "../../Common/common.h"

struct Logic_Edge{

public:

	~Logic_Edge(){
	}

	Logic_Edge(){
	}

	Logic_Edge(NodeID s, NodeID t, EdgeWeight w, double sc)
		: source(s), target(t), weight(w){

			this->score = sc;
			//this->counter = 0;
	}

	Logic_Edge(NodeID s, NodeID t, EdgeWeight w)
		: source(s), target(t), weight(w){

			this->score = 0;
			//this->counter = 0;
	}

	bool operator < ( const Logic_Edge &le ){

		return this->score < le.score; // 改为最小堆
	}

	NodeID source; //only contracted node ID
	NodeID target;
	EdgeWeight weight;
	double score;
	//size_t counter;
};



#endif //LOGIC_EDGE_H