// C++ program to find the shortest path between
#ifndef DFSPATH_H
#define DFSPATH_H

#include <iostream>
#include <cstdio>

int p0,q0,p1,q1;//储存起始点和终点的横纵坐标
char a[15][15];//根据数据量自己调整 
int book[15][15];//标记数组来判断有没有到达 
int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//分别储存x,y坐标下一步的可能情况 
int mini=99999;//先给最小路径一个很大的初值     
int n,m;
void dfs(int x,int y,int step)


#endif
