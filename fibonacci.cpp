#include <iostream>
#include <iomanip>
using namespace std;

int fibonacciTriangle(int row){
    int i = 1, j, a, b, resultLeft, resultRight, left, right;
    while (i <= row){
        j = 1;
        a = 0;        
        b = 1;
      
      // space
        while (j <= row - i){
            cout << "\t";
            j++;
        }
        left = i;
      
      //left side
        while (left > 0){            
            resultLeft = a + b;
            cout << resultLeft << "\t";
            a = b;
            b = resultLeft;
            left--;     //head from left to middle center
        }
        right = 2;
      
      //right side
        while (right <= i){   
            if (right == 2){cout << a << "\t";}
            else{   
                resultRight = resultLeft - a;
                cout << resultRight << "\t";
                resultLeft = a;
                a = resultRight;
            }
            right++;    //head from middle center to right
        }
        cout << "\n";
        i++;
    }
    cout << "\n" << endl;
    return 0;
}

// half triangle
int fibonacciHalfTriangle(int row){
    int a = 0, b = 1, c;
    for (int i = 1; i <= row+1; i++){
        a = 0;
        b = 1;
        for (int j = 1; j < i; j++){
            c = a + b;
            cout << c << "\t";
            a = b;
            b = c;
        }
        cout << endl;
    }
    cout << "\n" << endl;
    return 0;
}


int main() {
    int row;     
    cout << "Enter the number for Fibonacci triangle row count: ";
    cin >> row;
  
    fibonacciHalfTriangle(row);
    fibonacciTriangle(row);
}

