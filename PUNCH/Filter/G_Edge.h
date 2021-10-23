#ifndef G_EDGE_H
#define G_EDGE_H

#include "../Common/common.h"

class G_Edge{

public:

	~G_Edge(){
	}

	G_Edge(NodeID s, NodeID t, EdgeID id): source(s), target(t), eid(id) {
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

private:

	const NodeID source;
	const NodeID target;
	const EdgeID eid;
};



#endif //G_EDGE_H