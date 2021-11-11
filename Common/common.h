#ifndef COMMON_H
#define COMMON_H

#include<vector>
#include<time.h>
#include<assert.h>
using namespace std;

//debug
#define VERBOSE(x) x
//#define VERBOSE(x)
//#define NDEBUG

//node
typedef uint32_t NodeID;
//typedef NodeID NodeID;
typedef double Coordinate;
typedef uint32_t NodeSize;
//typedef NodeID NodeSize;
#define REALLATLNG 100000.0

//edge
typedef uint32_t EdgeID;
typedef uint32_t EdgeWeight;
//typedef NodeID EdgeID;
//typedef NodeID EdgeWeight;
typedef unsigned long long Bits;

//random
#define RANDOM_LEN 999

//parameter
//#define DNCC 1 //detect natural cuts C (times)
////#define DNCF 5 //detect natrual cuts f NOTE: only for sample
//#define DNCF 10 //detect natrual cuts f, which sets the core size relative to the ring
//#define FI 2 //each pair reoptimize fail times limit
//#define M  4 //multistart and combination number of iteration


#endif //COMMON_H