#include <stdio.h>
#include <iostream>
#include <stdlib.h >
#include <fstream>
#include<iomanip>
 using namespace std;

 #define MAX 65536
 void find_path(int v,int cost[7][7],int dist[7],int path[6],int n)
 {
    int visit[7] = {0};//访问标志数组初始化
    for(int i=0;i<7;i++)//初始化v1与其他点的距离
    {
        dist[i] = cost[0][i];//path数组用于记录路径，记录前面的节点
        if(dist[i] != MAX)
            path[i] = 0;
    }
    visit[0] = 1;
    dist[0] = 0;
    for(int i=1;i<7;++i)
    {
        int u;
        int temp = MAX;
        for(int j=0;j<7;++j)
        {
            if(visit[j]==0 && dist[j]<temp)
            {
                u = j;
                temp = dist[j];
            }
        }
        visit[u] = 1;

    for(int j=0;j<7;++j)    //逐渐加入各个顶点
    {
        if(visit[j] == 0)
        {
            int newdistanation = dist[u]+cost[u][j];
            if(newdistanation < dist[j])     //如果加入新的顶点后，距离变短了，就得设置新的顶点加入路径数组
            {
                dist[j] = newdistanation;
                path[j] = u;
            }
        }
    }
  }
}

void printpath(int path[],int last)
{
    if(last == 0)
      return;
  printpath(path,path[last]);
  printf("V%d",path[last]+1);   //从最后开始递归 输出相应路径
}
int main()
{

    int i,j;
    int num;
    int cost[][7]= {{0,MAX,MAX,MAX,MAX,MAX,MAX},
                    {MAX,0,MAX,MAX,MAX,MAX,MAX},
                    {MAX,MAX,0,MAX,MAX,MAX,MAX},
                    {MAX,MAX,MAX,0,MAX,MAX,MAX},
                    {MAX,MAX,MAX,MAX,0,MAX,MAX},
                    {MAX,MAX,MAX,MAX,MAX,0,MAX},
                    {MAX,MAX,MAX,MAX,MAX,MAX,0},};
    ifstream fp2("graph.txt");//读取文件
	if (!fp2){
		cout << "读取文件失败！！" << endl;
        system("pause");
		exit(1);
	}
	while (fp2){
            fp2 >>i>>j>>num;
            cost[i-1][j-1]=num;
	}
	fp2.close();

    int dist[7];
    int path[7];
    find_path(0,cost,dist,path,7);
    cout<<"路径      "<<"代价"<<endl;
    for(int i=1;i<7;++i)
    {
        printpath(path,i);
        cout<<"V"<<i+1<<"    "<<dist[i]<<endl;
    }
    system("pause");
    return 0;
}
