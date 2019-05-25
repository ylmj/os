#include<iostream>
using namespace std;
struct PCB {
	char name[100];
	int prio;
	int round;
	int cputime;
	int needtime;
	
	bool flag;
	char state;

	PCB* next;
};
//��ʾÿִ��һ�κ����н��̵�״̬���й���Ϣ
void print(PCB *run, PCB *ready, PCB *finish)
{
	cout << endl << "name" << "\t" << "cputime" << "\t" << "needtime" << "\t" << "priority" << "\t" << "state"<< endl;
	cout << endl << "��������:" << endl;
	if (run)
	{
		cout << run->name << "\t" << run->cputime << "\t" << run->needtime << "\t\t" << run->prio << "\t\t" << run->state << endl;
		run = NULL;
	}
	cout << endl << "��������:" << endl;
	while (ready->next)
	{
		if (ready->next)
		{
			cout << ready->next->name << "\t" << ready->next->cputime << "\t" << ready->next->needtime << "\t\t" << ready->next->prio << "\t\t" << ready->next->state << endl;
			ready = ready->next;
		}
	}
	cout << endl << "��ɶ���:" << endl;
	while (finish->next)
	{
		if (finish->next)
		{
			cout << finish->next->name << "\t" << finish->next->cputime << "\t" << finish->next->needtime << "\t\t" << finish->next->prio << "\t\t" << finish->next->state << endl;
			finish = finish->next;
		}
	}
	cout << endl;
	system("pause");
}
//���������㷨�У�����δ��ɵ�PCB ��������˳����뵽����������
void insert1(PCB *p, PCB *ready)
{
	PCB *q, *temp;
	q = new PCB;
	q->next = NULL;
	temp = new PCB;
	temp->next = NULL;
	temp = ready;
	q = ready->next;
	while (q && (q->prio) >= (p->prio))
	{
		temp = q;
		q = q->next;
	}
	if (!q)
	{
		p->state = 'W';
		temp->next = p;
		p->next = NULL;
	}
	else
	{
		p->state = 'W';
		p->next = q;
		temp->next = p;
	}
}
//��ת������
void insert2(PCB *p, PCB *ready)
{
	PCB *q;
	q = new PCB;
	q->next = NULL;
	q = ready;
	while (q->next)
	{
		q = q->next;
	}
	p->state = 'W';
	q->next = p;
	p->next = NULL;
}
//������ɶ���
void insert3(PCB *p, PCB *finish)
{
	PCB *q;
	q = new PCB;
	q->next = NULL;
	q = finish;
	while (q->next)
	{
		q = q->next;
	}
	q->next = p;
	p->state = 'F';
	p->next = NULL;
}
//�����½��̣���������PCB�����������
void create1(int n, PCB *ready)
{
	PCB *p;
	for (int i = 0; i < n; i++)
	{
		p = new PCB;
		p->next = NULL;
		cout << endl << "�������ƣ�";
		cin >> p->name;
		cout << endl << "�ý���ִ��ʱ�䣺";
		cin >> p->needtime;
		p->cputime = 0;
		p->prio = 50 - p->needtime;
		p->round = 0;
		p->flag = false;
		p->state = 'W';
		insert1(p, ready);
	}
}
//��ת������������PCB�����������
void create2(int n, PCB *ready)
{
	PCB *p;
	for (int i = 0; i < n; i++)
	{
		p = new PCB;
		p->next = NULL;
		cout << endl << "�������ƣ�";
		cin >> p->name;
		cout << endl << "�ý���ִ��ʱ�䣺";
		cin >> p->needtime;
		p->cputime = 0;
		p->prio = 0;
		p->round = 2;
		p->flag = false;
		p->state = 'W';
		insert2(p, ready);
	}
}
//���ȵ��ȵ��Ⱦ������еĵ�һ������Ͷ������
void firstin1(int time, PCB *ready, PCB *run, PCB *finish)
{
	run = NULL;
	while (ready->next)
	{
		if (ready->next)
		{
			run = ready->next;
			ready->next = run->next;
			run->next = NULL;//�Ƴ���������
			run->state = 'R';
			run->prio--;
			if (!run->flag)
			{
				run->flag = true;
			}
			run->cputime++;
			run->needtime--;
			time++;//����
			if (run->needtime <= 0)
			{
				run->needtime = 0;
			}
			print(run, ready, finish);
			if (run->needtime <= 0)
			{
				insert3(run, finish);//������ɶ���
				run = NULL;
				print(run, ready, finish);
				firstin1(time, ready, run, finish);
			}
			else
			{
				insert1(run, ready);//�����������
				run = NULL;
				print(run, ready, finish);
				firstin1(time, ready, run, finish);
			}
		}
		else
		{
			run = NULL;
		}
	}
}
//ʱ��Ƭ��ת�����Ⱦ������еĵ�һ������Ͷ������
void firstin2(int time, PCB *ready, PCB *run, PCB *finish)
{
	run = NULL;
	while (ready->next)
	{
		if (ready->next)
		{
			run = ready->next;
			ready->next = run->next;
			run->next = NULL;//�Ƴ���������
			run->state = 'R';
			if (!run->flag)
			{
				run->flag = true;
			}
			if (run->needtime >= run->round)
			{
				run->cputime += run->round;
			}
			else
			{
				run->cputime += run->needtime;
			}
			if (run->needtime >= run->round)
			{
				time += run->round;
				run->needtime -= run->round;
			}
			else
			{
				time += run->needtime;
				run->needtime = 0;
			}//����
			print(run, ready, finish);
			if (run->needtime <= 0)
			{
				insert3(run, finish);//������ɶ���
				run = NULL;
				print(run, ready, finish);
				firstin2(time, ready, run, finish);
			}
			else
			{
				insert2(run, ready);//�����������
				run = NULL;
				print(run, ready, finish);
				firstin2(time, ready, run, finish);
			}
		}
		else
		{
			run = NULL;
		}
	}
}
//���������㷨���Ƚ���
void prisch(PCB *ready, PCB *run, PCB *finish)
{
	int n, time = 0;
	cout << endl << "��������̸�����";
	cin >> n;
	create1(n, ready);
	print(run, ready, finish);
	firstin1(time, ready, run, finish);
}
//��ʱ��Ƭ��ת�����Ƚ���
void roundsch(PCB *ready, PCB * run, PCB *finish)
{
	int n, time = 0;
	cout << endl << "��������̸�����";
	cin >> n;
	create2(n, ready);
	print(run, ready, finish);
	firstin2(time, ready, run, finish);
}
void main()
{
	while (true)
	{
		PCB *run, *ready, *finish;
		run = new PCB;
		run = NULL;
		ready = new PCB;
		ready->next = NULL;
		finish = new PCB;
		finish->next = NULL;
		int choice;
		cout << endl << "1.���ȼ������㷨\t2.��ת�����㷨" << endl<< "��ѡ���㷨:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			prisch(ready, run, finish);
			break;
		case 2:
			roundsch(ready, run, finish);
			break;
		default:
			cout << endl << "��������, ����������" << endl;
			break;
		}
		delete finish, ready, run;
	}
}