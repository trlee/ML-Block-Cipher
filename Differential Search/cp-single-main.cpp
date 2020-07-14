#include "stdafx.h"
/*#include <iostream>
#include "common.h"
#ifndef CP_DIFF_TRAIL_SEARCH
#include "cp-diff-trail-search.h"
#endif

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include <omp.h>
using namespace std;

extern std::map<string, double> diffSet;

struct sort_pred {
	bool operator()(const std::pair<unsigned int, unsigned int> &left, const std::pair<unsigned int, unsigned int> &right) {
		return left.second > right.second;
	}
};

vector <vector <pair<unsigned int, unsigned int > > > diffTable; //[sBoxNum][inputDiff][outputDiff][outputDiff/occurences out of 16]
std::map<string, int> inputSet;

int main()
{
/*******************************************************************************************************************/
/*                                  Initialize Differential Table                                                  */
/*******************************************************************************************************************/
/*    int B[NROUNDS];  // number of active sbox for rounds 0 ~ i

	//Load difference distribution table
		for(unsigned int i=0;i<16;i++){
			vector<pair <unsigned int, unsigned int> > row;
			for(unsigned int j=0; j<16; j++){
				//pair<unsigned int, unsigned int> element;
				if(diffTabOriginal[i][j]!=0){
					row.push_back(make_pair(j, diffTabOriginal[i][j]));
				}
			}
			sort(row.begin(), row.end(), sort_pred());
			diffTable.push_back(row);
		}

	cout<<"-------------- CP Diff Table ---------------"<<endl;
    for(int i=0;i<diffTable.size();i++){
        for(int j=0; j<diffTable[i].size(); j++){
            cout << diffTable[i][j].first<<" ";
            cout << diffTable[i][j].second<<", ";
        }
        cout<<endl;
    }

/*******************************************************************************************************************/
/*                                  Single Path Differential Search                                                */
/*******************************************************************************************************************/
/*
        cout<<"Perform active s-box truncated search..."<<endl;
        cp_AS_search(B); //cp-diff-trail-search
        cout<<"------Optimal number of Active Sbox for each rounds--------"<<endl;
        for(uint32_t i = 0; i < NROUNDS; i++) {
            cout<<"Round "<<i<<": "<<B[i]<<endl; // B[i]: the smallest number of active Sbox for rounds 0 ~ i
        }
    cout << "Press 'enter' key to exit..." << endl;
	getchar();
	return 0;
}*/
