#include "mazegame.h"

//Create a stack to record the route of player's move
class stack_of_maze{
private:
	struct node				//a node struct record maze coordinates
	{
		int x;
		int y;
		char direction;  	//record the move direction
		node* next;
	};
	node* head;

public:
	stack_of_maze(){
		head = NULL;
	}

	~stack_of_maze(){		//create a linked-list backward
		node* p = head;
		while ( head!=NULL ){
			head = head->next;
			delete p;
			p = head;
		}
	}

	//Push stack, insert the node operation
	void push(int row_x, int col_y, char ddirection){
		node* new_node = new node;
		if(new_node != NULL){
			new_node->x = row_x;
			new_node->y = col_y;
			new_node->direction = ddirection;
			new_node->next = NULL;

			if(head==NULL){
				head = new_node;
			}else{
				new_node->next = head;
				head = new_node;
			}
		}else{
			cout << "Memory allocation failure" <<endl;
		}
	}


	//Pop stack, remove the node operation
	node* pop(int& row_x,int& col_y){
		if(head!=NULL){
			node* p = head;
			head = head->next;
			row_x = p->x;
			col_y = p->y;
			delete p;
		}
		return head;
	}

	//print the player's position every move
	void print(){
		if( head!=NULL ){
			node* p = head;
			while(p!=NULL){
				cout << " " << p->x << " " << p->y << " " << p->direction <<endl;
				p = p->next;
			}
		}else{
			cout<<"Empaty stack, failure"<<endl;
		}
	}
};


//Create the random maze
void maze_create(){
	int x,y;
	int way = row * column;			//the maximum iteration times to ensure there will always be a path
	
	for( x=0; x<row; x++){
		for( y=0; y<column; y++){
			maze[x][y] = 1;			//first fill maze array all with walls(1)
		}
	}

	srand((unsigned)time(NULL));	//use time as root
	for(int i=0; i<way; i++)		//random make roads in the maze
	{
		x = rand() % (row-2) + 1; 	//only fill 1-13 rows (leave 4 boundaries)
		y = rand() % (row-2) + 1; 	//only fill 1-13 columns
		maze[x][y] = 0;
	}	

	maze[0][1] = 0; 				//set as the fixed entrance
	maze[row-1][column-2] = 0;		//set as the fixed the exit
}


//Create 2D array s as the copy of maze
void copy_maze(){
	int i, j;
	for( i=0; i<row; i++){
		for( j=0; j<column; j++){
			mazecopy[i][j] = maze[i][j];
		}
	}	
}


//Print the maze to gameboard
void printMaze(){
	int x,y;
	system("clear");		//to clear the output screen				
	for( x=0; x<row; x++)
	{
		for( y=0; y<column; y++)
		{
			if(maze[x][y]==0){cout<<"  ";continue;}		//repsrent roards using space
			if(maze[x][y]==1){cout<<"口";continue;}		//represent walls using 口
			if(maze[x][y]==2){cout<<"¥ ";continue;}		//represent the play using ¥
		}
		cout<<endl;
	}
	if(slow){
		sleep(1);										//give system reaction time
	}
}


//Check there will always be a shortest path of the maze
void check(stack_of_maze &s){
	int map[row][column];			//create a copy of maze named 'map'
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			map[i][j] = maze[i][j];
		}
	}

	int x=0, y=1;					//the entrance point	
	while(1){
		map[x][y] = 2;				//player start from here

		//Check from downwards
		if(map[x+1][y]==0){
			s.push(x,y,'D');
			x = x + 1;
			map[x][y] = 2;			//new postion
			if( (x==row-1)&&(y==column-2) ){
				flag = true;		//arrive at the exit, successful maze
				return;
			}else{
				continue;
			}
		}

		//Check from rightwards
		if(map[x][y+1]==0){
			s.push(x,y,'R');
			y = y + 1;
			map[x][y] = 2;
			if( (x==row-1)&&(y==column-2) ){
				flag = true;
				return;
			}else{
				continue;
			}
		}

		//Check from upwards
		if(map[x-1][y]==0){
			s.push(x,y,'U');
			x = x - 1;
			map[x][y] = 2;
			if( (x==row-1)&&(y==column-2) ){
				flag = true;
				return;
			}else{
				continue;
			}
		}

		//Check from leftwards
		if(map[x][y-1]==0){
			s.push(x,y,'L');
			y = y - 1;
			map[x][y] = 2;
			if( (x==row-1)&&(y==column-2) ){
				flag = true;
				return;
			}else{
				continue;
			}
		}

		//Go to the last move if can't move further
		if( s.pop(x,y)==NULL && map[x-1][y]!=0 && map[x][y-1]!=0 && map[x][y+1]!=0 && map[x+1][y]!=0){
			map[0][1] = 2;
			if(map[1][1]!=1)
				map[1][1] = 2;
			return;
		}
	}
}


//Get a char command from users and terminal setting
char getch(){
	char user_command;   
    static struct termios old_terminal, new_terminal;		//Save the old terminal properties and the newly set terminal properties
    tcgetattr( STDIN_FILENO, &old_terminal);				//Get the terminal's original attributes and save in the structure oldflag

    new_terminal = old_terminal;							//Set the new terminal properties
    new_terminal.c_lflag &= ~(ICANON);          
    tcsetattr( STDIN_FILENO, TCSANOW, &new_terminal);		//set the parameters associated with the terminal

    system("stty -echo");									//Cancle the echo
    user_command = getchar();
    system("stty echo");    

    tcsetattr( STDIN_FILENO, TCSANOW, &old_terminal);		//restore original property of the terminal
	return user_command;
}

//Search the shortest path of the maze using dfs
void dfs(int x,int y,int step, int &pmove){
    int i, x2, y2;
    if(x == 14 && y == 13)			//if arrives at the exit, end the search
    {								
		if (pmove > step){			//compare actual move with optimal move steps
			cout << "\n\n              You also failed:( Can you find a shorter path?" << endl;
		}else{
			cout << "\n\n              You found the shortest path (^o^)" << endl;
		}
		return;
    }

	//if does not arrive at the exit, go to the next recursion
    for(i=0; i<4; i++)				//loop 4 times for 4 directions
    {
        x2 = x+dir[i][0];			//new varibles to x and y (x2 and y2)	
        y2 = y+dir[i][1];			//do not change original position
        if(x2<0||x2>=15||y2<0||y2>=15)	
        {							// do not exceed the boundaries
            continue;				
        }

        if(mazecopy[x2][y2]==0)			//if path, then walk
        {
            mazecopy[x2][y2]=1;			//after walk, mark the last position as wall to avoid repetition
            dfs(x2,y2,step+1, pmove);	
        }							//go to next recursion
    }
    return;
}


//Read player's command to move and print out dynamic maze
void move(){
	int x=0,y=1;							//start from entrance
	maze[0][1] = 2;
	printMaze();

	while(1){
		switch(getch()){
			case 's':						//type s to move downwards
				if(maze[x+1][y]==0){
					maze[x][y] = 0;
					x = x + 1;
					maze[x][y] = 2;			//print current position
					printMaze();
					pmove += 1;				//add 1 to pmove count
					cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
					if((x==row-1)&&(y==column-2)){
						cout<<"\n\n              You Escaped!"<<endl;
						return;
					}
				}				
				break;

			case 'd':						//type d to move rightwards
				if(maze[x][y+1]==0){
					if(maze[x][y+1]==0){
						maze[x][y] = 0;
						y = y + 1;
						maze[x][y] = 2;
						printMaze();
						pmove += 1;
					cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
						if((x==row-1)&&(y==column-2)){
							cout<<"\n\n            You Escaped!"<<endl;
							return;
						}
					}		
				}
				break;

			case 'w':						//type w to move upwards
				if(maze[x-1][y]==0){
					maze[x][y] = 0;
					x = x - 1;
					maze[x][y] = 2;
					printMaze();
					pmove += 1;
					cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
					if((x==row-1)&&(y==column-2)){
						cout<<"\n\n              You Escaped!"<<endl;
						return;
					}
				}	
				break;

			case 'a':						//type a to move leftwards
				if(maze[x][y-1]==0){
					maze[x][y] = 0;
					y = y - 1;
					maze[x][y] = 2;
					printMaze();
					pmove += 1;
					cout<<"\n\n              You have moved "<< pmove << " steps." << endl;
					if((x==row-1)&&(y==column-2)){
						cout<<"\n\n              You Escaped!"<<endl;
						return;
					}
				}		
				break;
		}
	}
}

//Declare menu first, initialize later
void menu();


//Game start to call all functions above
void start_game(){
	flag = false;	
	while(!flag){						//while there's a successful path
		stack_of_maze stack;			//declare a stack to record the move route
		maze_create();
		check(stack);
		system("clear");
		cout<<"\t*                loading.              *"<<endl;
	}

	printMaze();						//print initial maze map
	cout<<"\n\n		* Press Enter to Start *"<<endl;
	getchar();							//get next command

	copy_maze();						//copy the maze map for dfs use
	
	move();								//player moves
	
	dfs(0,1,0, pmove); 					//dfs path search, start from maze[0][1]

	cout<<"\n\n		* Press Enter to Continue *"<<endl;

	pmove =0;				//reset player's move equals to 0
	getchar();
	menu();
	
}

//initialize menu function
void menu(){
	system("clear");
	cout<<"\t****************************************"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t*               1.Play :)              *"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t*               2.Exit :(              *"<<endl;
	cout<<"\t*                                      *"<<endl;
	cout<<"\t****************************************"<<endl;

	switch(getch()){
		case '1':
			start_game();
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


//body function to start
int main(int argc,char** argv){
	menu();
	return 0;
}
