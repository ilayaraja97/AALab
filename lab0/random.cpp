#include<bits/stdc++.h>
using namespace std;
// Pseudo Random Number Generator
class RandomGenerator{
	int seed;
	int x;
	const static int a=1103515245,c=12345,m=2147483648;
	public:
	RandomGenerator(int seed){
		this->seed=seed;
		this->x=0;
		rand();
	}
	RandomGenerator(){
		this->seed=time(NULL);
		this->x=0;
		rand();
	}
	// [INT_MIN,INT_MAX]
	int rand(){
		this->x=(a*seed+c)%m;
		this->seed=x;
		return x;
	}
	// [0,1]
	double frand(){
		double r=rand();
		return (r/INT_MAX+1)/2;
	}
	// [a,b]
	int rand(int a,int b)
	{
		return frand()*(b-a)+a;
	}
};
int main()
{
	RandomGenerator x;
	cout<<x.rand(2,7)<<endl;
	cout<<x.rand(5,10)<<endl;
	cout<<x.rand(3,8)<<endl;
	cout<<x.rand(2,9)<<endl;
	return 0;
}
