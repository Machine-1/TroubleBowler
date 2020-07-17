#include <stdio.h>
#include <cstring>
#include <string>
#include <queue>
#include <set>
#include "time.h"
using namespace std;

#define PAIR 6
#define MAX 2 * PAIR+1

int control(char start[], char goal[])
{
	int expend(int *push_time, queue<string> &q, set<string> &visitedSet_1, set<string> &visitedSet_2);
	void recnum(int *r, int *p, int *time);		//	use this function to record the traverse layer 

	set<string> visitedSet_s;
	set<string> visitedSet_g;
	queue<string> q_s, q_g;
	int success = 0;
	int push_time[2] = { 0,0 };
	int record[3][2] = { {0 ,1} ,{0,1} ,{1} };  //分别对应					顺序			逆序      次数  
												//			record			 0			 0			0
												//			addition		 1			 1

	q_s.push(start);								//先将start进队,并标记为已遍历
	visitedSet_s.insert(start);
	q_g.push(goal);								//先将goal进队,并标记为已遍历
	visitedSet_g.insert(goal);

	
	while (!q_s.empty() && !q_g.empty())
	{
		if (q_s.size() < q_g.size())
		{
			success = expend(push_time, q_s, visitedSet_s, visitedSet_g);
			recnum(record[0],push_time,record[2]);
		}
		else
		{
			success = expend(push_time+1, q_g, visitedSet_g, visitedSet_s);
			recnum(record[1],push_time+1,record[2]);
		}

		if (success == 1)
		{
			break;
		}
		
	}
	
	return record[2][0];
}



int expend(int* push_time,queue<string> &q, set<string> &visitedSet_1, set<string> &visitedSet_2)
{
	string frontStr;
	string result;

		int c = 0;									//接球手的序号
		int p = 0;									//接球手正对面的序号
		int i = 0;
		frontStr = q.front();
		q.pop();

		c = frontStr.find('o');					//获取接球手位置,即在字符串中找到‘o’的位置
		p = (c + PAIR) % (PAIR * 2);			//获取接球手正对的位置

		if (c % PAIR == 0)						//无球者处于左上或左下	a	 b	c	d	e	f	
		{										//						o	 h	i	j	k	g
			for (i = 0; i < 2; i++)
			{
				swap(frontStr[c], frontStr[p + i]);				//交换字符串中的字符

				result = frontStr;
				swap(frontStr[c], frontStr[p + i]);	//恢复原样
													//如果result 存在于set中，说明它已经被遍历过了
				if (visitedSet_1.count(result) == 0) //该状态未被遍历时
				{
					visitedSet_1.insert(result);  //标记为已遍历，也就是插入到集合之中
					q.push(result);
					(*push_time)++;
				

					if (visitedSet_2.count(result) == 1)
					{
						return 1;
					}
				}
			}//完成for循环以后，就遍历完成了一个状态下的分支，并将其标记，逐个插入到队列中
		}

		else if (c % PAIR == PAIR - 1)						//无球者处于右上或右下，只能有2种投球情况
		{
			for (i = -1; i < 1; i++)
			{
				swap(frontStr[c], frontStr[p + i]);

				result = frontStr;
				swap(frontStr[c], frontStr[p + i]);	//恢复原样

				if (visitedSet_1.count(result) == 0) //该状态未被遍历时
				{
					visitedSet_1.insert(result);  //标记为已遍历
					q.push(result);
					(*push_time)++;

					if (visitedSet_2.count(result) == 1)
					{
						return 1;
					}
				}
			}
		}

		else									//有3种投球情况
			for (i = -1; i < 2; i++)
			{
				swap(frontStr[c], frontStr[p + i]);

				result = frontStr;
				swap(frontStr[c], frontStr[p + i]);	//恢复原样

				if (visitedSet_1.count(result) == 0) //该状态未被遍历时
				{
					visitedSet_1.insert(result);  //标记为已遍历
					q.push(result);
					(*push_time)++;

					if (visitedSet_2.count(result) == 1)
					{
						return 1;
					}
				}
			}

		return 0;


}

void recnum(int *r,int *p, int *time)						//分别对应					顺序			逆序      次数  
{															//		record，r[0]			 0			 0			0
	r[0]++;													//		addition, r[1]		 1			 1			
	if (r[0] == r[1])										//	r[0]记录结点出队的次数, r[1]记录每层遍历结点的个数，*p record the number of subnodes in each expend  
	{														//		when r[0]=r[1], last floor wasfinished, one way was done.
		r[1] = *p;
		*p = 0;
		r[0] = 0;
		(*time)++;
	}
}


int main(void)
{
	
	char start[MAX] = "abcdefghijko";
	char goal[MAX] = "obcdefghijka";
	clock_t start_time, end_time;
	start_time = clock();
	int answer = control(start, goal);
	end_time = clock();
	double Time = (double)(end_time - start_time)/CLOCKS_PER_SEC;;
	printf("The time of pitches is %d\n", answer);
	printf("The time cost is %fs", Time);
	return 0;
}
