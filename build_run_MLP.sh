#!/bin/bash
date_str=$(date +%Y%m%d)
time_str=$(date +%H%M%S)
if [ -d "$date_str" ]
then
  echo "dir $date_str exists"
else
  echo "creating dir $date_str"
  mkdir "$date_str"
fi

g++ ./Common/Utility.cpp ./MLP/Filter.cpp ./MLP/Assembly.cpp ./MLP/MultiLayerPartition.cpp ./PUNCH/Filter/G_Graph.cpp ./PUNCH/Assemble/A_Graph.cpp -o ./bin/MLP -std=c++11 > ./logs/"$date_str"/"$time_str".log 2>&1
./bin/MLP ./data/paras.txt ./data/nodes_all ./data/links ./result/ >> ./logs/"$date_str"/"$time_str".log 2>&1