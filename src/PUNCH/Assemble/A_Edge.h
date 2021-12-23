#ifndef A_EDGE_H
#define A_EDGE_H

#include "../../../common/common.h"

class A_Edge{

public:

	~A_Edge(){
	}

	A_Edge(NodeID s, NodeID t, EdgeWeight w, EdgeID id)
		: source(s), target(t), weight(w),eid(id){
	}

	const NodeID get_source() const{
		return this->source;
	}

	const NodeID get_target() const{
		return this->target;
	}

	const EdgeID get_id() const{
		return this->eid;
	}

	const EdgeWeight get_weight() const{
		return this->weight;
	}



private:

	const NodeID source;
	const NodeID target;
	const EdgeWeight weight;
	const EdgeID eid;
};



#endif //A_EDGE_H