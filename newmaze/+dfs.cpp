#include <iostream>
#include <cstdlib>			//dynamic memory management
#include <unistd.h>			//to use sleep function
#include <stdio.h>			//getchar
#include <ctime>			//used in random number generator
#include <termios.h>		//terminal setting

#define MAX_X 15
#define MAX_Y 15
bool flag = false;
bool slow = false;

using namespace std;

int maze[MAX_X][MAX_Y];		//creat a 2D int array to store mazemap
int book[15][15];//标记数组来判断有没有到达
int pmove = 0;
int mini = 99999;


//Stack to record the route
class stack_of_maze{
private:
	//record maze coordinates
	struct node
	{
		int x;
		int y;
		char direction;  	//上一步路径（如何来的
		node* next;
	};
	node* head;
public:
	stack_of_maze(){
		head = NULL;
	}

	~stack_of_maze(){
		node* p = head;
		while(head!=NULL){
			head = head->next;
			delete p;
			p = head;
		}
	}


	//压栈
	void push(int xx,int yy,char ddirection){
		node* new_node = new node;
		if(new_node!=NULL){
			new_node->x = xx;
			new_node->y = yy;
			new_node->direction = ddirection;
			new_node->next = NULL;

			if(head==NULL)
				head = new_node;
			else{
				new_node->next = head;
				head = new_node;
			}
		}
		else
			cout<<"内存分配失败"<<endl;

	}


	//出栈
	node* pop(int& xx,int& yy){
		if(head!=NULL){
			node* p = head;
			head = head->next;
			xx = p->x;
			yy = p->y;
			delete p;
		}
		return head;
	}

	void print(){
		if(head!=NULL){
			node* p = head;
			while(p!=NULL){
				cout<<" "<<p->x<<" "<<p->y<<" "<<p->direction<<endl;
				p = p->next;
			}
		}
		else
			cout<<"栈为空，打印失败"<<endl;
	}
};



//创建迷宫
void createMaze(){
	int maxway = MAX_X * MAX_Y;		//the maximum route values to ensure there will always be a path
	int x,y;

	for(x=0;x<MAX_X;x++)
		for(y=0;y<MAX_Y;y++)
			maze[x][y] = 1;			//first fill maze with walls

	srand((unsigned)time(NULL));	//use time as root
	for(int i=0;i<maxway;i++)		//random make roads in the maze
	{
		x = rand() % (MAX_X-2) + 1; //only fill 1-13 rows
		y = rand() % (MAX_Y-2) + 1; //only fill 1-13 columns
		maze[x][y] = 0;
	}

	maze[0][1] = 0; 				//the entrance
	maze[MAX_X-1][MAX_Y-2] = 0;		//the exit

}

//输出迷宫
void printMaze(){
	int x,y;
	system("clear");				//windows下使用system("cls")
	//cout<<endl;
	for(x=0;x<MAX_X;x++)
	{
		for(y=0;y<MAX_Y;y++)
		{
			if(maze[x][y]==0){cout<<"  ";continue;}		//repsrent roards using space
			if(maze[x][y]==1){cout<<"口";continue;}		//represent walls using ■
			if(maze[x][y]==7){cout<<"¥ ";continue;}		//represent the play using *
		}
		cout<<endl;
	}
	if(slow){
		sleep(1);										//give system reaction time
	}
}



void check(stack_of_maze &s){
	int temp[MAX_X][MAX_Y];

	for(int x=0;x<MAX_X;x++)
		for(int y=0;y<MAX_Y;y++)
			temp[x][y] = maze[x][y];

	int x=0,y=1;					//出发点
	while(1){
		temp[x][y] = 7;

		//向下
		if(temp[x+1][y]==0){
			s.push(x,y,'D');
			x = x + 1;
			temp[x][y] = 7;			//当前位置
			if((x==MAX_X-1)&&(y==MAX_Y-2)){
				flag = true;
				return;
			}
			else
				continue;
		}

		//向右
		if(temp[x][y+1]==0){
			s.push(x,y,'R');
			y = y + 1;
			temp[x][y] = 7;
			if((x==MAX_X-1)&&(y==MAX_Y-2)){
				flag = true;
				return;
			}
			else
				continue;
		}

		//向上
		if(temp[x-1][y]==0){
			s.push(x,y,'U');
			x = x - 1;
			temp[x][y] = 7;
			if((x==MAX_X-1)&&(y==MAX_Y-2)){
				flag = true;
				return;
			}
			else
				continue;
		}

		//向左
		if(temp[x][y-1]==0){
			s.push(x,y,'L');
			y = y - 1;
			temp[x][y] = 7;
			if((x==MAX_X-1)&&(y==MAX_Y-2)){
				flag = true;
				return;
			}
			else
				continue;
		}

		//上下左右不通，则回退
		if(s.pop(x,y)==NULL && temp[x-1][y]!=0 && temp[x][y-1]!=0 && temp[x][y+1]!=0 && temp[x+1][y]!=0){
			temp[0][1] = 7;
			if(temp[1][1]!=1)
				temp[1][1] = 2;
			return;
		}
	}
}

//输入,windows下可以使用#incldue<conio.h>替代此函数
char getch(){
	char ch;
    static struct termios oldt, newt;				//保存原有终端属性和新设置的终端属性
    tcgetattr( STDIN_FILENO, &oldt);				//获得终端原有属性并保存在结构体oldflag

    //设置新的终端属性
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    //取消回显
    system("stty -echo");
    ch = getchar();
    system("stty echo");

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);		//让终端恢复为原有的属性
	return ch;
}

void dfs( int x,int y,int step ){
    int next[4][2]={{0,1}, {1,0}, {0,-1}, {-1,0}};    //Store the next possible step of the x and y coordinates
    if( x == MAX_X-1 && y == MAX_Y-2 ){
        if( step < mini )
        mini = step;
        return ;                                   //Directly end the function
    }
    for( int k = 0; k < 4; k++ ){
        int nx = x + next[k][0], ny = y + next[k][1];      //Enumerates the next possible horizontal and vertical coordinates
        if( nx < 1 || nx > 15 || ny < 1 || ny > 15 ){                //Control does not cross boundaries
            continue;
        }
        if(book[nx][ny] == 0 && maze[nx][ny]== 0 || book[nx][ny]== 0 && maze[nx][ny]== maze[MAX_X-1][MAX_Y-2]){
            //cout<<step<<endl;
            book[nx][ny] = 1;//标记走过了
            dfs(nx, ny, step+1);
            book[nx][ny] = 0;//注意dfs后返回这一点为没走过。
        }
    }
        return ;
}


void move(){
	int x=0,y=1;
	book[0][1] = 1;
        dfs(0,1,0); //start from maze[0][1]
	maze[0][1] = 7;
	while(1){
		switch(getch()){
			case 's':						//type s to move downwards
				if(maze[x+1][y]==0){
					maze[x][y] = 0;
					x = x + 1;
					maze[x][y] = 7;			//print current position
					printMaze();
					pmove += 1;
					cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
					if((x==MAX_X-1)&&(y==MAX_Y-2)){
						cout<<"\n\n              You Escaped!";
					    if (pmove > mini)
					    cout << "\n\n              Fail" << endl;
					    else
					    cout << "\n\n              Success" << endl;
						return;
					}
				}
				break;

			case 'd':					//type d to move rightwards
				if(maze[x][y+1]==0){
					if(maze[x][y+1]==0){
						maze[x][y] = 0;
						y = y + 1;
						maze[x][y] = 7;
						printMaze();
						pmove += 1;
					    cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
						if((x==MAX_X-1)&&(y==MAX_Y-2)){
							cout<<"\n\n            You Escaped!"<<endl;
                            if (pmove > mini)
					        cout << "\n\n              Fail" << endl;
					        else
					        cout << "\n\n              Success" << endl;
							return;
						}
					}
				}
				break;

			case 'w':					//type w to move upwards
				if(maze[x-1][y]==0){
					maze[x][y] = 0;
					x = x - 1;
					maze[x][y] = 7;
					printMaze();
					pmove += 1;
					cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
					if((x==MAX_X-1)&&(y==MAX_Y-2)){
						cout<<"\n\n              You Escaped!"<<endl;
						if (pmove > mini)
					    cout << "\n\n              Fail" << endl;
					    else
					    cout << "\n\n              Success" << endl;
						return;
					}
				}
				break;

			case 'a':					//type a to move leftwards
				if(maze[x][y-1]==0){
					maze[x][y] = 0;
					y = y - 1;
					maze[x][y] = 7;
					printMaze();pmove += 1;
					cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
					if((x==MAX_X-1)&&(y==MAX_Y-2)){
						cout<<"\n\n              You Escaped!"<<endl;
						if (pmove > mini)
					    cout << "\n\n              Fail" << endl;
					    else
					    cout << "\n\n              Success" << endl;
						return;
					}
				}
				break;
		}
	}
}

void menu();

void gamestart(){
	flag = false;
	while(!flag){
		stack_of_maze stack;			//定义一个栈的对象，用来记录行走路线
		createMaze();
		check(stack);
		system("clear");
		cout<<"\t*                loading.              *"<<endl;
		system("clear");
		cout<<"\t*                loading..             *"<<endl;
		system("clear");
		cout<<"\t*                loading...            *"<<endl;
	}

	printMaze();						//输出当前迷宫的初始状态
	cout<<"\n\n		* Press Enter to Start *"<<endl;
	getchar();

	move();
	cout<<"\n\n		* Press Enter to Continue *"<<endl;
	getchar();
	menu();

}

void menu(){
	system("clear");
	int num;
	cout<<"\t****************************************"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t*               1.Play :)              *"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t*               2.Exit :(              *"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t****************************************"<<endl;

	switch(getch()){
		case '1':
			gamestart();
			break;
		case '2':
			exit(1);
			break;
		default:
			cout<<"\n\n		wrong command, try again"<<endl;
			getchar();
			menu();
	}
	getchar();
}

int main(int argc,char** argv){
	menu();
	return 0;
}
