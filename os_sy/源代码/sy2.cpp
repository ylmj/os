/*�����������㷨*/
#include<iostream>
#define MAX_SIZE 32767
using namespace std;
struct Node
{
	int pid;
	int adr;//�����׵�ַ
	int size;//������С
	Node *next;//ָ����һ��������ָ��
};
void print(Node *head, Node *pro)//���������������Ϣ
{
	Node *p, *pl;
	p = head;
	if (p->next)
	{
		cout << endl << "���ж��У�" << endl << "���\t��ַ\t��ַ\t��С" << endl;
		while (p->next)
		{
			p = p->next;
			if (p->pid < 0)
			{
				p->pid = 0;
			}
			cout << endl <<p->pid<<"\t"<< p->adr << "\t" << p->adr + p->size - 1 << "\t" << p->size << endl;
		}
	}
	pl = pro;
	if (pl->next)
	{
		cout << endl << "���̶��У�" << endl << "���\t��ַ\t��ַ\t��С" << endl;
		while (pl->next)
		{
			pl = pl->next;
			cout << endl << pl->pid << "\t" << pl->adr << "\t" << pl->adr + pl->size - 1 << "\t" << pl->size << endl;
		}
	}
}
//����ͷ��ڴ�ĺϷ��� �鿴���Ƿ��ڽ��̶���
bool check(int pid, Node *pro)
{
	Node *pl;
	bool check = false;
	pl = pro;
	while (pl->next)
	{
		pl = pl->next;
		if (pl->adr == pid)
		{
			check = true;
			break;
		}
	}
	if (!check)
	{
		cout << endl << "û�д˽���" << endl;
	}
	return check;
}

void assignment1(int pid, int free, Node *head, Node *pro)
{
	Node *head1, *after, *assign, *pl;
	assign = (Node*)malloc(sizeof(Node));
	head1 = head;
	after = head->next;
	pl = pro;
	while (pl->next)
	{
		pl = pl->next;
	}
	while (after != NULL&&after->size < free)
		{
			head1 = head1->next;
			after = after->next;
		}
	
	if (after == NULL)
	{
		cout << endl << "����ʧ��" << endl;
	}
	else
	{
		if (after->size == free)
		{
			assign->pid = pid;
			assign->adr = after->adr;
			assign->size = free;
			assign->next = NULL;
			head1->next = after->next;
			pl->next = assign;
			pl = pl->next;
		}
		else
		{
			assign->pid = pid;
			assign->adr = after->adr;
			assign->size = free;
			assign->next = NULL;
			after->adr += free;
			after->size -= free;
			pl->next = assign;
			pl = pl->next;
		}
		cout << endl << "����ɹ�" << endl;
	}
}
void acceptment1(int pid, Node *head, Node *pro)
{
	Node *head1, *after, *back, *pl;
	head1 = head;
	after = head->next;
	pl = pro;
	while (pl->next)
	{
		pl = pl->next;
		if (pl->adr == pid)
		{
			break;
		}
	}
	back = (Node*)malloc(sizeof(Node));
	back->pid = pl->pid;
	back->adr = pl->adr;
	back->size = pl->size;
	back->next = NULL;
	bool insert = false;
	//���ж���Ϊ�� 
	if (after == NULL)
	{
		head1->next = back;
		cout << endl << "���ճɹ�" << endl;
	}
	//���ж��в�Ϊ��
	else
	{
		while (!insert && after)
		{
			//�������յķ������������������ַ��С��С������룩
			if (after == NULL || back->adr >= head1->adr && back->adr <= after->adr)
			{
				head1->next = back;
				back->next = after;
				insert = true;
			}
			else
			{
				head1 = head1->next;
				after = after->next;
			}
		}
		if (insert)
		{
			if (back->adr == head1->adr + head1->size && after && back->adr + back->size == after->adr)
			{
				//��ǰ�����ͬʱ�ϲ�
				head1->size += back->size;
				head1->size += after->size;
				head1->next = after->next;
				back = NULL;
				after = head1->next;
			}
			else if (back->adr == head1->adr + head1->size)
			{
				//��ǰ�����ϲ�
				head1->size += back->size;
				head1->next = back->next;
				back = NULL;
			}
			else if (after&&back->adr + back->size == after->adr)
			{
				//�ͺ�����ϲ�
				back->size += after->size;
				back->next = after->next;
				after = back;
			}
			cout << endl << "���ճɹ�" << endl;
		}
		else
		{
			cout << endl << "����ʧ��" << endl;
		}
	}
	Node *p;
	p = pro;
	while (p->next)
	{
		if (p->next->pid == pl->pid)
		{
			p->next = pl->next;
			break;
		}
		p = p->next;
	}
}
void assignment2(int pid, int free, Node *head, Node *pro)
{
	Node *head1, *after, *assign, *p, *pl;
	assign = (Node*)malloc(sizeof(Node));
	p = (Node*)malloc(sizeof(Node));
	head1 = head;
	after = head->next;
	pl = pro;
	while (pl->next)
	{
		pl = pl->next;
	}

	while (after != NULL&&after->size < free)
	{
			head1 = head1->next;
			after = after->next;
	}
	if (after == NULL)
	{
		cout << endl << "����ʧ��" << endl;
	}
	else
	{
		if (after->size == free)
		{
			assign->pid = pid;
			assign->adr = after->adr;
			assign->size = free;
			assign->next = NULL;
			head1->next = after->next;
			pl->next = assign;
			pl = pl->next;
		}
		else
		{
			assign->pid = pid;
			assign->adr = after->adr;
			assign->size = free;
			assign->next = NULL;
			head1->next = after->next;
			pl->next = assign;
			pl = pl->next;
			//�Է�����������
			p = after;
			p->adr += free;
			p->size -= free;
			head1 = head;
			after = head->next;
			if (after == NULL)
			{
				head1->next = p;
				p->next = NULL;
			}
			else
			{
				while (after != NULL && after->size < p->size)
					{
						head1 = head1->next;
						after = after->next;
					}
					head1->next = p;
					p->next = after;					
			}
		
		}
		cout << endl << "����ɹ�" << endl;
	}
}

void acceptment2(int pid, Node *head, Node *pro)
{
	Node *head1, *after, *back, *pl;
	head1 = head;
	after = head->next;
	pl = pro;
	while (pl->next)
	{
		pl = pl->next;
		if (pl->adr == pid)
		{
			break;
		}
	}
	back = (Node*)malloc(sizeof(Node));
	back->pid = pl->pid;
	back->adr = pl->adr;
	back->size = pl->size;
	back->next = NULL;
	bool insert = false;
	if (after == NULL)
	{
		//���ж���Ϊ�� 
		head1->next = back;
		cout << endl << "���ճɹ�" << endl;
	}
	else
	{
		//���ж��в�Ϊ��
		//��ǰ�����ϲ�
		head1 = head;
		after = head->next;
		while (after)
		{
			if (back->adr == after->adr + after->size)
			{
				head1->next = after->next;
				after->size += back->size;
				back = after;
				back->next = NULL;
				after = after->next;
				break;
			}
			else
			{
				head1 = head1->next;
				after = after->next;
			}
		}
		//�ͺ�����ϲ�
		head1 = head;
		after = head->next;
		while (after)
		{
			if (after->adr == back->adr + back->size)
			{
				head1->next = after->next;
				back->size += after->size;
				back->next = NULL;
				after = after->next;
				break;
			}
			else
			{
				head1 = head1->next;
				after = after->next;
			}
		}
		head1 = head;
		after = head->next;
		while (!insert)
		{
			//�������յĿ���뵽ǡ����λ�ã���������С��С����
			if (after == NULL || back->size >= head1->size && back->size <= after->size)
			{
				head1->next = back;
				back->next = after;
				insert = true;
				break;
			}
			else
			{
				head1 = head1->next;
				after = after->next;
			}
		}
		if (insert)
		{
			cout << endl << "���ճɹ�" << endl;
		}
		else
		{
			cout << endl << "����ʧ��" << endl;
		}
	}
	Node *p;
	p = pro;
	while (p->next)
	{
		if (p->next->pid == pl->pid)
		{
			p->next = pl->next;
			break;
		}
		p = p->next;
	}
}

void start(Node *head)
{
	Node *pro;
	pro = (Node*)malloc(sizeof(Node));
	pro->next = NULL;
	int option, choose, free, pid,adr;
	print(head, pro);
	cout << endl << "1.������Ӧ�㷨" << endl << endl << "2.�����Ӧ�㷨" << endl;
	cout << endl << "��ѡ��:";
	cin >> option;
	while (true)
	{
		switch (option)
		{
		case 1://������Ӧ�㷨
			cout << endl << "1.�����ڴ�" << endl << endl << "2.�����ڴ�" << endl << endl << "3.����" << endl;
			cout << endl << "��ѡ��:";
			cin >> choose;
			switch (choose)
			{
			case 1://�����ڴ�
				cout << endl << "���������ID: ";
				cin >> pid;
				cout << endl << "�������С��";
				cin >> free;
				assignment1(pid, free, head, pro);
				print(head, pro);
				cout << "------------------------------------------" << endl;
				break;
			case 2://�����ڴ�
				cout << endl << "��������ַ: ";
				cin >> adr;
				if (check(adr, pro))
				{
					acceptment1(adr, head, pro);
					print(head, pro);
					cout << "------------------------------------------" << endl;
				}
				break;
			case 3:
				return;
				print(head, pro);
				cout << endl << "1.������Ӧ�㷨" << endl << endl << "2.�����Ӧ�㷨" << endl;
				cout << endl << "��ѡ��:";
				cin >> option;
				break;
			default:
				cout << endl << "������������������" << endl;
				break;
			}
			break;
		case 2://�����Ӧ�㷨
			cout << endl << "1.�����ڴ�" << endl << endl << "2.�����ڴ�" << endl << endl << "3.����" << endl;
			cout << endl << "��ѡ��:";
			cin >> choose;
			switch (choose)
			{
			case 1://�����ڴ�
				cout << endl << "���������ID: ";
				cin >> pid;
				cout << endl << "�������С��";
				cin >> free;
				assignment2(pid, free, head, pro);
				print(head, pro);
				cout << "------------------------------------------" << endl;
				break;
			case 2://�����ڴ�
				cout << endl << "��������ַ: ";
				cin >> adr;
				if (check(adr, pro))
				{
					acceptment2(adr, head, pro);
					print(head, pro);
					cout << "------------------------------------------" << endl;
				}
				break;
			case 3:
				return;
				print(head, pro);
				cout << endl << "1.������Ӧ�㷨" << endl << endl << "2.�����Ӧ�㷨" << endl;
				cout << endl << "��ѡ��:";
				cin >> option;
				break;
			default:
				cout << endl << "������������������" << endl;
				break;
			}
			break;
		default:
			cout << endl << "������������������" << endl;
			print(head, pro);
			cout << endl << "1.������Ӧ�㷨" << endl << endl << "2.�����Ӧ�㷨" << endl;
			cout << endl << "��ѡ��:";
			cin >> option;
			break;
		}
	}
}
void main()
{
	while (true)
	{
		//��ʼ��
		Node *head, *p;
		head = (Node*)malloc(sizeof(Node));
		p = (Node*)malloc(sizeof(Node));
		p->adr = 0;
		p->size = MAX_SIZE;
		p->next = NULL;
		head->next = p;
		//��ʼ�����
		start(head);
		free(head);
		head = NULL;
		free(p);
		p = NULL;
	}
}