
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// ----------------------chooser---------------------
int nextPrime(unsigned p, vector<bool> &s)
{
    unsigned i = p;
    do
    {
        i++;
    }
    while (!s[i]);
    return i;
}
// ------------------- end chooser --------------------
// -----------------------generator----------------------------
void generator(unsigned p, unsigned e, unsigned n, vector<bool> &s)
{
    unsigned l = (e - p + 1u);
    unsigned start = e + 1u;
    unsigned end = (p) * l + nextPrime(p, s) - 1u;
    if (end >= n || end < 0)
    {
        end = n;
    }
    for (unsigned i = start; i <= end; i++)
    {
        s[i] = s[i - l];
    }
}
// -------------------end generator------------------------

// ---------------------selector---------------------------
void selection(unsigned p, unsigned e, vector<bool> &s)
{
    for (unsigned i = e; i >= p; i--)
    {
        if (s[i])
        {
            s[i * p] = false;
        }
    }
}

// ----------------end selector------------------
int  main()
{
    unsigned n;
    cout << "Enter the maximum number: ";
    cin >> n;

    vector<bool> s(max(n + 1u, 6u));

    clock_t start = clock();

    unsigned e, p;
    e = 2;
    p = 2;
    s[2] = true;
    s[3] = true;
    s[5] = true;


    do
    {
        generator(p, e, n, s);
        selection(p, e, s);
        e = p * (e - p + 1) + nextPrime(p, s) - 1;
        p = nextPrime(p, s);
    }
    while ((p * e <= n && p * e > 0));

    generator(p, e, n, s);

    do
    {
        selection(p, n / p, s);
        p = nextPrime(p, s);
    }
    while (p * p <= n);
    float timeA =(float)(clock() - start)/1000;
    cout << ( "Action time  = " );
    cout << timeA << " s";
    //----------------------------- RECODR TO FILE --------------------------
    ofstream record ("prime.txt");
    int k=0;
    for (unsigned i=0; i<= n; i++)
    {
        if(s[i])
        {
            k+=1;
            record << i <<",";
            if (k%25==0)
            {
                record << "\n";
            }
        }

    }
    record.close();

    return 0;
}
