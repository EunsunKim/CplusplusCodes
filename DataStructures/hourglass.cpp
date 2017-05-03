# Hackerrank - Data Structures - 2D Arrays
# Input information : There are 6 lines of input, where each line contains 6 space-separated integers describing 2D Array.
# Output format     : Print the largest (maximum) hourglass sum found in A.
##########################################################################################################################
# Input example 
/*
1 1 1 0 0 0
0 1 0 0 0 0
1 1 1 0 0 0
0 9 2 - 4 - 4 0
0 0 0 - 2 0 0
0 0 - 1 - 2 - 4 0
*/
# Expected Output   : 13
# solutions by Cecilia Kim

#include <iostream>
#include <vector>
#include <algorithm>  // std::min_element, std::max_element
using namespace std;

int main() {
	vector< vector<int> > arr(6, vector<int>(6));
	for (int arr_i = 0; arr_i < 6; arr_i++) {
		for (int arr_j = 0; arr_j < 6; arr_j++) {
			cin >> arr[arr_i][arr_j];
		}
	}	
	int tsum[16];
	int count = 0;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)	{
			int t1 = arr[i][j] + arr[i][j+1] + arr[i][j+2];
			int t2 = arr[i + 1][j + 1];
			int t3 = arr[i+2][j] + arr[i+2][j+1] + arr[i+2][j+2];
			tsum[count] = t1 + t2 + t3; 			
			count++;
		}
	}	
	cout << *max_element(tsum, tsum + 16);
	
	return 0;
}
