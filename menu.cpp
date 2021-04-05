#include <iostream>
#include <cstdlib>			//标准库
#include <unistd.h>			//延时函数
#include <stdio.h>			//getchar	
#include <ctime>			
#include <termios.h>		//终端设置

#include "MazeMap.h"
#include "MazeMan.h"

using namespace std;


int main()
{
  //定义并初始化存储地图数据的二维数组
#define MapRow 11    //迷宫地图的行数
#define MapCol 11    //迷宫地图的列数
int map[MapRow][MapCol];	//迷宫
 

//创建迷宫
void createMaze(){
	int maxway = MapRow * MapCol;		//最大通路
	int x,y;

	for(x=0;x<MapRow;x++)
		for(y=0;y<MapCol;y++)
			map[x][y] = 1;			//先填充迷宫
	
	
	
	//最外围层设为路径的原因，为了防止挖路时挖出边界，同时为了保护迷宫主体外的一圈墙体被挖穿
	for (int i = 0; i < MapRow; i++){
		map[i][0] = 1;
		map[0][i] = 1;
		map[i][MapRow - 1] = 1;
		map[MapRow - 1][i] = 1;
	}


	srand((unsigned)time(NULL));	//随机函数种子，以时间为参数
	for(int i=0;i<maxway;i++)		//随机构建迷宫通路, 1-9
	{
		x = rand() % (MapRow-2) + 1;
		y = rand() % (MapCol-2) + 1;
		map[x][y] = 0;
	}	
	

	map[0][1] = 0; 			//入口
	map[11][10] = 0;		//出口

};

	

  //从堆中实例化地图对象
  MazeMap *mm = new MazeMap();
  mm->setMazeMap(&map[0][0],MapRow,MapCol);
  mm->setExitPosition(11,10);
  mm->pintMazeMap();
  //从堆中实例化游戏角色对象
  MazeMan *man = new MazeMan();
  //设置角色起始位置
  man->setPosition(0,1);
  //设置游戏要走的地图
  man->setMap(mm);
  //用new的方式从堆中实例化的对象，使用完毕之后需要手动释放内存
  man->start();
  delete mm;
  mm = NULL;
  delete man;
  man = NULL;
  std::cout << "闯关成功！" << std::endl;
  system("pause");
}
