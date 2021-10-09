#ifndef __R_NODE_H__
#define __R_NODE_H__

#include <vector>
#include <map>

using namespace std;

#include "../share/common.h"
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


#endif __G_NODE_H__