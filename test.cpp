#include <iostream>
#include <string>
#define False 0
#define True 1
using namespace std;

int Max[100][100] = { 0 };//各进程所需各类资源的最大需求
int Available[100] = { 0 };//系统可用资源
int Allocation[100][100] = { 0 };//系统已分配资源
int Need[100][100] = { 0 };//还需要资源
string Name[20] = { "0" };//资源的名称
string workName[20] = { "0" };//进程的名字
int Request[100] = { 0 };//请求资源向量
string Temp[20] = { "0" };//存放安全序列
int Work[100] = { 0 };//存放系统可提供的资源
int M;//进程的数目
int N;//资源的种类数
int Sum[100];//存放资源的数量
int Finish[100] = { 0 };//表示系统是否有足够的资源分配给进程
void Init()
{
	string name;
	int num;
	cout << "请输入系统提供资源种类的数量：";
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cout << "资源" << i + 1 << "的名称：";
		cin >> name;
		Name[i] = name;
		cout << "资源的数量为：";
		cin >> num;

		Sum[i] = num;
	}
	cout << endl;
	cout << "请输入进程的数量：";
	cin >> M;
	cout << endl;
	cout << "请输入各进程的名字(空格隔开)：" << endl;
	for (int i = 0; i < M; i++)
	{
		string name;
		cin >> name;
		workName[i] = name;
	}
	cout << "请输入各进程的最大需求量" << M << "*" << N << "矩阵Max" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Max[i][j];
		}
	}
	//以上实现了所有作业的Max矩阵的初始化
	cout << "请输入各进程已经申请的资源量：" << M << "*" << N << "矩阵Allocation" << endl;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Allocation[i][j];
			if (Allocation[i][j]>Max[i][j])
			{
				cout << "输入错误，请重新输入：" << endl;
				cin >> Allocation[i][j];
			}
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
	//以上完成Allocation和Need的初始化
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
//以上计算出Available的值
void showdata()   //打印出资源表
{
	cout << "	  Max         Allocation       Need " << endl;
	cout << "进程名" << "  ";
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
	cout << "Available的值为：" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << Available[i] << ",";
	}
	cout << endl;
}
void restore(int i)//系统资源回收
{
	for (int j = 0; j < N; j++)
	{
		Available[j] = Available[j] + Request[j];
		Allocation[i][j] = Allocation[i][j] - Request[j];
		Need[i][j] = Need[i][j] + Request[j];
	}
}
void ChangeData(int i)//进行资源分配，修改值
{
	for (int j = 0; j < N; j++)
	{
		Available[j] = Available[j] - Request[j];
		Allocation[i][j] = Allocation[i][j] + Request[j];
		Need[i][j] = Need[i][j] - Request[j];
	}
}
int Safe()//安全算法
{
	int m = 0;
	for (int i = 0; i < N; i++)
	{
		Work[i] = Available[i];
	}
	for (int i = 0; i < M; i++)//找满足条件的进程
	{
		int count = 0;//设置计数，即三个资源的Need都要小于work
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
					Temp[m] = workName[i];//存储安全序列
					m++;
					if (sizeof(Temp) / sizeof(Temp[0]) != M)//不进行判断会多遍历M次
					{
						i = -1;//每次从头开始循环查找
					}
				}
			}
		}
	}
	for (int i = 0; i < M; i++)
	{
		if (Finish[i] == False)
		{
			cout << "没有安全序列！" << endl;
			return -1;
			break;
		}
	}
	cout << "系统是安全的!" << endl;
	cout << "安全序列为：";
	for (int i = 0; i < M; i++)
	{
		cout << Temp[i] << " ";
	}
	cout << endl;
	return 1;
}
void InitFinish()  //每次调用银行家算法后都要把Finish初始化成False
{
	for (int i = 0; i < M; i++)
	{
		Finish[i] = False;
	}
}
void Share()//利用银行家算法对申请资源进行判定
{
	int num;
	char ch = 'y';
	cout << "请输入要求分配资源的进程序号：";
	cin >> num;
	cout << "请输入作业" << workName[num - 1] << "申请的资源:" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << Name[i] << ":";
		cin >> Request[i];
	}
	for (int j = 0; j < N; j++)
	{
		if (Request[j]>Need[num - 1][j])
		{
			cout << "进程" << workName[num - 1] << "申请的资源大于它需要的资源!!!";
			cout << "不分配！" << endl;
			ch = 'n';
			break;
		}

		if (Request[j] > Available[j])
		{
			cout << "进程" << workName[num - 1] << "申请的资源大于系统现在可利用的资源!!!";
			cout << "不分配！" << endl;
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
			cout << "试分配后无安全序列，系统回收资源：" << endl;
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
	Share();   //测试有安全序列的情况
	InitFinish();
	Share();   //测试Request>Need
	InitFinish();
	Share();   //测试Request>Available
	InitFinish();
	Share();   //测试试分配成功，但是找不到安全序列
}
int main()
{
	test1();
	return  0;
}



