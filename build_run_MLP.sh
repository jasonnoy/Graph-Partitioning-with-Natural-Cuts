#!/bin/bash
date_str=$(date +%Y%m%d)
time_str=$(date +%H%M%S)

if [ -d bin ]
then
  echo "output dir: ./bin"
else
  echo "creating dir bin, output dir: ./bin"
  mkdir bin
fi

if [ -d logs ]
then
  echo "log dir: ./logs"
else
  echo "creating log dir ./logs"
  mkdir logs
fi

if [ -d ./logs/"$date_str" ]
then
  echo "log output dir: ./logs/$date_str"
else
  echo "creating log output dir: ./logs/$date_str"
  mkdir "./logs/$date_str"
fi

if [ -f "./logs/$date_str/$time_str.log" ]
then
  echo "log .logs/$date_str/$time_str.log exists, log output to $time_str _1"
  touch ./logs/"$date_str"/"$time_str"_1.log || exit
else
  echo "log output to .logs/$date_str/$time_str.log"
  touch ./logs/"$date_str"/"$time_str".log || exit
fi

g++ ./MLP/MultiLayerPartition.cpp ./MLP/Assembly.cpp ./MLP/Filter.cpp ./MLP/AdaptivePrinter.cpp ./MLP/Preprocess.cpp ./MLP/GraphPrinter.cpp ./Common/Utility.cpp ./PUNCH/Filter/G_Graph.cpp ./PUNCH/Assemble/A_Graph.cpp -o ./bin/MLP -std=c++11 > ./logs/"$date_str"/"$time_str".log 2>&1

if [ -f "./result/phantom_nodes.txt" ]
then
  echo "phantom_nodes file found."
  ./bin/MLP ./data/paras.txt ./data/nodes_all ./data/links ./result/ 1 >> ./logs/"$date_str"/"$time_str".log 2>&1
else
  echo "phantom_nodes file not found."
  ./bin/MLP ./data/paras.txt ./data/nodes_all ./data/links ./result/ 0 >> ./logs/"$date_str"/"$time_str".log 2>&1
fi
echo "Finished"