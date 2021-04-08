#include <iostream>
#include <cstdio>
using namespace std;
int p0,q0,p1,q1;//储存起始点和终点的横纵坐标
char a[15][15];//根据数据量自己调整 
int book[15][15];//标记数组来判断有没有到达 
int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//分别储存x,y坐标下一步的可能情况 
int mini=99999;//先给最小路径一个很大的初值     
int n,m;
void dfs(int x,int y,int step){
    if(x==p1&&y==q1){
        if(step<mini)
        mini=step; 
        return ;//函数直接结束
    }
    for(int k=0;k<4;k++){
        int nx=x+next[k][0], ny=y+next[k][1];//枚举下一步可能的横纵坐标
        if(nx<1||nx>n||ny<1||ny>m){//控制不越界 
            continue;
        }
        if(book[nx][ny]==0&&a[nx][ny]=='0'||book[nx][ny]==0&&a[nx][ny]=='G'){
            //cout<<step<<endl;
            book[nx][ny]=1;//标记走过了 
            dfs(nx,ny,step+1);
            book[nx][ny]=0;//注意dfs后返回这一点为没走过。 
        }
    } 
        return ; 
}
int main(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='S'){
                p0=i;q0=j;
            }
            if(a[i][j]=='G'){
                p1=i;q1=j;
            }
        }
    }
    //cout<<p0<<q0<<p1<<q1<<endl;
    //if(a[2][1]=='.')    cout<<"just a test \n";
    book[p0][q0]=1;//标记起始点走过了 
    dfs(p0,q0,0);
    cout<<mini<<endl;
    return 0;
}
