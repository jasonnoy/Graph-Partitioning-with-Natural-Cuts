#ifndef __G_EDGE_H__
#define __G_EDGE_H__

#include "../share/common.h"

class G_Edge{

public:

	~G_Edge(){
	}

	G_Edge(NodeID s, NodeID t, EdgeID id, uint64_t oid): source(s), target(t), eid(id), origin_eid(oid){
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

    const uint64_t get_origin_id() const{
        return this->origin_eid;
    }
private:

	const NodeID source;
	const NodeID target;
	const EdgeID eid;
    const uint64_t origin_eid;
};



#endif __G_EDGE_H__