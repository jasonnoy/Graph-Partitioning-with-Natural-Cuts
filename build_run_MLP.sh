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

if [ -f "./logs/$date_str/$time_str.log" ]
then
  echo "log ./$date_str/$time_str.log exists, creating $time_str _1"
  touch ./"$date_str"/"$time_str"_1.log || exit
else
  echo "output to ./$date_str/$time_str.log"
  touch ./"$date_str"/"$time_str".log || exit
fi
g++ ./Common/Utility.cpp ./MLP/Filter.cpp ./MLP/Assembly.cpp ./MLP/MultiLayerPartition.cpp ./PUNCH/Filter/G_Graph.cpp ./PUNCH/Assemble/A_Graph.cpp -o ./bin/MLP -std=c++11 > ./logs/"$date_str"/"$time_str".log 2>&1
./bin/MLP ./data/paras.txt ./data/nodes_all ./data/links ./result/ >> ./logs/"$date_str"/"$time_str".log 2>&1