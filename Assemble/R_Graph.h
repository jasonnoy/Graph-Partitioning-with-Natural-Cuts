#ifndef R_GRAPH_H
#define R_GRAPH_H

#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

#include "R_Node.h"
#include "../Common/Utility.h"

class R_Graph{

public:
	
	R_Graph(){
	}

	~R_Graph(){
	}

	vector<R_Node>& get_node_list(){
		return this->node_list;
	}

	vector<R_Edge>& get_edge_list(){
		return this->edge_list;
	}

	NodeID contract_id( NodeID nid ){
		return this->contract_to[nid];
	}

	/////////////////////////////main methods////////////////////////////

	void read_graph(string co_path, string gr_path);

	void fill_contract_to( vector< vector<NodeID> >& final_result );

	EdgeWeight write_result( vector< vector<NodeID> >& result, vector< vector<NodeID> >& id_map, 
		const string& co_path, const string& gr_path, const string& r_path, bool isPhantom );

private:
	//basic
	vector<R_Node> node_list;
	vector<R_Edge> edge_list;

	vector<NodeID> contract_to;

};


#endif //R_GRAPH_H