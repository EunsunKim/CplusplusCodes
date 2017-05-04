/* Hackerrank - Data Structures - Left Rotation

Question desc.
	A left rotation operation on an array of size nshifts each of the array's
	elements 1 unit to the left.

Input information : Given an array of n integers and a number, d, perform d left
					rotations on the array.
Output format     : Then print the updated array as a single line of space-separated
					integers.
####################################################################################
Sample Input
5 4
1 2 3 4 5
Sample Output
5 1 2 3 4

solution by Cecilia Kim
*/

#include <vector>
#include <iostream>
#include <algorithm>  //std::rotate
using namespace std;

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int d, shift;
	cin >> d >> shift;
	vector <int> arr(d);

	// set some values:
	for (int arr_i = 0; arr_i < d; arr_i++) {
		cin >> arr[arr_i];
	}	
	//for (int i = shift; i < d; i++) { cout << arr[i] << ' ';}
	//for (int i = 0; i < shift; i++) { cout << arr[i] << ' ';}
	
	// Rotate left the elements in range 
	rotate(arr.begin(), arr.begin() + shift, arr.end());   

	// print out content:
	//for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)  cout << *it << ' ';
	for( auto arr_elements : arr)		
	  cout << arr_elements << ' ';
	
	return 0;
}
