#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 3
#define L 100
#define MAX 2000

int queue[L];
int list[N];//�ڴ�ҳ�����
int count = 0;//�ڴ�ҳ��ʹ��ͳ��
int que_num = 0;//���ʶ�������ʹ�õ�ֵ
int flag = 0;//ÿ�û�һ��flag��+1
int first_come[N];//�����ڴ�ҳ���ʱ��
int last_use[N];//�ϴ�ҳ��ʹ��ʱ��
int state[N][2];//�ڸĽ���clock�㷨�����α�ʾ����λ�޸�λ
int clock_num;//�ڸĽ�clock�㷨�б�ʾ��ǰλ�ã�����ָ��
int count2 = 0;//ͳ�ƿ��ж�����q������ҳ����Ŀ
int m_count = 0;
typedef struct QNode  //�����н��Ķ���
{
	int val;
	int num;
	struct QNode *next;
}QNode, *Linklist;
Linklist p, q;//p�������޸�ҳ������q�������ҳ������
void sequence_generate(int p, int e, double t, int m)//�����������,����pΪ��������ʼλ�ã�eΪ����������ҳ����mΪ�������ƶ���
{
	int choice;
	double r;
	srand(time(0));
	for (int i = 0; i < m; i++, que_num++)//����L��ȡֵ��Χ��p��p+e֮����������Ϊ��������
		queue[que_num] = rand() % e + p;
	m_count++;
	printf("�������ɳɹ�����������Ϊ��\n");
	for (int i = 0; i < m*m_count; i++)
		printf("%d ", queue[i]);
	printf("\n");

	printf("�Ƿ�������ӷ������г���\n1.��\n2.��\n");
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		if (L < m_count*m)
		{
			printf("�ѳ�������������󳤶ȣ��Զ�����\n");
			return;
		}
		else
		{
			r = (rand() % 100)*0.01;
			if (r < t)
			{
				printf("����������p��ֵ\n");
				scanf_s("%d", &p);
			}
			else
				p = (p + 1) % N;
			sequence_generate(p, e, t, m);
		}
	}
	if (choice == 2)
		return;
}
int find_num(int a)//������һ��ʹ�ü��
{
	int i;
	for (i = que_num; i < L; i++)
	{
		if (queue[i] == a)
			return	i - que_num;
	}
	return MAX;//�������ֵ
}

void opt(int num) //����û��㷨,num�Ƿ��������е�һ��ֵ
{
	int i, max = 0, rep_num, temp = 0;
	if (count != N)//����ڴ�ҳ����ڿ�λ�ã����������
	{
		list[count] = num;
		count++;
		flag++;
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			if (list[i] == num)
				return;
		}
		for (i = 0; i<N; i++)
		{
			{
				temp = find_num(list[i]);
				if (temp > max)
				{
					max = temp;
					rep_num = i;
				}
			}
		}
		list[rep_num] = num;
		flag++;
	}
}

int find_first()//�ҵ����Ƚ����ڴ�ҳ�����һ��
{
	int i, result = 0, min = first_come[0];
	for (i = 0; i < N; i++)
	{
		if (first_come[i] < min)
		{
			min = first_come[i];
			result = i;
		}
	}
	return result;
}
void fifo(int num)//�Ƚ��ȳ��û��㷨
{
	int i, rep_num, min = MAX;
	if (count != N)//����ڴ�ҳ����ڿ�λ�ã����������
	{
		list[count] = num;
		first_come[count] = count;
		count++;
		flag++;
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			if (list[i] == num)
				return;
		}
		rep_num = find_first();
		list[rep_num] = num;
		first_come[rep_num] = que_num;
		flag++;
	}

}

int find_last()//�ҵ����δʹ�õ���һ��
{
	int i, result = 0, min = last_use[0];
	for (i = 0; i < N; i++)
	{
		if (last_use[i] < min)
		{
			min = last_use[i];
			result = i;
		}
	}
	return result;
}
void lru(int num)//������δʹ���㷨
{
	int i, rep_num = 0;
	if (count != N)//����ڴ�ҳ����ڿ�λ�ã����������
	{
		list[count] = num;
		last_use[count] = count;
		count++;
		flag++;
	}
	else
	{
		for (i = 0; i < N; i++)
		{
			if (list[i] == num)
			{
				last_use[i] = que_num;
				return;
			}
		}
		rep_num = find_last();
		list[rep_num] = num;
		last_use[rep_num] = que_num;
		flag++;
	}
}

int find_clock()
{
	int i = clock_num;
	while (true)//���û���ҵ��ڶ���ҳ�棬�����¿�ʼѰ�ҵ�һ��ҳ��
	{
		while (true)//Ѱ�ҵ�һ��ҳ��
		{
			if (state[i][0] == 0 && state[i][1] == 0)
				return i;
			i = (i + 1) % N;
			if (i == clock_num)
				break;
		}
		while (true)//���û���ҵ���һ��ҳ�棬��ʼ�ҵڶ���ҳ��
		{
			if (state[i][0] == 0 && state[i][1] == 1)
				return i;
			state[i][0] = 0;
			i = (i + 1) % N;
			if (i == clock_num)
				break;
		}
	}
}
void clock_pro(int num)
{
	int i, rep_num;
	for (i = 0; i < N; i++)
	{
		if (list[i] == num)
		{
			state[i][0] = 1;
			state[i][1] = 0;
			clock_num = i;
			return;
		}
	}
	rep_num = find_clock();
	clock_num = (rep_num + 1) % N;
	list[rep_num] = num;
	state[rep_num][0] = 1;
	state[rep_num][1] = 1;
	flag++;
}

void create_linklist(Linklist &p, int num)
{
	p = (Linklist)malloc(sizeof(QNode));
	if (!p)
		exit(-1);
	p->val = 0;
	p->next = p;
}
void Insert_LNode(Linklist &m, int e, int f)//��ѭ�������в����µĽ�㣬��Lͷ��㿪ʼ����������
{
	Linklist p, q;
	p = (Linklist)malloc(sizeof(QNode));
	q = (Linklist)malloc(sizeof(QNode));
	q->val = e;
	q->num = f;
	p = m;
	while (p->next != m)
	{
		p = p->next;
	}
	p->next = q;
	q->next = m;
}
void Exchange_LNode(Linklist &m, int e, int f, int i)//������L�����Ϊi�Ľ���滻ΪvalΪe��numΪf�Ľ��
{
	if (m->next == m)
		exit(-1);
	Linklist p, q;
	int j = 0;
	p = (Linklist)malloc(sizeof(QNode));
	q = (Linklist)malloc(sizeof(QNode));
	q->val = e;
	q->num = f;
	p = m;
	for (j = 0; j < i; j++)//ʹpΪ����������ǰһ����㣬��Ӧ��֤��ɾ����һ����ͷ���ʱi=0���Դ�����
		p = p->next;
	q->next = p->next->next;
	p->next = q;
}
bool Search_LinkList(Linklist &m, int e, int &i)//�ҵ�����L������Ϊe�Ľ�㣬����i������λ�ã�i=1��ʾ��һ����ͷ��㣬��������
{
	i = 1;
	if (m->next == m)
		exit(-1);
	Linklist p;
	p = (Linklist)malloc(sizeof(QNode));
	if (!p)
		exit(-1);
	p = m->next;		//pָ������ĵ�һ����㣨��ͷ��㣩
	while (p != m && p->val != e)
	{
		p = p->next;
		i++;
	}
	if (p == m)		//û���ҵ�����Ҫ��Ľ��
		return false;
	return true;
}
void pba(int number)//p�������޸�ҳ������q�������ҳ������
{
	int i, min = MAX, rep_num = 0, j = 0;
	QNode *t = p->next;
	QNode *r = q->next;
	if (count != N)//����ڴ�ҳ����ڿ�λ�ã����������
	{
		Insert_LNode(p, number, que_num);
		flag++;
		count++;
	}
	else
	{
		for (i = 0; i < N; i++)//���numer�Ѿ������޸Ķ���p��
		{
			if (t->val == number)
				return;
			t = t->next;
		}
		for (i = 0; i < 2; i++)//������ж�������num
		{
			if (r->val == number)
			{
				Insert_LNode(p, number, r->num);;//�����q�м���p�Ķ�β
				QNode *s = q;//�����q���Ƴ�
				for (int ii = 0; ii < 2; ii++)
				{
					if (s->next->val == number)
					{
						s->next = s->next->next;
						break;
					}
					s = s->next;
				}
				//��p�����������Ƴ�
				t = p->next;
				for (i = 0; i < N; i++)//�ҵ����Ƚ������һ��
				{
					if (t->num < min)
						min = t->num;
					t = t->next;
				}
				t = p;
				for (i = 0; i < N; i++)
				{
					if (t->next->num == min)
					{
						t->next = t->next->next;
						break;
					}
					t = t->next;
				}
				count2--;
				return;
			}
			r = r->next;
		}
		//������ж�����û��number
		t = p->next;
		for (i = 0; i < N; i++)//�ҵ����Ƚ������һ��
		{
			if (t->num < min)
				min = t->num;
			t = t->next;
		}
		t = p->next;
		for (i = 0; i < N; i++)//�����Ƚ������һ��ҳ����̭�����뵽����ҳ������
		{
			if (t->num == min)
			{
				Insert_LNode(q, t->val, min);//���������ж���q�Ķ�β
				count2++;
				if (count2 == 2)
					q->next = q->next->next;//�Ƴ�q�еĵ�һ������
				Exchange_LNode(p, number, que_num, j);//���޸Ķ���p�ж�Ӧλ���滻
				flag++;
				break;
			}
			t = t->next;
			j++;
		}
	}
}

void print()//��ӡ����ڴ�ҳ����е�ǰ���
{
	for (int i = 0; i < N&& i <= que_num; i++)
		printf("%d ", list[i]);
	printf("\n");
}
int main()
{
	int choice, m;
	while (true)
	{
		printf("��*��*��*��*��*��*��*��*��*��*��\n");
		printf("����ϵͳ���Ĵ�ʵ�飺ҳ���û��㷨\n0.���ɷ�������\n1.����û��㷨\n2.�Ƚ��ȳ��û��㷨\n3.������δʹ���㷨\n4.�Ľ�clock�㷨\n5.ҳ�滺���㷨PBA\n6.�˳�\n");
		printf("��*��*��*��*��*��*��*��*��*��*��\n");
		scanf_s("%d", &choice);
		if (choice == 0)
		{
			int p, e;
			double t;
			printf("����������p,e,t,m��ֵ\n");
			scanf_s("%d%d%lf%d", &p, &e, &t, &m);
			sequence_generate(p, e, t, m);
		}
		if (choice == 1)
		{
			count = 0;
			flag = 0;
			for (que_num = 0; que_num < m*m_count; que_num++)
			{
				opt(queue[que_num]);
				printf("��%d��ҳ�����:", que_num + 1);
				print();
			}
			printf("ȱҳ��Ϊ%.2f\n", (float)flag / (m * m_count));
			system("pause");
		}
		if (choice == 2)
		{
			count = 0;
			flag = 0;
			for (que_num = 0; que_num < m*m_count; que_num++)
			{
				fifo(queue[que_num]);
				printf("��%d��ҳ�����:", que_num + 1);
				print();
			}
			printf("ȱҳ��Ϊ%.2f\n", (float)flag / (m * m_count));
			system("pause");
		}
		if (choice == 3)
		{
			count = 0;
			flag = 0;
			for (que_num = 0; que_num < m*m_count; que_num++)
			{
				lru(queue[que_num]);
				printf("��%d��ҳ�����:", que_num + 1);
				print();
			}
			printf("ȱҳ��Ϊ%.2f\n", (float)flag / (m * m_count));
			system("pause");
		}
		if (choice == 4)
		{
			count = 0;
			flag = 0;
			clock_num = 0;
			for (que_num = 0; que_num < m*m_count; que_num++)
			{
				clock_pro(queue[que_num]);
				printf("��%d��ҳ�����:", que_num + 1);
				print();
			}
			printf("ȱҳ��Ϊ%.2f\n", (float)flag / (m * m_count));
			system("pause");
		}
		if (choice == 5)
		{
			count = 0;
			flag = 0;
			create_linklist(p, N);
			create_linklist(q, 2);
			for (que_num = 0; que_num < m*m_count; que_num++)
			{
				pba(queue[que_num]);
				printf("��%d��ҳ�����:", que_num + 1);
				QNode *t = p->next;
				for (int i = 0; i < N && i <= que_num; i++)
				{
					printf("%d ", t->val);
					t = t->next;
				}
				printf("\n");
			}
			printf("ȱҳ��Ϊ%.2f\n", (float)flag / (m * m_count));
			system("pause");
		}
		if (choice == 6)
			return 0;
	}
}


