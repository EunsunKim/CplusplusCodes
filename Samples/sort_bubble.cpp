// by Eunsun Cecilia Kim
#include <vector>
#include <cmath>
#include <iostream>
#include <functional>

using namespace std;

//bubble sort
/////////////////////////////////////////////////////////////////////////
//
// basic c++ style sort method for integer
//
// bool ascending(int a, int b) { return a > b; }
// bool descending(int a, int b) { return a < b; }
//
//
//void sortBubble(vector<int>& a, int n, function<bool(int, int)> comp) {
//	for (int i = n - 1; i > 0; i--) {
//		for (int j = 0; j < i; j++) {
//			if (comp(a[j], a[j + 1])) {
//				int temp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = temp;
//			}
//		}
//	}
//}

template <typename T>
void templateBubbleSort(vector<T>& array, int n, function<bool(T, T)> comp) {
	for (int i = 0; i < (n - 1); i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (comp(array[j], array[j + 1])) {
				T temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

int main(int argc, char** argv) {

	int number = 10;
	if (argc > 1) number = atoi(argv[1]); // user command check
	
	vector<int> input(number);

	for (auto& e : input) {
		e = 1 + rand() % number;   //<cstdlib>  Generate random number
	}

	function<bool(int, int)> comp;
	comp = [](int a, int b) {return a > b; };
	templateBubbleSort(input, number, comp);
	cout << " ";
	for (auto e : input)
		cout << e << " ";
	cout << "\n";

	return 0;
}

