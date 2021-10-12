/*****************************************
* MLP - Multiple Layer Partition
*
* This software implements the MLP model using PUNCH algorithm in
* "Customizable Route Planning in Road Networks, Daniel Delling etc., Microsoft, 2013".
*
* Author: Junhui Ji, University of Sydney, Huolala Ltd intern.
* Last update date: 10.12.2021
******************************************/

Parameters: takes in a txt file, the formats of parameters are as following:
The first line is the number of layer n, the following n lines defines other parameters as following:
U, C, FI, M, Size of Pool
such as:
3
1024 1 1 1 16
4096 4 8 16 32
4096 8 16 32 64

