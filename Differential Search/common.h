#ifndef COMMON_H
#define COMMON_H
// Global file #include-s
#ifndef IOSTREAM_H
#define IOSTREAM_H /**< C++ iostream */
#include <iostream>
#endif
#ifndef FSTREAM_H
#define FSTREAM_H /**< C++ iostream */
#include <fstream>
#endif
#ifndef CASSERT_H
#define CASSERT_H	 /**< C++ cassert */
#include <cassert>
#endif
#ifndef MATH_H
#define MATH_H /**< math.h */
#include <math.h>
#endif
#ifndef STRING_H
#define STRING_H /**< string.h */
#include <string>
#endif
#ifndef STL_ALGORITHM_H
#define STL_ALGORITHM_H
#include <algorithm> /**< STL algorithm */
#endif
#ifndef STL_VECTOR_H
#define STL_VECTOR_H /**< STL vector */
#include <vector>
#endif
#ifndef STL_MAP_H
#define STL_MAP_H /**< STL vector */
#include <map>
#endif
#ifndef STL_SET_H
#define STL_SET_H	/**< STL set */
#include <set>
#endif
#ifndef CSTDINT_H
#define CSTDINT_H
#include <stdint.h>
#endif
#ifndef STL_STRING_H
#define STL_STRING_H
#include <string>
#endif
#include    <sstream>
#include <iomanip>
#include <bitset>
#include <omp.h>

using namespace std;

//diff Table
extern vector <vector <pair <unsigned int, unsigned int> > > diffTable;

const int HW_D = 2; //Max hamming weight for the difference (s-box related)
const int max_as = 100;

//PRESENT Differential Table
const uint32_t diffTabOriginal[16][16]={                           // best      ave(exp)	 	worst
		{16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1.0       1.0				1.0		1.0
		{0, 0, 0, 4, 0, 0, 0, 4, 0, 4, 0, 0, 0, 4, 0, 0 }, // 0.25      1/4=0.25		0.25	0.25
		{0, 0, 0, 2, 0, 4, 2, 0, 0, 0, 2, 0, 2, 2, 2, 0 }, // 0.25      1/7=0.14286		0.125	0.2
		{0, 2, 0, 2, 2, 0, 4, 2, 0, 0, 2, 2, 0, 0, 0, 0 }, // 0.25		1/7=0.14286		0.125	0.2
		{0, 0, 0, 0, 0, 4, 2, 2, 0, 2, 2, 0, 2, 0, 2, 0 }, // 0.25		1/7=0.14286		0.125	0.2
		{0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 2, 2, 4, 2, 0, 0 }, // 0.25		1/7=0.14286		0.125	0.2
		{0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 4, 2, 0, 0, 4 }, // 0.25 		1/6=0.16667		0.125	0.2
		{0, 4, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 4 }, // 0.25		1/6=0.16667		0.125	0.2
		{0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 4, 0, 2, 0, 4 }, // 0.25		1/6=0.16667		0.125	0.2
		{0, 0, 2, 0, 4, 0, 2, 0, 2, 0, 0, 0, 2, 0, 4, 0 }, // 0.25		1/6=0.16667		0.125	0.2
		{0, 0, 2, 2, 0, 4, 0, 0, 2, 0, 2, 0, 0, 2, 2, 0 }, // 0.25		1/7=0.14286		0.125
		{0, 2, 0, 0, 2, 0, 0, 0, 4, 2, 2, 2, 0, 2, 0, 0 }, // 0.25		1/7=0.14286		0.125
		{0, 0, 2, 0, 0, 4, 0, 2, 2, 2, 2, 0, 0, 0, 2, 0 }, // 0.25		1/7=0.14286		0.125
		{0, 2, 4, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0 }, // 0.25		1/7=0.14286		0.125
		{0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0 }, // 0.25		1/8=0.125		0.125
		{0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4 }  // 0.25		1/4=0.25		0.25
};

// Macros
#ifndef NROUNDS
#define NROUNDS 12 //Number of rounds being tested
#endif

#ifndef WORD_SIZE
#define WORD_SIZE 4			  /**< Word size in  bits. */
#endif

#define high1_64(h1in) ( (uint64_t)h1in >> 63 )	//msb as lsb
#define high4_64(h4in) ( (uint64_t)h4in >> 60 )	//4 msb as lsb
#define low4_64(l4in)  ( (uint64_t)l4in << 60 ) //4 lsb as msb
#define low32_64(l32in)( (uint64_t)l32in<< 32 ) //32 lsb as msb
#define rotate1l_64(r1lin)	( high1_64(r1lin) | ( r1lin << 1 ) )	//input rotated left (1x)
#define rotate4l_64(r4lin)	( high4_64(r4lin) | ( r4lin << 4 ) )	//input rotated left (4x)
#define rotate4r_64(r4rin)  ( low4_64(r4rin)  | ( r4rin >> 4 ) )    //input rotated right(4x)
#define swap32(s32rin)      ( low32_64(s32rin)| ( s32rin>>32 ) )    //swap the left 32 bits with the right

//for 8-bit cyclic left shift
#define high8_32(h8in) ( (uint64_t)h8in >> 24 ) //msb as lsb
#define rotate8l_32(r8lin)  ( high8_32(r8lin) | ( r8lin << 8 ) )    //input rotated left (8x) for 32-bit of LSBs

//for 8-bit cyclic right shift
#define low8_32(l8in) ( (uint64_t)l8in << 24 ) //lsb as msb
#define rotate8r_32(r8rin)  ( low8_32(r8rin) | ( r8rin >> 8 ) )    //input rotated right (8x) for 32-bit of LSBs

// Function declarations
uint32_t random32();

uint32_t hw4(uint32_t x);
uint32_t hw6(uint32_t x);
uint32_t hw8(uint32_t x);

uint32_t hw16(uint32_t x);
uint64_t hw64_4_t(uint64_t x);

uint32_t hw32(uint32_t x);

uint32_t hw32_4(uint32_t x);

uint64_t hw64_4(uint64_t x);

bool is_even(uint32_t i);

uint32_t gen_sparse(uint32_t hw, uint32_t n);

void print_binary(uint32_t n);

void HW(int n, int r, int *position, int sz, vector<uint64_t>& data) ;

void storeInput(int *position, int sz, uint64_t tmp, vector<uint64_t>& data);

void diffTabComp();

double log2( double n );

string int_to_hex(uint64_t x);


#endif  // #ifndef COMMON_H
