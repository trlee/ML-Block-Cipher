/*
 * present-diff-trail-search.h
 *
 *  Created on: Oct 29, 2014
 *      Author: chinkako, Teh Je Sen
 */

#ifndef CP_DIFF_TRAIL_SEARCH_H_
#define CP_DIFF_TRAIL_SEARCH_H_


int cp_init_estimate(uint32_t next_round,  int B[NROUNDS], unsigned short internalTruncState[NROUNDS+1][2]);

void cp_AS_threshold_search(const int n, const int nrounds, int B[NROUNDS], int* Bn,
	unsigned short internalTruncState[NROUNDS + 1][2]);

uint32_t cp_AS_search(int B[]);

void roundProcess(const int n, const int nrounds, int as, int B[], int* Bn,
	unsigned short internalTruncState[NROUNDS+1][2]);

void concreteDiff(unsigned short truncInput, vector<int> &filteredAS);

void F_Function(uint64_t& ori, uint64_t diff, const int n, vector<int>& activeAS, int AS, const int sboxnum, int hw, double prob);

//void setL(unsigned int left, int HW_L, vector<int>& hwL_idx, vector<int>& hwR_idx, vector<int>& truncActiveSBOX);

//void setR(unsigned int left, unsigned int right, int HW_R,  vector<int>& hwR_idx,  vector<int>& truncActiveSBOX);

#endif
