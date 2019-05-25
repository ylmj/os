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
//显示每执行一次后所有进程的状态及有关信息
void print(PCB *run, PCB *ready, PCB *finish)
{
	cout << endl << "name" << "\t" << "cputime" << "\t" << "needtime" << "\t" << "priority" << "\t" << "state"<< endl;
	cout << endl << "正在运行:" << endl;
	if (run)
	{
		cout << run->name << "\t" << run->cputime << "\t" << run->needtime << "\t\t" << run->prio << "\t\t" << run->state << endl;
		run = NULL;
	}
	cout << endl << "就绪队列:" << endl;
	while (ready->next)
	{
		if (ready->next)
		{
			cout << ready->next->name << "\t" << ready->next->cputime << "\t" << ready->next->needtime << "\t\t" << ready->next->prio << "\t\t" << ready->next->state << endl;
			ready = ready->next;
		}
	}
	cout << endl << "完成队列:" << endl;
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
//在优先数算法中，将尚未完成的PCB 按优先数顺序插入到就绪队列中
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
//轮转法插入
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
//插入完成队列
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
//创建新进程，并将它的PCB插入就绪队列
void create1(int n, PCB *ready)
{
	PCB *p;
	for (int i = 0; i < n; i++)
	{
		p = new PCB;
		p->next = NULL;
		cout << endl << "进程名称：";
		cin >> p->name;
		cout << endl << "该进程执行时间：";
		cin >> p->needtime;
		p->cputime = 0;
		p->prio = 50 - p->needtime;
		p->round = 0;
		p->flag = false;
		p->state = 'W';
		insert1(p, ready);
	}
}
//轮转法，并将它的PCB插入就绪队列
void create2(int n, PCB *ready)
{
	PCB *p;
	for (int i = 0; i < n; i++)
	{
		p = new PCB;
		p->next = NULL;
		cout << endl << "进程名称：";
		cin >> p->name;
		cout << endl << "该进程执行时间：";
		cin >> p->needtime;
		p->cputime = 0;
		p->prio = 0;
		p->round = 2;
		p->flag = false;
		p->state = 'W';
		insert2(p, ready);
	}
}
//优先调度调度就绪队列的第一个进程投入运行
void firstin1(int time, PCB *ready, PCB *run, PCB *finish)
{
	run = NULL;
	while (ready->next)
	{
		if (ready->next)
		{
			run = ready->next;
			ready->next = run->next;
			run->next = NULL;//移出就绪队列
			run->state = 'R';
			run->prio--;
			if (!run->flag)
			{
				run->flag = true;
			}
			run->cputime++;
			run->needtime--;
			time++;//运行
			if (run->needtime <= 0)
			{
				run->needtime = 0;
			}
			print(run, ready, finish);
			if (run->needtime <= 0)
			{
				insert3(run, finish);//插入完成队列
				run = NULL;
				print(run, ready, finish);
				firstin1(time, ready, run, finish);
			}
			else
			{
				insert1(run, ready);//插入就绪队列
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
//时间片轮转法调度就绪队列的第一个进程投入运行
void firstin2(int time, PCB *ready, PCB *run, PCB *finish)
{
	run = NULL;
	while (ready->next)
	{
		if (ready->next)
		{
			run = ready->next;
			ready->next = run->next;
			run->next = NULL;//移出就绪队列
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
			}//运行
			print(run, ready, finish);
			if (run->needtime <= 0)
			{
				insert3(run, finish);//插入完成队列
				run = NULL;
				print(run, ready, finish);
				firstin2(time, ready, run, finish);
			}
			else
			{
				insert2(run, ready);//插入就绪队列
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
//按优先数算法调度进程
void prisch(PCB *ready, PCB *run, PCB *finish)
{
	int n, time = 0;
	cout << endl << "请输入进程个数：";
	cin >> n;
	create1(n, ready);
	print(run, ready, finish);
	firstin1(time, ready, run, finish);
}
//按时间片轮转法调度进程
void roundsch(PCB *ready, PCB * run, PCB *finish)
{
	int n, time = 0;
	cout << endl << "请输入进程个数：";
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
		cout << endl << "1.优先级调度算法\t2.轮转调度算法" << endl<< "请选择算法:";
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
			cout << endl << "输入有误, 请重新输入" << endl;
			break;
		}
		delete finish, ready, run;
	}
}