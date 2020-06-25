#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 20//最大顶点数目
#define INFINITY 65535//无穷大的数 
typedef enum {DN,UDN} GraphKind;//图类型标志:有向网,无向网
typedef struct {
	int data;
} VertexNode; //图中顶点结构定义
typedef struct {
	int Value;//权值
} ArcCell,AdjMatrix[MAX_NUM][MAX_NUM]; //边或弧结构的定义
typedef struct {
	VertexNode Vertex[MAX_NUM];//存储顶点数组
	AdjMatrix arcs;//存储顶点之间的关系，即边或弧(邻接矩阵)
	int Vexnum,Arcnum;//当前途中顶点数目、边或弧数目
	GraphKind kind;//图的类型
} MGraph; //图结构的定义
int Locate(MGraph G,VertexNode v) {//返回顶点v在图G中的下标 ,不存在则返回-1
	int i;
	for(i=0; i<G.Vexnum; i++)
		if(G.Vertex[i].data==v.data)
			return i;
	printf("错误！图中不存在顶点%d！",v.data);
	return -1;
}
void CreatGraph(MGraph &G) {//构造网结构，采用邻接矩阵存储
	int i,j,isign,jsign;
	VertexNode v1,v2;
	ArcCell arc;
	while(1) {
		printf("输入图中顶点数目和弧的数目：");
		fflush(stdin);//清空键盘缓冲区
		scanf("%d%d",&G.Vexnum,&G.Arcnum);
		if(G.Vexnum<=0||G.Vexnum>MAX_NUM||G.Arcnum<=0||G.Arcnum>G.Vexnum*(G.Vexnum-1))
			printf("顶点数或弧数输入错误！请重新输入\n");
		else  break;
	}
	printf("输入这%d个顶点：",G.Vexnum);//初始化顶点
	fflush(stdin);//清空键盘缓冲区
	for(i=0; i<G.Vexnum; i++)
		scanf("%d",&G.Vertex[i].data);
	for(i=0; i<G.Vexnum; i++)
		for(j=0; j<G.Vexnum; j++)
			G.arcs[i][j].Value=INFINITY;//先初始化邻接矩阵
	printf("初始化顶点之间的联系(%d条弧):(格式：顶点1 顶点2 权值)\n",G.Arcnum);
	for(i=0; i<G.Arcnum; i++) {//初始化弧
		printf("输入第%2d条弧:",i+1);
		fflush(stdin);//清空键盘缓冲区
		scanf("%d%d%d",&v1.data,&v2.data,&arc.Value);
		isign=Locate(G,v1);
		jsign=Locate(G,v2);
		if(isign==-1||jsign==-1) {
			printf("请重新输入这条弧的信息\n");
			i--;
			continue;
		}
		G.arcs[isign][jsign].Value=arc.Value;//初始化邻接矩阵中该位置弧权值的信息
		if(G.kind==UDN)//无向网
			G.arcs[jsign][isign].Value=arc.Value;
	}
	printf("网的邻接矩阵存储构建完成！\n");
}
typedef int Path[MAX_NUM][MAX_NUM];//存放路径
typedef int Dist[MAX_NUM];//存放最短路径长度
//最短路径_迪杰斯特拉算法：以图G中顶点v0为源点求源点到其他顶点的最短路径
//路径存放在二维数组P中,P[i][j]表示源点v0到顶点G.Vertex[i]的最短路径上的前驱顶点为G.Vertex[j]
//源点到各顶点最短路径长度存放在一维数组D中
void ShortPath_Dijkstra(MGraph G,int v0,Path &P,Dist &D) {
	int i,j,w=-1,k,n,Final[MAX_NUM],min;
	for(i=0; i<G.Vexnum; i++) {//初始化数组P[][],D[],Final[]
		Final[i]=0;
		D[i]=G.arcs[v0][i].Value;
		for(j=0; j<G.Vexnum; j++)
			P[i][j]=D[i]<INFINITY?v0:-1;
	}
	D[v0]=0;
	Final[v0]=1;
	for(i=1; i<G.Vexnum; i++) {	//其余G.Vexnum-1个顶点的最短路径
		min=INFINITY;
		for(j=0; j<G.Vexnum; j++)
			if(min>D[j]&&Final[j]==0) {
				min=D[j];
				w=j;
			}
		if(w==-1)
			continue;
		Final[w]=1;//表示源点到该顶点的最短路径已经找到
		for(k=0; k<G.Vexnum; k++)//更新当前最短路径及距离
			if(Final[k]==0&&D[k]>(min+G.arcs[w][k].Value)) {
				D[k]=min+G.arcs[w][k].Value;
				for(n=0; n<G.Vexnum; n++)
					P[k][n]=P[w][n];
				P[k][k]=w;//存储最短路径前驱顶点下标
			}
	}
}
//打印最短路径：给定图G和源点下标v0,
//根据数组P打印出源点到其余各顶点的最短路径，根据数组D打印出各路径的最短路径长度
void PrintPath(MGraph G,int v0,Path P,Dist D) {
	int i,j,k;
	int V=G.Vertex[v0].data;
	char r[MAX_NUM*2],s[MAX_NUM],t[2];
	printf("_________________________________________________\n");
	printf("源点\t终点\t最短路径\t\t路径长度\n");
	printf("_________________________________________________\n%d",V);
	for(i=0; i<G.Vexnum; i++) {
		if(i==v0)
			continue;
		if(D[i]==INFINITY) { //不可达
			printf("\t%d\t无\n",G.Vertex[i].data);
			continue;
		}
		strcpy(s,"");
		strcpy(r,"");
		for(j=i; j!=v0; j=P[i][j]) //查找路径P，并将路径顶点连接到字符串s中
			strcat(s,itoa(G.Vertex[j].data, t, 10));
		strcat(s,itoa(V, t, 10));
		for(j=strlen(s)-1; j>=0; j--) {//将字符串s逆序复制到字符串r中
			sprintf(t,"%c",s[j]);
			strcat(r,t);
			if(j!=0)	strcat(r,"->");
		}
		printf("\t%d\t%-15s\t\t%-5d\n",G.Vertex[i].data,r,D[i]);
	}
	printf("_________________________________________________\n");
}
//主函数
int main() {
	MGraph G;
	int k,index;
	printf("***************************************************\n");
	printf("*************单源点最短路径算法的实现**************\n");
	printf("功能：实现建立任意m个顶点n条边的图算法\n按照用户给定的源点，求出源点到其他顶点间的最短路径\n") ;
	printf("***************************************************\n");
	printf("输入图的类型：【1.有向网/2.无向网】\n");
	while(1) {
		scanf("%d",&k);
		if(k==1) {
			G.kind=DN;
			break;
		}
		if(k==2) {
			G.kind=UDN;
			break;
		}
		printf("输入错误！请重新选择：");
		fflush(stdin);//清空键盘缓冲区
	}
	CreatGraph(G);
	VertexNode V;
	Path P;
	Dist D;
	while(1) {
		printf("输入源点(-1退出)：");
		fflush(stdin);//清空键盘缓冲区
		scanf("%d",&V.data);
		if(V.data==-1)//输入-1结束程序
			break;
		index=Locate(G,V);//查找源点v在图G中的位置
		if(index==-1) { //未找到，即输入的源点不合法
			printf("\n");
			continue;
		}
		ShortPath_Dijkstra(G,index,P,D);
		PrintPath(G,index,P,D);
	}
	return 0;
}
