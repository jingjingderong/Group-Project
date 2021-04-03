#include <iostream>
#include <cstdlib>			//标准库
#include <unistd.h>			//延时函数
#include <stdio.h>			//getchar	
#include <ctime>			
#include <termios.h>		//终端设置

#define MAX_X 20
#define MAX_Y 30
bool flag = false;
bool slow = false;

using namespace std;

int maze[MAX_X][MAX_Y];		//迷宫

void menu(){
	system("clear");
	int num;
	cout<<"\t****************************************"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t*               1.自行游戏             *"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t*               2.退出游戏             *"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t****************************************"<<endl;
	slow = false;
	switch(getch()){
		case '1':
			gamestart();
			break;
		case '2':
			exit(1);break;
		default:
			cout<<"\n\n              错误操作，输入enter返回！"<<endl;
			getchar();
			menu();
	}
	getchar();
}

//put in another main file
int main(int argc,char** argv){
	menu();
	return 0;
}
