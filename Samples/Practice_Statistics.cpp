// Practice_Statistics.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Mean: The "average" number
// Median: The middle number
// Mode: The most frequent number

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;
#pragma once

int main()
{
    int n;
    cout << "*** Enter the total numbers to get the median value \n";
    cin >> n;
    cout << " -> You entered " << n << endl;
    vector<int> numbers(n);
    cout << "*** Enter the each integer number to get the median value \n";
    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }
    sort(begin(numbers), end(numbers));

    double sum = accumulate(begin(numbers), end(numbers), 0);
    double average = sum / n;
    /*
    if the number of numbers is odd, the median is the middle data point in the list.
    if the number of numbers is even, the median is the average of the two middle data points in the list.
    */
    
    double median = numbers[n / 2];
    if (n%2 ==0)
    {
        median += numbers[n / 2 - 1];
        median /= 2;
    }
    /* 
    //same result
    double k = numbers[n / 2];
    double median = (n % 2 == 0) ? ((numbers[(n/2) - 1] + k))/2 : k;
    */
    
    map<int, int> findingMode;

    for(int j:numbers)
    {
        findingMode[j]++;
    }

    int mode = 0;

    for (auto j : findingMode)
    {
        if (j.second > findingMode[mode])
        {
            mode = j.first;
        }
    }
    cout << "---------- Result ----------\n";
    cout << "Average is " << average << "\n";
    cout << "Median is " << median << "\n";
    cout << "Mode is " << mode << "\n";
    cin >> n;
}
