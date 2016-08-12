#include <iostream>
#include <string>
#define False 0
#define True 1
using namespace std;

int Max[100][100] = { 0 };//���������������Դ���������
int Available[100] = { 0 };//ϵͳ������Դ
int Allocation[100][100] = { 0 };//ϵͳ�ѷ�����Դ
int Need[100][100] = { 0 };//����Ҫ��Դ
string Name[20] = { "0" };//��Դ������
string workName[20] = { "0" };//���̵�����
int Request[100] = { 0 };//������Դ����
string Temp[20] = { "0" };//��Ű�ȫ����
int Work[100] = { 0 };//���ϵͳ���ṩ����Դ
int M;//���̵���Ŀ
int N;//��Դ��������
int Sum[100];//�����Դ������
int Finish[100] = { 0 };//��ʾϵͳ�Ƿ����㹻����Դ���������
void Init()
{
	string name;
	int num;
	cout << "������ϵͳ�ṩ��Դ�����������";
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cout << "��Դ" << i + 1 << "�����ƣ�";
		cin >> name;
		Name[i] = name;
		cout << "��Դ������Ϊ��";
		cin >> num;

		Sum[i] = num;
	}
	cout << endl;
	cout << "��������̵�������";
	cin >> M;
	cout << endl;
	cout << "����������̵�����(�ո����)��" << endl;
	for (int i = 0; i < M; i++)
	{
		string name;
		cin >> name;
		workName[i] = name;
	}
	cout << "����������̵����������" << M << "*" << N << "����Max" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Max[i][j];
		}
	}
	//����ʵ����������ҵ��Max����ĳ�ʼ��
	cout << "������������Ѿ��������Դ����" << M << "*" << N << "����Allocation" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Allocation[i][j];
			if (Allocation[i][j]>Max[i][j])
			{
				cout << "����������������룺" << endl;
				cin >> Allocation[i][j];
			}
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
	//�������Allocation��Need�ĳ�ʼ��
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < M; i++)
		{
			Sum[j] = Sum[j] - Allocation[i][j];
		}
		Available[j] = Sum[j];
	}
	cout << endl;
}
//���ϼ����Available��ֵ
void showdata()   //��ӡ����Դ��
{
	cout << "	  Max         Allocation       Need " << endl;
	cout << "������" << "  ";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << Name[j] << " ";
		}
		cout << "         ";
	}
	cout << endl;
	for (int i = 0; i < M; i++)
	{
		cout << workName[i] << "      ";
		for (int j = 0; j < N; j++)
		{
			cout << Max[i][j] << ",";
		}
		cout << "         ";
		for (int j = 0; j < N; j++)
		{
			cout << Allocation[i][j] << ",";
		}
		cout << "         ";
		for (int j = 0; j < N; j++)
		{
			cout << Need[i][j] << ",";
		}
		cout << endl;
	}
	cout << "Available��ֵΪ��" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << Available[i] << ",";
	}
	cout << endl;
}
void restore(int i)//ϵͳ��Դ����
{
	for (int j = 0; j < N; j++)
	{
		Available[j] = Available[j] + Request[j];
		Allocation[i][j] = Allocation[i][j] - Request[j];
		Need[i][j] = Need[i][j] + Request[j];
	}
}
void ChangeData(int i)//������Դ���䣬�޸�ֵ
{
	for (int j = 0; j < N; j++)
	{
		Available[j] = Available[j] - Request[j];
		Allocation[i][j] = Allocation[i][j] + Request[j];
		Need[i][j] = Need[i][j] - Request[j];
	}
}
int Safe()//��ȫ�㷨
{
	int m = 0;
	for (int i = 0; i < N; i++)
	{
		Work[i] = Available[i];
	}
	for (int i = 0; i < M; i++)//�����������Ľ���
	{
		int count = 0;//���ü�������������Դ��Need��ҪС��work
		for (int j = 0; j < N; j++)
		{
			if (Finish[i] == False&&Need[i][j] <= Work[j])
			{
				count++;
				if (count == N)
				{
					for (int k = 0; k < N; k++)
					{
						Work[k] = Work[k] + Allocation[i][k];
					}
					Finish[i] = True;
					Temp[m] = workName[i];//�洢��ȫ����
					m++;
					if (sizeof(Temp) / sizeof(Temp[0]) != M)//�������жϻ�����M��
					{
						i = -1;//ÿ�δ�ͷ��ʼѭ������
					}
				}
			}
		}
	}
	for (int i = 0; i < M; i++)
	{
		if (Finish[i] == False)
		{
			cout << "û�а�ȫ���У�" << endl;
			return -1;
			break;
		}
	}
	cout << "ϵͳ�ǰ�ȫ��!" << endl;
	cout << "��ȫ����Ϊ��";
	for (int i = 0; i < M; i++)
	{
		cout << Temp[i] << " ";
	}
	cout << endl;
	return 1;
}
void InitFinish()  //ÿ�ε������м��㷨��Ҫ��Finish��ʼ����False
{
	for (int i = 0; i < M; i++)
	{
		Finish[i] = False;
	}
}
void Share()//�������м��㷨��������Դ�����ж�
{
	int num;
	char ch = 'y';
	cout << "������Ҫ�������Դ�Ľ�����ţ�";
	cin >> num;
	cout << "��������ҵ" << workName[num - 1] << "�������Դ:" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << Name[i] << ":";
		cin >> Request[i];
	}
	for (int j = 0; j < N; j++)
	{
		if (Request[j]>Need[num - 1][j])
		{
			cout << "����" << workName[num - 1] << "�������Դ��������Ҫ����Դ!!!";
			cout << "�����䣡" << endl;
			ch = 'n';
			break;
		}

		if (Request[j] > Available[j])
		{
			cout << "����" << workName[num - 1] << "�������Դ����ϵͳ���ڿ����õ���Դ!!!";
			cout << "�����䣡" << endl;
			ch = 'n';
			break;
		}
	}
	if (ch == 'y')
	{
		ChangeData(num - 1);
		showdata();
		int ret = Safe();
		if (ret == -1)
		{
			restore(num - 1);
			cout << "�Է�����ް�ȫ���У�ϵͳ������Դ��" << endl;
			showdata();
		}
	}
	else
	{
		showdata();
	}

}

void test1()
{
	Init();
	showdata();
	//Safe();
	Share();   //�����а�ȫ���е����
	InitFinish();
	Share();   //����Request>Need
	InitFinish();
	Share();   //����Request>Available
	InitFinish();
	Share();   //�����Է���ɹ��������Ҳ�����ȫ����
}
int main()
{
	test1();
	return  0;
}



