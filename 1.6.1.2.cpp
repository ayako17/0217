#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
static void calculatenum(int n)
{
    double log2n = log2(n);
    double nlog2n = n * log2(n);
    double nSquared = n * n;
    cout <<setw(10)<<right<< n;
    cout << fixed << setprecision(2)<<setw(10) << right << log2n;
    cout << fixed << setprecision(2) << setw(10) << right << n;
    cout << fixed << setprecision(2) << setw(15) << right << nlog2n;
    cout << fixed << setprecision(2) << setw(15) << right << nSquared;
    cout << endl;
}
int main()
{
    int a[] = { 1,4,10,100,1000,10000 };
    int n = sizeof(a) / sizeof(a[0]);
    cout << setw(10) << "n:" << setw(12) << "log2(n):" << setw(8) 
         << "n:" << setw(15) << "n*log2(n):" << setw(15) << "n^2:" << endl;
    for (int i = 0; i < n; ++i)
    {
        calculatenum(a[i]);
    }
    return 0;
}

