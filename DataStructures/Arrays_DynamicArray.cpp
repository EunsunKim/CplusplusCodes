/* Hackerrank - Data Structures - Dynamic Array
Input information : The first line contains two space-separated integers, N,Q respectively.                    
				    N - the number of sequences
					Q - the number of queries
Output format     : For each type 2 query, print the updated value of lastAns on a new line.
############################################################################################
Sample Input
2 5
1 0 5
1 1 7
1 0 3
2 1 0
2 1 1
Sample Output
7
3

solution by Cecilia Kim
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>  // std::min_element, std::max_element
using namespace std;

int main() {	
	
	int N, Q, x, y, lastAns = 0, queryType = 0;
		
	cin >> N >> Q;

	vector <int>seq;
	vector <vector<int>>seqList(N, seq);
		
	for (int i = 0; i < Q; i++) {		
		cin >> queryType >> x >> y;
			if (queryType == 1)	{				
				seqList[((x ^ lastAns) % N)].push_back(y);
			}
			else {				
				lastAns = seqList[((x ^ lastAns) % N)][y % seqList[((x ^ lastAns) % N)].size()];				
				cout << lastAns << endl;
			}			
	}
	return 0;
}
