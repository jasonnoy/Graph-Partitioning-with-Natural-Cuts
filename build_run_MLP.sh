#!/bin/bash
date_str=$(date +%Y%m%d)
time_str=$(date +%H%M%S)

if [ -d bin ]
then
  echo "output dir ./bin"
else
  echo "creating dir bin, output dir ./bin"
  mkdir bin
fi

if [ -d logs ]
then
  echo "log dir ./logs"
else
  echo "creating log dir ./logs"
  mkdir logs
fi

if [ -d ./logs/"$date_str" ]
then
  echo "dir ./logs/$date_str exists"
else
  echo "creating dir ./logs/$date_str"
  mkdir "./logs/$date_str"
fi

if [ -f "./logs/$date_str/$time_str.log" ]
then
  echo "log .logs/$date_str/$time_str.log exists, creating $time_str _1"
  touch ./logs/"$date_str"/"$time_str"_1.log || exit
else
  echo "output to .logs/$date_str/$time_str.log"
  touch ./logs/"$date_str"/"$time_str".log || exit
fi

g++ ./MLP/MultiLayerPartition.cpp ./MLP/Assembly.cpp ./MLP/Filter.cpp ./MLP/AdaptivePrinter.cpp ./MLP/Preprocess.cpp ./MLP/GraphPrinter.cpp ./Common/Utility.cpp ./PUNCH/Filter/G_Graph.cpp ./PUNCH/Assemble/A_Graph.cpp -o ./bin/MLP -std=c++11 > ./logs/"$date_str"/"$time_str".log 2>&1

{ ./bin/MLP ./data/paras.txt ./data/nodes_all ./data/links ./result/1_1/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras1_2.txt ./data/nodes_all ./data/links ./result/1_2/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras1_3.txt ./data/nodes_all ./data/links ./result/1_3/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras1_4.txt ./data/nodes_all ./data/links ./result/1_4/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras2_1.txt ./data/nodes_all ./data/links ./result/2_1/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras2_2.txt ./data/nodes_all ./data/links ./result/2_2/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras2_3.txt ./data/nodes_all ./data/links ./result/2_3/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras2_4.txt ./data/nodes_all ./data/links ./result/2_4/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
#{ ./bin/MLP ./data/paras0_0.txt ./data/nodes_all ./data/links ./result/0_0/ >> ./logs/"$date_str"/"$time_str".log 2>&1;}
echo "Finished"