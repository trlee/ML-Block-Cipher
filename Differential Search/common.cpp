#include "stdafx.h"
#ifndef COMMON_H
#include "common.h"
#endif

#ifndef CP_DIFF_TRAIL_SEARCH
#include "cp-diff-trail-search.h"
#endif

#include <vector>
#include <map>

using namespace std;
/**
 * Generate a random 32-bit value.
 */
//uint32_t random32()
//{
 // return(random() ^ (random() << 16));
//}

/**
* Hamming weight of a 4-bit word (only those that are involved in sbox computation)
*/
uint32_t hw4(uint32_t x)
{
    int i;
    int w=0;
    int offset = 0x2;
    for (i=0; i<4; i++){
        if ((x&offset)!=0)
            w++;
        offset = offset<<2;
    }
    return w;
}

/**
* Hamming weight of a 6-bit word (only those that are involved in sbox computation)
*/
uint32_t hw6(uint32_t x)
{
    int i;
    int w=0;
    int offset = 0x2;
    for (i=0; i<6; i++){
        if ((x&offset)!=0)
            w++;
        offset = offset<<2;
    }
    return w;
}

/**
 * Hamming weight of a byte.
 */
uint32_t hw8(uint32_t x)
{
     int i;
     int w=0;
     for(i=0; i<8; i++)
          w+=((x>>i) & 1);
     return w;
}

/**
* Hamming weight of a 16-bit word
*/
uint32_t hw16(uint32_t x)
{
    int i;
    int w=0;
    int offset = 0x2;
    for (i=0; i<8; i++){
        if ((x&offset)!=0)
            w++;
        offset = offset<<2;
    }
    return w;
}

/**
* Hamming weight of a 64-bit word (only those that are involved in sbox computation)
*/
uint64_t hw64_4_t(uint64_t x){
    int i;
    int w=0;
    int offset = 4;
    for (i=0; i<8; i++){
        offset += 8;
        if (((x>>offset)&0xF)!=0)
            w++;
    }
    return w;
}

/**
 * Hamming weight of a 32-bit word
 */
uint32_t hw32(uint32_t x)
{
     int i;
     int w=0;
     for(i=3; i>=0; i--) {
          w+=hw8((x >> i*8) & 0xff);
     }
     return w;
}

uint32_t hw32_4(uint32_t x)
{
  int i;
  int w=0;
  uint32_t y;

  for(i=0; i<8; i++) {
    y = x>>(4*i);
    if((y&0xF)!=0)
      w+=1;
    }
    return w;
  }

  uint64_t hw64_4(uint64_t x)
{
  int i;
  int w=0;
  uint64_t y;

  for(i=0; i<16; i++) {
    y = x>>(4*i);
    if((y&0xF)!=0)
      w+=1;
    }
    return w;
  }

/**
 * Returns true if the argument is an even number.
 */
bool is_even(uint32_t i)
{
  bool b_ret = true;
  if((i%2) == 1)
	 b_ret = false;
  return b_ret;
}

/**
 * Print a value in binary.
 */
void print_binary(uint32_t n)
{
  for(int i = 8; i >= WORD_SIZE; i--) {
	 cout<<" ";
  }
  for(int i = WORD_SIZE - 1; i >= 0; i--) {
	 int msb = (n >> i) & 1;
	 cout << msb;
  }
}

void storeInput(int *position, int sz, uint64_t tmp, vector<uint64_t>& data){
	if(sz==0){
		//cout << hex << tmp <<endl;
		data.push_back(tmp);
		return;
	}
	else{
		for(uint64_t i=0;i<16;i++){
			uint64_t tmp0;
			tmp0 = tmp ^ (i<<((position[sz-1]-1)*4));
			storeInput(position, sz-1, tmp0, data);
		}
	}
}

void HW(int n, int r, int *position, int sz, vector<uint64_t>& data) {
    for (int i = n; i >= r; i --) {
        // choose the first element
        position[r - 1] = i;
        if (r > 1) { // if still needs to choose
            // recursive into smaller problem
        	HW(i - 1, r - 1, position, sz, data);
        } else {
			// process the data regarding the positions
            // print out one solution
        	uint64_t tmp = 0;
        	storeInput(position, sz, tmp, data);

            //for (int i = 0; i < sz; i ++) {
            //    cout << position[i] << " ";
            //}
            //cout << endl;
        }
    }
}

double log2( double n )
{
    // log(n)/log(2) is log2.
    return log( n ) / log( 2 );
}


//------compute differential distribution table--------
void diffTabComp()
{
	uint32_t S[16] = {0xC, 0x5, 0x6, 0xB, 0x9, 0x0, 0xA, 0xD, 0x3, 0xE, 0xF, 0x8, 0x4, 0x7, 0x1, 0x2}; // SBox
	uint32_t diffTab[16][16] = {0};

	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			diffTab[i^j][S[i]^S[j]]++;
		}
	}

	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){
			cout<<diffTab[i][j]<<" ";
		}
		cout<<endl;
	}
}


string int_to_hex(uint64_t x)
{
  stringstream stream;
  stream << hex << x;
  return stream.str();
}

