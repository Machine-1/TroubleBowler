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
	int record[3][2] = { {0 ,1} ,{0,1} ,{1} };  //�ֱ��Ӧ					˳��			����      ����  
												//			record			 0			 0			0
												//			addition		 1			 1

	q_s.push(start);								//�Ƚ�start����,�����Ϊ�ѱ���
	visitedSet_s.insert(start);
	q_g.push(goal);								//�Ƚ�goal����,�����Ϊ�ѱ���
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

		int c = 0;									//�����ֵ����
		int p = 0;									//����������������
		int i = 0;
		frontStr = q.front();
		q.pop();

		c = frontStr.find('o');					//��ȡ������λ��,�����ַ������ҵ���o����λ��
		p = (c + PAIR) % (PAIR * 2);			//��ȡ���������Ե�λ��

		if (c % PAIR == 0)						//�����ߴ������ϻ�����	a	 b	c	d	e	f	
		{										//						o	 h	i	j	k	g
			for (i = 0; i < 2; i++)
			{
				swap(frontStr[c], frontStr[p + i]);				//�����ַ����е��ַ�

				result = frontStr;
				swap(frontStr[c], frontStr[p + i]);	//�ָ�ԭ��
													//���result ������set�У�˵�����Ѿ�����������
				if (visitedSet_1.count(result) == 0) //��״̬δ������ʱ
				{
					visitedSet_1.insert(result);  //���Ϊ�ѱ�����Ҳ���ǲ��뵽����֮��
					q.push(result);
					(*push_time)++;
				

					if (visitedSet_2.count(result) == 1)
					{
						return 1;
					}
				}
			}//���forѭ���Ժ󣬾ͱ��������һ��״̬�µķ�֧���������ǣ�������뵽������
		}

		else if (c % PAIR == PAIR - 1)						//�����ߴ������ϻ����£�ֻ����2��Ͷ�����
		{
			for (i = -1; i < 1; i++)
			{
				swap(frontStr[c], frontStr[p + i]);

				result = frontStr;
				swap(frontStr[c], frontStr[p + i]);	//�ָ�ԭ��

				if (visitedSet_1.count(result) == 0) //��״̬δ������ʱ
				{
					visitedSet_1.insert(result);  //���Ϊ�ѱ���
					q.push(result);
					(*push_time)++;

					if (visitedSet_2.count(result) == 1)
					{
						return 1;
					}
				}
			}
		}

		else									//��3��Ͷ�����
			for (i = -1; i < 2; i++)
			{
				swap(frontStr[c], frontStr[p + i]);

				result = frontStr;
				swap(frontStr[c], frontStr[p + i]);	//�ָ�ԭ��

				if (visitedSet_1.count(result) == 0) //��״̬δ������ʱ
				{
					visitedSet_1.insert(result);  //���Ϊ�ѱ���
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

void recnum(int *r,int *p, int *time)						//�ֱ��Ӧ					˳��			����      ����  
{															//		record��r[0]			 0			 0			0
	r[0]++;													//		addition, r[1]		 1			 1			
	if (r[0] == r[1])										//	r[0]��¼�����ӵĴ���, r[1]��¼ÿ��������ĸ�����*p record the number of subnodes in each expend  
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
