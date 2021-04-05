//final map is PrintMap()

#ifndef MAZEMAP_H
#define MAZEMAP_H

#include <bits/stdc++.h>

#define m 11  //row
#define n 11  //line
#define down 1
#define right 2
#define left 4
#define up 8
#define WALL -1
#define NOTHING 2

class MazeMap
{
public:
  struct block{
	  int row,column,direction;
	  block(int _row,int _column,int _direction){
		  row = _row;
		  column = _column;
		  direction = _direction;
	    }
    };
  struct point{
	  int x;
	  int y;
  }start,end;
  void init(); //将地图全部置为墙，定义起点终点
  void FindBlock(); //找出与当前位置相邻的墙
  void PrintMap(); 
  
private:
  vector<block> myblock;
  int x_num=1,y_num=1;//矿工位置
  int G[100][100];
};

#endif
