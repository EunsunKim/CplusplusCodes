# Input information : The first line contains an integer, the number of integers in. 
#                     The second line contains  space-separated integers describing .
# Output format     : Print all  integers in  in reverse order as a single line of space-separated integers.
# Hackerrank - Data Structures - Arrays
# solutions by Cecilia Kim

#include <vector>
#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int arr_i = 0; arr_i < n; arr_i++) {
		cin >> arr[arr_i];
	}
	
	vector<int>::reverse_iterator rit = arr.rbegin();
	for (rit = arr.rbegin(); rit != arr.rend(); rit++)
		std::cout << *rit << ' ' ;

	return 0;
}
