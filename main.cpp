#include<iostream>
#include<vector>
#include<deque>


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
	vector<int> value; // maybe value
};

typedef deque<Point> pointVec;

pointVec p;

void getMaybeValue()
{
	deque<Point>::iterator it = p.begin();
	while(it != p.end())
	{
		for(int i = 0;i < 10;i++)
		{
			(*it).value.push_back(i);
		}
		for(int i = 0;i < 9;i++)
		{
			(*it).value[A[it->rows][i]] = 0;
		}
		for(int i = 0;i < 9;i++)
		{
			(*it).value[A[i][it->cols]] = 0;
		}
		
		int tempCols = (*it).cols / 3;
		tempCols *= 3;
		int tempRows = (*it).rows / 3;
		tempRows *= 3;
		for(int i = 0;i < 3;i++)
		{
			(*it).value[A[tempRows][i + tempCols]] = 0;
			(*it).value[A[tempRows + 1][i + tempCols]] = 0;
			(*it).value[A[tempRows + 2][i + tempCols]] = 0;
		}
		/***************delete the zero***************/ 
		vector<int>::iterator itValue = (*it).value.begin();
		while(itValue != (*it).value.end())
		{
			if(*itValue == 0)
			{
				(*it).value.erase(itValue);
			}
			else
			{
				itValue++;
			}
		} 
		vector<int>((*it).value).swap((*it).value);//free the memory
		
//		if((*it).value.size() == 1)
//		{
//			A[(*it).rows][(*it).cols] = (*it).value[0];
//			p.erase(it);
//		}
//		else
//		{
			it++;
//		}
		
	}
	
}
/*************************************/
void display(void)
{
	for(int i = 0;i < 9;i++)
	{
		for(int j = 0;j < 9;j++)
		{
			cout<<A[i][j];
			if(j == 2 || j == 5 || j == 8)
			cout<<"|";
		}
		cout<<endl;
		if(i == 2 || i == 5)
		cout<<"------------"<<endl;
	}
} 
/*************************************/
bool check(Point &nowPoint,int nowValue)
{
	if(nowValue == 0)
		return false;
	for(int i = 0;i < 9;i++)
	{
		if(A[nowPoint.rows][i] == nowValue)
		return false;
	}
	for(int i = 0;i < 9;i++)
	{
		if(A[i][nowPoint.cols] == nowValue)
		return false;
	}
	int tempCols = nowPoint.cols / 3;
	tempCols *= 3;
	int tempRows = nowPoint.rows / 3;
	tempRows *= 3;
	for(int i = 0;i < 3;i++)
	{
		if(A[tempRows][i + tempCols] == nowValue 
		|| A[tempRows + 1][i + tempCols] == nowValue
		|| A[tempRows + 2][i + tempCols] == nowValue)
		return false;
	}
	return true;
}
/*********************************/
bool tryOneNumber(deque<Point> &q)
{
	if(q.empty())
	return true;
	
	Point tempPoint = q[0];
	q.pop_front();
	
	for(int i = 0;i < tempPoint.value.size();i++)
	{
		if(check(tempPoint,tempPoint.value[i]))
		{
			A[tempPoint.rows][tempPoint.cols] = tempPoint.value[i];
			if(tryOneNumber(q) == false)
			{
				A[tempPoint.rows][tempPoint.cols] = 0;
			}
			else
				return true;
			
		}
	}
	q.push_front(tempPoint);
	return false;
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

	tryOneNumber(p);
	
	display();
	
	return 0;
} 
