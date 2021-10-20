#ifndef R_EDGE_H
#define R_EDGE_H

#include "../Common/common.h"

class R_Edge{

public:

	~R_Edge(){
	}

	R_Edge(NodeID s, NodeID t): source(s), target(t){
	}

	const NodeID get_source() const{
		return this->source;
	}

	const NodeID get_target() const{
		return this->target;
	}

private:

	const NodeID source;
	const NodeID target;
};


#endif //R_EDGE_H