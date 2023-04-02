#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> integerVector;
    int element;
	
    while (cin >> element) // read integer inputs until end-of-file (EOF) is reached
	{
        integerVector.push_back(element);
		
		// since 'integerVector' was sorted before the introduction of 'element', use insertion sort to place 'element' in its correct position 
        for (int i = integerVector.size() - 2; i >= 0; i--) 
		{
            if (integerVector[i] > integerVector[i + 1]) {
                swap(integerVector[i], integerVector[i + 1]);
            }
            else {
                break;
            }
        }
		
		// since median is either 'x' or 'x.5' print median as a one decimal point number to STDOUT
        if (integerVector.size() % 2 == 1) 
		{
            cout << fixed << setprecision(1) << integerVector[integerVector.size() / 2] << ".0\n";
        }
        else 
		{
            cout << (double)(integerVector[integerVector.size() / 2 - 1] + integerVector[(integerVector.size() / 2)]) / 2 << endl;
        }
    }
    return 0;
}
