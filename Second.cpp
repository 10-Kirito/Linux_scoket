#include<iostream>
using namespace std;

int main()
{
	int temp = 16;

	for(int i = 0;i < 15;i++)
	{
		for(int j = 0;j < 16;j++)
		{
			cout << char(temp)<<" ";
			temp ++;
		}
		cout<<endl;
	
	}




	return 0;
}
