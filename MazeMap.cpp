#include "MazeMap.h"
MazeMap::void init() 
{
	//将地图全部置为墙
	memset(G,WALL,sizeof(G));
	//定义起始点
	G[0][1] = NOTHING;
	G[1][1] = NOTHING;
	G[11][12] = NOTHING;
	G[11][11] = NOTHING;
	G[11][10] = NOTHING;
	start.x = start.y = 1;
}

MazeMap::void FindBlock() 
{
	//找出与当前位置相邻的墙
	if(x_num+1<=m && G[x_num+1][y_num] == WALL) {//down
		myblock.push_back(block(x_num+1,y_num,down));
	}
	if(y_num+1<=n && G[x_num][y_num+1] == WALL) {//right
		myblock.push_back(block(x_num,y_num+1,right));
	}
	if(x_num-1>=1 && G[x_num-1][y_num] == WALL) {//up
		myblock.push_back(block(x_num-1,y_num,up));
	}
	if(y_num-1>=1 && G[x_num][y_num-1] == WALL) {//left
		myblock.push_back(block(x_num,y_num-1,left));
	}
}

MazeMap::void PrintMap() 
{
	init();
	srand((unsigned)time(NULL));//随机数种子
	FindBlock();
	//第一步压入两堵墙（起点右边和起点下面）进入循环
	while(myblock.size()) {
		int BlockSize = myblock.size();
		//随机选择一堵墙（生成0 ~ BlockSize-1之间的随机数，同时也是vector里墙的下标）
		int randnum = rand() % BlockSize;
		block SelectBlock = myblock[randnum];
		x_num = SelectBlock.row;//矿工来到我们“选择的墙”这里
		y_num = SelectBlock.column;
		//根据当前选择的墙的方向进行后续操作
		//此时，起始点 选择的墙 目标块 三块区域在同一直线上
		//我们让矿工从“选择的墙”继续前进到“目标块”
		//矿工有穿墙能力 ：)
		switch(SelectBlock.direction) {
			case down: {
				x_num++;
				break;
			}
			case right: {
				y_num++;
				break;
			}
			case left: {
				y_num--;
				break;
			}
			case up: {
				x_num--;
				break;
			}
		}
		//目标块如果是墙
		if(G[x_num][y_num]==WALL) {
			//打通墙和目标块
			G[SelectBlock.row][SelectBlock.column] = G[x_num][y_num] = NOTHING;
			//再次找出与矿工当前位置相邻的墙
			FindBlock();
		}
		else{//如果不是呢？说明我们的矿工挖到了一个空旷的通路上面 休息一下就好了
			//relax
		}
		//删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
		myblock.erase(myblock.begin()+randnum);
	}
	for (int i=0;i<=m+1;i++) {
		for (int j=0;j<=n+1;j++) {
			/*
			if(i == start.x && j == start.y) {
				printf("%c%c",0xa7,0xb0 );
			} */
			if(G[i][j] == NOTHING) {
				printf("  ");
			} 
			else {
				printf("%c%c", 0xa8, 0x80);
			}
		}
		printf("\n");
}
