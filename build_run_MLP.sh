#!/bin/bash
date_str=$(date +%Y%m%d)
time_str=$(date +%H%M%S)

if [ -d bin ]
then
  echo "bin file output dir ./bin"
else
  echo "creating dir bin, bin file output dir ./bin"
  mkdir bin
fi

if [ -d result ]
then
  echo "result output dir ./result"
else
  echo "creating dir result, result output dir ./result"
  mkdir result
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
  echo "log .logs/$date_str/$time_str.log exists, creating {$time_str}_1"
  echo "log output to .logs/$date_str/{$time_str}_1.log"
  touch ./logs/"$date_str"/"$time_str"_1.log || exit
else
  echo "log output to .logs/$date_str/$time_str.log"
  touch ./logs/"$date_str"/"$time_str".log || exit
fi

g++ ./MLP/MultiLayerPartition.cpp -g -lpthread ./MLP/Assembly.cpp ./MLP/Filter.cpp ./MLP/AdaptivePrinter.cpp ./MLP/Preprocess.cpp ./MLP/GraphPrinter.cpp ./Common/Utility.cpp ./PUNCH/Filter/G_Graph.cpp ./PUNCH/Assemble/A_Graph.cpp -o ./bin/MLP -std=c++11 > ./logs/"$date_str"/"$time_str".log 2>&1

#./bin/MLP ./data/paras.txt /data/cris.su/code/ch-routing-demo/data/china/nodes /data/cris.su/code/ch-routing-demo/data/china/links ./result/ 50 >> ./logs/"$date_str"/"$time_str".log 2>&1

./bin/MLP ./data/paras.txt /data/map_data/rp_2.0/normal/2021_11_25_21_07_41/all/all/nodes_all /data/map_data/rp_2.0/normal/2021_11_25_21_07_41/all/all/links ./result/ 32 >> ./logs/"$date_str"/"$time_str".log 2>&1

# ./bin/MLP ./data/paras_beijing.txt ./data/nodes_all ./data/links ./result/beijing/ 32 >> ./logs/"$date_str"/"$time_str".log 2>&1

echo "Finished"