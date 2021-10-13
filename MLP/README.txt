/*****************************************
* MLP - Multiple Layer Partition
*
* This software implements the MLP model using PUNCH algorithm in
* "Customizable Route Planning in Road Networks, Daniel Delling etc., Microsoft, 2013".
*
* Author: Junhui Ji, University of Sydney, Huolala Ltd intern.
* Last update date: 10.12.2021
******************************************/

MLP abstracted origin fractional filter and assembly phases into classes, making the project more OOP.
New MLP class is added as the front api for process control.
Under ./Bin/ directory, run the project as following:

./MLP <path of the parameter file for mlp> <path of the sw node file> <path of the sw link file> <output path>
e.g.  ./MLP ../data/paras.txt ../data/nodes_all ../data/links ../result/

Parameters: takes in a txt file, the formats of parameters are as following:
The first line is the number of layer n, the following n lines defines other parameters as following:
U, C, FI, M, Size of Pool
such as:
3
1024 1 1 1 16
4096 4 8 16 32
4096 8 16 32 64

