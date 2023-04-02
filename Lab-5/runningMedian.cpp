#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> integerVector;
    int element;
	
    while (cin >> element) // Read inputs until end-of-file (EOF) is reached. {
        integerVector.push_back(element);
		
	// Since 'integerVector' was sorted before the introduction of 'element', use insertion sort to place 'element' in its correct position. 
        for (int i = integerVector.size() - 2; i >= 0; i--) {
            if (integerVector[i] > integerVector[i + 1]) {
                swap(integerVector[i], integerVector[i + 1]);
            }
            else {
                break;
            }
        }
		
	/* If 'integerVector' has an odd number of elements, the median is the element in the middle. Otherwise it is the average of the two elements in the middle.
         * Since median is either 'x' or 'x.5', calculate & print median as a one decimal point number to STDOUT.
         */        
        if (integerVector.size() % 2 == 1) {
            cout << fixed << setprecision(1) << integerVector[integerVector.size() / 2] << ".0\n";
        }
        else {
            cout << (double)(integerVector[integerVector.size() / 2 - 1] + integerVector[(integerVector.size() / 2)]) / 2 << endl;
        }
    }
    
    return 0;
}
