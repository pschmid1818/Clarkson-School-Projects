#include<iostream>
#include<vector>
using namespace std;

vector<int> polymake(int degree);
void ip_multiply(vector<int> poly1, vector<int> poly2, int deg1, int deg2);

int main()
{
	int deg1,deg2;
	vector<int> output;
	vector<int> poly1;
	vector<int> poly2;
	
	cout <<"Enter the degree of your first polynomial: ";
	cin >>deg1;
	poly1=polymake(deg1);
	

	cout <<"Enter the degree of your second polynomial: ";
	cin >>deg2;
	poly2=polymake(deg2);
	
	ip_multiply(poly1,poly2,deg1,deg2);

	return 0;
}

vector<int> polymake(int degree)
{
	vector<int> output;
	for (int c=0; c<=degree; c++)
	{
		cout <<"Enter constant for x^" <<c <<": ";
		int x;
		cin >>x;
		output.push_back(x);
	}
	
	cout <<output[0] <<" + ";
	for (int c=1; c<degree; c++)
	{
		cout <<output[c] <<"x^" <<c <<" + ";
	}
	cout <<output[degree] <<"x^" <<degree <<endl;
	
	return output;
}	

void ip_multiply(vector<int> poly1, vector<int> poly2, int deg1, int deg2)
{
	vector<int> polyans;
	int degans=deg1+deg2;
	int x=0;
	
	for(int d=0; d<=degans; d++)
	{
		x=0;
		for(int a=0; a<=deg1; a++)
		{
			for (int b=0; b<=deg2; b++)
			{	
				if(a+b==d)
				{
					x+=poly1[a]*poly2[b];
				}
			}
		}
		polyans.push_back(x);
	}

	cout <<"The product of the two entered polynomials is: \n";
	cout <<polyans[0] <<" + ";
	for (int c=1; c<degans; c++)
	{
		cout <<polyans[c] <<"x^" <<c <<" + ";
	}
	cout <<polyans[degans] <<"x^" <<degans <<endl;
}	


