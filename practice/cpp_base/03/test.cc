#include <iostream>
using namespace std;

class Sample 
{
public:
      Sample();
      void Display();
private:
      int i;
      static int k;
};

Sample::Sample() 
{
	i=0;
	k++;
}

void Sample::Display() 
{
   cout << "i=" << i << ",k=" << k << endl;
}

int Sample::k=0;

int main( ) 
{
    Sample a, b;
    a.Display();
    b.Display();
    
    return 0;
}