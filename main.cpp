#include<iostream>
#include<vector>

using namespace std;

int A[9][9] = 
{
	{8,0,0,0,0,0,0,0,0},
	{0,0,3,6,0,0,0,0,0},
	{0,7,0,0,9,0,2,0,0},
	
	{0,5,0,0,0,7,0,0,0},
	{0,0,0,0,4,5,7,0,0},
	{0,0,0,1,0,0,0,3,0},
	
	{0,0,1,0,0,0,0,6,8},
	{0,0,8,5,0,0,0,1,0},
	{0,9,0,0,0,0,4,0,0}
};
struct Point
{
	Point(int newRows,int newCols)
	{
		rows = newRows;
		cols = newCols;
	}
	int rows;
	int cols;
	int value[10] = {0,1,2,3,4,5,6,7,8,9}; // maybe value
};

typedef vector<Point> pointVec;

pointVec p;

void getMaybeValue()
{
	for(vector<Point>::iterator it = p.begin();it != p.end();it++)
	{
		for(int i = 0;i < 9;i++)
		{
			it->value[A[it->rows][i]] = 0;
		}
		for(int i = 0;i < 9;i++)
		{
			it->value[A[i][it->cols]] = 0;
		}
		
		int tempCols = it->cols / 3;
		int tempRows = it->rows / 3;
		for(int i = 0;i < 3;i++)
		{
			it->value[A[tempCols][i + tempRows]] = 0;
			it->value[A[tempCols + 1][i + tempRows]] = 0;
			it->value[A[tempCols + 2][i + tempRows]] = 0;
		}
	}
	
}

int main()
{
	for(int i = 0;i < 9;i++)
	{
		for(int j = 0;j < 9;j++)
		{
			if(A[i][j] == 0)
			{
				p.push_back(Point(i,j));
			}
		}
	}
	/**************check the number needed to fill****************/
	getMaybeValue();

	for(int i = 0;i < 10;i++)
	{
		cout<<p[0].value[i]<<endl;
	}
	
	
	return 0;
} 
