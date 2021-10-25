#ifndef R_NODE_H
#define R_NODE_H

#include <vector>
#include <map>

using namespace std;

#include "../../Common/common.h"
#include "R_Edge.h"

class R_Node{

public:

	~R_Node(){
	}

	R_Node(Coordinate lt, Coordinate lg)
		:lat(lt), lng(lg){
	}

	unsigned int get_lat(){
		return this->lat;
	}
	 
	unsigned int get_lng(){
		return this->lng;
	}

private:

	unsigned int lat;
	unsigned int lng;
};


#endif //G_NODE_H