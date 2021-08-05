#include<iostream>
#include<stdio.h>
#include<string.h>
#include <Windows.h>
#include<time.h>
#include <graphics.h>
#include <conio.h>
#include<algorithm>
#include<stdlib.h>
#include <random>
#include <string>
#include <fstream>
#include <ddraw.h>
#include<iomanip>
#include <sapi.h>                                             // 语音头文件
#include <sphelper.h>                                     // 语音识别头文件
#include <thread>                                           //多线程
                                                                        //vs2019自定义控制台代码模板 by mao
                                                                        //作者QQ1296193245
using namespace std;
#pragma warning(disable : 4996)
#pragma comment (lib,"ddraw.lib")
#pragma comment(lib,"sapi.lib")
#pragma comment(lib,"ole32.lib")
#pragma intrinsic(__rdtsc)
unsigned __int64 t1, t2, t3, t4;
double run_time;                                                   //微秒级算法时间计时器
LARGE_INTEGER time_start;	                                //开始时间
LARGE_INTEGER time_over;	                                //结束时间
double dqFreq;		                                               //计时器频率
LARGE_INTEGER f;	                                               //计时器频率
double tt;
long double totaltime;

inline void runstart()
{
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	t1 = __rdtsc();
	QueryPerformanceCounter(&time_start);	       //计时开始
}
inline void runend()
{
	QueryPerformanceCounter(&time_over);	        //计时结束
	run_time = 1000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	t2 = __rdtsc();
	t3 = t2 - t1;
}
void rundisplay()
{
	cout << endl;
	cout << "-------------------------------------------------------" << endl;
	if (t3 < 10000)
	{
		cout << "CPU脉冲数：" << (t3) << endl;
	}
	else if (t3 < 100000000 && t3 >= 10000)
	{
		tt = t3;
		cout << "CPU脉冲数：" << (tt) / 10000 << "万" << endl;
	}
	else if (t3 > 100000000000)
	{
		t4 = t3;
		t4 = t3 / 10000000;
		tt = t4;
		cout << "CPU脉冲数：" << (tt) / 10 << "亿" << endl;
	}
	else
	{
		t4 = t3;
		t4 = t3 / 10000;
		tt = t4;
		cout << "CPU脉冲数：" << (tt) / 10000 << "亿" << endl;
	}
	if (run_time > 10000)
	{
		cout << "算法运行时间：" << run_time / 1000 << "秒" << endl;
	}
	else if (run_time < 1)
	{
		cout << "算法运行时间：" << run_time * 1000 << "微秒" << endl;
	}
	else
	{
		cout << "算法运行时间：" << run_time << "毫秒" << endl;
	}
	totaltime = clock();
	cout << "程序运行时间：" << totaltime / 1000 << "秒" << endl;
	if (run_time > 0.4)
	{
		double frequency = t3 / run_time / 1000;
		cout << "CPU频率：" << frequency << "MHZ" << endl;
	}
	cout << "CPU名字";
	system("wmic cpu get Name");
	cout << "CPU使用率";
	system("wmic cpu get loadpercentage");
	cout << "-------------------------------------------------------" << endl;
}

/*   ****************************************
void FpsTime(const time_t* t0, time_t* t1, const time_t* t2)// 图形界面计算显示FPS和运行时间
{
	if (!t0 || !t1 || !t2)
		return;
	static int FPS = 0;
	static int fps = 0;
	static wstring fpsTime;
	if (*t2 - *t1 == 1)
	{
		FPS = ++fps;
	}
	fpsTime = L"FPS: ";
	fpsTime += to_wstring(FPS);
	fpsTime += L" 运行时间: ";
	fpsTime += to_wstring(*t2 - *t0);
	fpsTime += L"s";
	settextcolor(LIGHTMAGENTA);
	outtextxy(0, 0, fpsTime.c_str());

	if (*t2 - *t1 == 1)
	{
		fps = 0;
		*t1 = time(nullptr);
	}
	else
	{
		fps++;
	}
}
*/    //*************************************
/*bool cmp(const int a, const int b)
{
	return a > b;
}*/
/*    ***************************************
bool ChangeDisSize(int cx, int cy)	                                  // 分辨率设置为 cx × cy，退出程序时自动还原
{
	LPDIRECTDRAW DXW;
	HRESULT ddrval;
	ddrval = DirectDrawCreate(NULL, &DXW, NULL);
	if (DD_OK != DD_OK) return FALSE;	                         // 创建DirectDraw对象失败返回
	ddrval = DXW->SetCooperativeLevel(NULL, DDSCL_NORMAL);
	if (DD_OK != DD_OK) return FALSE;	                         // 取得窗口模式失败返回
	ddrval = DXW->SetDisplayMode(cx, cy, 16);
	if (DD_OK != DD_OK) return FALSE;	                          // 设置显示模式失败返回
}
*/
//**************************************************************//************************非主函数

//typedef enum { false = 0, true = 1 }bool;
#define MAXSIZE 50
// 字符栈
typedef struct
{
	char data[MAXSIZE];
	int top;
}Stack;

void InitStack(Stack** s)
{
	*s = (Stack*)malloc(sizeof(Stack));
	(*s)->top = -1;
}

bool Push(Stack* s, char e)
{
	if (s->top == MAXSIZE - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(Stack** s, char* e)
{
	if ((*s)->top == -1)
		return false;
	*e = (*s)->data[(*s)->top];
	(*s)->top--;
	return true;
}

bool GetTop(Stack** s, char* e)
{
	if ((*s)->top == -1)
		return false;
	*e = (*s)->data[(*s)->top];
	return true;
}

bool StackEmpty(Stack** s)
{
	if ((*s)->top == -1)
		return true;
	return false;
}

// 将中缀表达式转换成后缀表达式
void trans(char* exp, char postexp[])
{
	int i = 0;
	char e;
	Stack* Optr;
	InitStack(&Optr); //初始化操作符栈，为存储后缀表达式做准备

	while (*exp != '\0') // 对每个字符进行判断处理
	{
		switch (*exp)
		{
			//单独处理括号
			//如果是左括号，直接入栈
		case '(':
			Push(Optr, '(');
			exp++;
			break;
			//如果为右括号，一直出栈操作，直到将 ( 也出栈
		case ')':
			Pop(&Optr, &e);
			while (e != '(')
			{
				postexp[i++] = e;
				Pop(&Optr, &e);
			}
			exp++;
			break;
			// + - 优先级相同，当做同一种情况处理
		case '+':
		case '-':
			//由于 + - 的优先级只比 ( 大，所有只要栈顶字符不为 ( 就一直出栈；反之，则将 + - 入栈。
			while (!StackEmpty(&Optr))
			{
				GetTop(&Optr, &e);
				if (e == '(')
					break;
				else
				{
					postexp[i++] = e;
					Pop(&Optr, &e);
				}
			}
			//最后将 + - 入栈
			Push(Optr, *exp);
			exp++;
			break;
		case '*':
		case '/':
			// * / 优先级比 * / ^ ! 小，所有如果栈顶运算符是它们，就出栈；反之就将 * / 入栈
			while (!StackEmpty(&Optr))
			{
				GetTop(&Optr, &e);
				if (e == '/' || e == '*' || e == '^' || e == '!') // * / 的优先级仅仅低于它前面的 * /，高于前面的 + -，所以要将前面的 * / 弹出栈；+ - 保留，因为新的 * / 会放在栈低，优先级高。
				{
					postexp[i++] = e;
					Pop(&Optr, &e);
				}
				else
					break; // 其他情况（ + - 左括号 ）退出，
			}
			//最后将 / * 入栈
			Push(Optr, *exp);
			exp++;
			break;
		case '^':
			// ^ 优先级仅比 ^ ! 小，如果栈顶运算符是它们，则出栈；反之将 ^ 入栈
			while (!StackEmpty(&Optr))
			{
				GetTop(&Optr, &e);
				if (e == '^' || e == '!')
				{
					postexp[i++] = e;
					Pop(&Optr, &e);
				}
				else
					break; // 其他情况（ + - * / ( ）退出，
			}
			Push(Optr, *exp); //最后将 ^ 入栈
			exp++;
			break;
		case '!':
			// ! 优先级仅比 ! 小，所有如果栈顶运算符为 !,则将其出栈；反之，将 ! 入栈
			while (!StackEmpty(&Optr))
			{
				GetTop(&Optr, &e);
				if (e == '!')
				{
					postexp[i++] = e;
					Pop(&Optr, &e);
				}
				else
					break; // 其他情况（ + - * / ^ ( ）退出，
			}
			//最后将 ! 入栈
			Push(Optr, *exp);
			exp++;
			break;
		default:
			while (*exp >= '0' && *exp <= '9') //循环判断是否为数字字符，如果是则保存到postexp，循环判断是因为可能是多位数字
			{
				postexp[i++] = *exp;
				exp++;
			}
			//以#分隔各个数字字符
			postexp[i++] = '#';
		}
	}
	while (!StackEmpty(&Optr)) //扫描完exp后，操作符栈可能还有操作符，将其存到postexp
	{
		Pop(&Optr, &e);
		postexp[i++] = e;
	}
	postexp[i] = '\0'; //结束字符串
	free(Optr); //销毁栈
}

//将字符形式的后缀表达式，转换成数字形式的表达式并进行计算
typedef struct
{
	double data[MAXSIZE];
	int top;
}Stack_num;

void InitStack_num(Stack_num** s)
{
	*s = (Stack_num*)malloc(sizeof(Stack_num));
	(*s)->top = -1;
}

bool Push_num(Stack_num** s, double e)
{
	if ((*s)->top == MAXSIZE - 1)
		return false;
	(*s)->top++;
	(*s)->data[(*s)->top] = e;
	return true;
}

bool Pop_num(Stack_num** s, double* e)
{
	if ((*s)->top == -1)
		return false;
	*e = (*s)->data[(*s)->top];
	(*s)->top--;
	return true;
}

//计算后缀表达式的值
double compvalue(char* postexp)
{
	Stack_num* num;
	int i = 1;
	double result;
	double a, b;
	double c;
	double d;
	InitStack_num(&num);
	while (*postexp != '\0')
	{
		switch (*postexp)
		{
		case '+':
			Pop_num(&num, &a);
			Pop_num(&num, &b);
			//计算 b+a 的值
			c = b + a;
			Push_num(&num, c);
			break;
		case '-':
			//计算 b-a 的值
			Pop_num(&num, &a);
			Pop_num(&num, &b);
			c = b - a;
			Push_num(&num, c);
			break;
		case '*':
			Pop_num(&num, &a);
			Pop_num(&num, &b);
			//计算 b*a 的值
			c = b * a;
			Push_num(&num, c);
			break;
		case '/':
			Pop_num(&num, &a); // a是除数
			Pop_num(&num, &b);
			//计算 b/a 的值
			if (a != 0)
			{
				c = b / a;
				Push_num(&num, c);
			}
			else
			{
				printf("除0错误！\n");
				exit(0);
			}
			break;
		case '^':
			Pop_num(&num, &a); // a是指数
			Pop_num(&num, &b);
			//计算 b^a 的值
			if (a != 0)
			{
				i = 1;
				c = 1;
				while (i <= a) {
					c = c * b;
					i++;
				}
			}
			else if (b != 0)
			{
				c = 1;
			}
			else {
				c = 0;
			}
			Push_num(&num, c);
			break;
		case '!':
			Pop_num(&num, &a);
			//计算 a! 的值
			c = 1;
			i = a;
			while (i != 0) {
				c = c * i;
				i--;
			}
			Push_num(&num, c);
			break;
		default:
			//如果不是运算符，就只能是字符形式的数字，将其转换成对应的整数
			d = 0;
			while (*postexp >= '0' && *postexp <= '9')
			{
				d = 10 * d + (*postexp - '0');
				postexp++;
			}
			Push_num(&num, d);
		}
		postexp++; //继续下一个字符
	}
	Pop_num(&num, &result);
	return result;
}
//检查用户输入的表达式的正误
bool test(char* exp)
{
	int i = 0;
	Stack* s;
	char e;
	//判断是否包含非法字符
	for (; exp[i] != '\0'; i++)
	{
		if (!((exp[i] >= '0' && exp[i] <= '9') || exp[i] == '!' || exp[i] == '^' || exp[i] == '+' || exp[i] == '-' || \
			exp[i] == '*' || exp[i] == '/' || exp[i] == '(' || exp[i] == ')'))

			return false;
	}
	//如果表达式中包含括号，验证括号的完整性
	InitStack(&s);
	for (i = 0; exp[i] != '\0'; i++)
	{
		switch (exp[i])
		{
		case '(':
			Push(s, exp[i]);
			break;
		case ')':
			if (Pop(&s, &e))
			{
				if (exp[i] == ')' && e == '(')
					return true;
				else
					return false;
			}
			else
				return false;
			break;
		}
	}
	//栈为空表示括号匹配成功
	if (s->top != -1)
		return false;
	else
		return true;
	return true;
}

//**************************************************************//************************

int main()
{
	/*   *************************************
	constexpr int MIN = 1;                            //随机数
	constexpr int MAX = 100;
	constexpr int numm = 10;
	 random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> distr(MIN, MAX);

	for (int n = 0; n < numm; ++n)
	{
		cout << distr(eng) << ",";
	}
	*/   //***********************************
	/*  //************************************
	SYSTEMTIME sys;                                    //获取系统时间
	GetLocalTime(&sys);
	cout << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay << "      ";
	cout<< setfill('0') << setw(2) << sys.wHour << ":" << setfill('0') << setw(2) << sys.wMinute << ":" << setfill('0') << setw(2) << sys.wSecond << endl;
	*/   //***********************************
	/*   *************************************                                             //全屏图形窗口模板
	int rw, rh;
	rw = GetSystemMetrics(SM_CXSCREEN);                                          // 屏幕宽度 像素
	rh = GetSystemMetrics(SM_CYSCREEN);                                          // 屏幕高度 像素
	HWND hwnd = initgraph(rw, rh);                                                    // 初始化绘图窗口并获取窗口句柄
	setbkcolor(GREEN);
	cleardevice();
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);               // 获取窗口信息
																										 // 设置窗口信息 最大化 取消标题栏及边框
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);           // 修改窗口样式
	SetWindowPos(hwnd, HWND_TOP, 0, 0, rw, rh, 0);
	*/   //***********************************
	/*      ***********************************
	initgraph(1600, 900);
	setbkcolor(WHITE);
	cleardevice();
	*/  //***********************************
	/*    ***********************************                                             //后台方式运行，Unicode字符集改成多字节字符集
	HWND hwnd; if (hwnd = ::FindWindow("ConsoleWindowClass", NULL)) //找到控制台句柄
	{
		::ShowWindow(hwnd, SW_HIDE); //隐藏控制台窗口
	}
                                                                                                    //unicode字符集下：
	const char* sss = "ConsoleWindowClass";
	WCHAR wszName[200];
	memset(wszName, 0, sizeof(wszName));
	MultiByteToWideChar(CP_ACP, 0, sss, strlen(sss) + 1, wszName,
		sizeof(wszName) / sizeof(wszName[0]));
	HWND hwnd; if (hwnd = ::FindWindow(wszName, NULL)) //找到控制台句柄
	{
		::ShowWindow(hwnd, SW_HIDE); //隐藏控制台窗口
	}
	*/  //**********************************

	//*************************************************************************



	//*************************************************************************
	runstart();
	//*************************计时开始***************************************

	//存储用户输入的中缀表达式
	char exp[MAXSIZE];
	//用于存储转换后的后缀表达式
	char postexp[MAXSIZE];
	while (true)
	{
		printf("输入表达式：");
		scanf("%s", exp);
		if (!test(exp))
		{
			printf("存在非法字符或者括号不匹配！\n");
			continue;
		}
		trans(exp, postexp);
		printf("后缀表达式:%s\n", postexp);
		//printf("结果:%lf\n", compvalue(postexp));
		cout << "运算结果为：" << compvalue(postexp) << endl<<endl;
	}

	//*************************计时结束***************************************
	runend();



	/*   ************************************                            //微软TTS语音模板
	ISpVoice* pVoice = NULL;                                            //创建一个ISpVoice的空指针
	if (FAILED(::CoInitialize(NULL)))                                     //初始化COM编程环境
	{
		cout << "初始化COM环境失败！" << endl;
		return 0;
	}
	                                                                                   //获取ISpVoice接口对象：
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (SUCCEEDED(hr))                                                      //如果获取接口对象成功
	{
		char* szStr = (char*)malloc(200);
		sprintf(szStr, "你好，世界。");
		WCHAR wszClassName[200];
		memset(wszClassName, 0, sizeof(wszClassName));
		MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, wszClassName,
			sizeof(wszClassName) / sizeof(wszClassName[0]));
		hr = pVoice->Speak(wszClassName, 0, NULL);         //朗读
		
		pVoice->Release();                                                 //释放分配资源
		pVoice = NULL;                                                     //防止野指针
	}
	::CoUninitialize();                                                       //退出COM编程环境
	*/  //*********************************
	/*   **********************************                          //多线程模板
	void task()
    {
	//多线程代码
    }
	thread t(task);
	t.detach();
	*/   //*******************************
	rundisplay();                                                                   //计时结果显示
	_getch();
	//closegraph();
	// system("pause");
	//Sleep(10000);
	return 0;
}
