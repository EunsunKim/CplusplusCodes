//simple array

#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, sum = 0;

	cin >> n;
	vector<int> arr(n);

	for (int arr_i = 0; arr_i < n; arr_i++)
		cin >> arr[arr_i];

	for (int n : arr)
		sum += n;
	cout << sum;

	return 0;
}
