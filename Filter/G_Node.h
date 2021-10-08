#ifndef __G_NODE_H__
#define __G_NODE_H__

#include <vector>
#include <map>

using namespace std;

#include "G_Edge.h"
#include "../share/sw_basetypes.h"

class G_Node{

public:

	~G_Node(){
	}
	G_Node(NodeID id, geo_point_t geo): nid(id), geo_info(geo){
	}

	//G_Node(NodeID id): nid(id), sz(1){
	//}

	/*G_Node(NodeID ID, Coordinate lt, Coordinate lg)
		: nid(ID), lat(lt), lng(lg), sz(1){
	}

	G_Node(Coordinate c_lat, Coordinate c_lng): lat(c_lat), lng(c_lng), sz(1){
	}*/

	inline const NodeID get_id() const{
		return this->nid;
	}

    inline const geo_point_t get_geo_info() const{
        return this->geo_info;
    }

	//Coordinate get_lat(){
	//	return this->lat;
	//}
	 
	//Coordinate get_lng(){
	//	return this->lng;
	//}

	//inline NodeSize get_size(){
	//	return this->sz;
	//}

	//inline void set_size(NodeSize nsz){
	//	this->sz = nsz;
	//}

	//inline void add_size(NodeSize nsz){
	//	this->sz += nsz;
	//}

	//inline map< NodeID, G_Edge* >& get_adj_list(){
	//	return this->adj_list;
	//}

	inline vector<G_Edge*> &get_adj_list(){
		return this->adj_list;
	}

private:

	const NodeID nid;
	//map< NodeID, G_Edge* > adj_list;
	vector<G_Edge*> adj_list;
    geo_point_t geo_info;
	//Coordinate lat;
	//Coordinate lng;
	//NodeSize sz;
};


#endif __G_NODE_H__