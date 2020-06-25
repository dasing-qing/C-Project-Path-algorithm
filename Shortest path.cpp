#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NUM 20//��󶥵���Ŀ
#define INFINITY 65535//�������� 
typedef enum {DN,UDN} GraphKind;//ͼ���ͱ�־:������,������
typedef struct {
	int data;
} VertexNode; //ͼ�ж���ṹ����
typedef struct {
	int Value;//Ȩֵ
} ArcCell,AdjMatrix[MAX_NUM][MAX_NUM]; //�߻򻡽ṹ�Ķ���
typedef struct {
	VertexNode Vertex[MAX_NUM];//�洢��������
	AdjMatrix arcs;//�洢����֮��Ĺ�ϵ�����߻�(�ڽӾ���)
	int Vexnum,Arcnum;//��ǰ;�ж�����Ŀ���߻���Ŀ
	GraphKind kind;//ͼ������
} MGraph; //ͼ�ṹ�Ķ���
int Locate(MGraph G,VertexNode v) {//���ض���v��ͼG�е��±� ,�������򷵻�-1
	int i;
	for(i=0; i<G.Vexnum; i++)
		if(G.Vertex[i].data==v.data)
			return i;
	printf("����ͼ�в����ڶ���%d��",v.data);
	return -1;
}
void CreatGraph(MGraph &G) {//�������ṹ�������ڽӾ���洢
	int i,j,isign,jsign;
	VertexNode v1,v2;
	ArcCell arc;
	while(1) {
		printf("����ͼ�ж�����Ŀ�ͻ�����Ŀ��");
		fflush(stdin);//��ռ��̻�����
		scanf("%d%d",&G.Vexnum,&G.Arcnum);
		if(G.Vexnum<=0||G.Vexnum>MAX_NUM||G.Arcnum<=0||G.Arcnum>G.Vexnum*(G.Vexnum-1))
			printf("���������������������������\n");
		else  break;
	}
	printf("������%d�����㣺",G.Vexnum);//��ʼ������
	fflush(stdin);//��ռ��̻�����
	for(i=0; i<G.Vexnum; i++)
		scanf("%d",&G.Vertex[i].data);
	for(i=0; i<G.Vexnum; i++)
		for(j=0; j<G.Vexnum; j++)
			G.arcs[i][j].Value=INFINITY;//�ȳ�ʼ���ڽӾ���
	printf("��ʼ������֮�����ϵ(%d����):(��ʽ������1 ����2 Ȩֵ)\n",G.Arcnum);
	for(i=0; i<G.Arcnum; i++) {//��ʼ����
		printf("�����%2d����:",i+1);
		fflush(stdin);//��ռ��̻�����
		scanf("%d%d%d",&v1.data,&v2.data,&arc.Value);
		isign=Locate(G,v1);
		jsign=Locate(G,v2);
		if(isign==-1||jsign==-1) {
			printf("��������������������Ϣ\n");
			i--;
			continue;
		}
		G.arcs[isign][jsign].Value=arc.Value;//��ʼ���ڽӾ����и�λ�û�Ȩֵ����Ϣ
		if(G.kind==UDN)//������
			G.arcs[jsign][isign].Value=arc.Value;
	}
	printf("�����ڽӾ���洢������ɣ�\n");
}
typedef int Path[MAX_NUM][MAX_NUM];//���·��
typedef int Dist[MAX_NUM];//������·������
//���·��_�Ͻ�˹�����㷨����ͼG�ж���v0ΪԴ����Դ�㵽������������·��
//·������ڶ�ά����P��,P[i][j]��ʾԴ��v0������G.Vertex[i]�����·���ϵ�ǰ������ΪG.Vertex[j]
//Դ�㵽���������·�����ȴ����һά����D��
void ShortPath_Dijkstra(MGraph G,int v0,Path &P,Dist &D) {
	int i,j,w=-1,k,n,Final[MAX_NUM],min;
	for(i=0; i<G.Vexnum; i++) {//��ʼ������P[][],D[],Final[]
		Final[i]=0;
		D[i]=G.arcs[v0][i].Value;
		for(j=0; j<G.Vexnum; j++)
			P[i][j]=D[i]<INFINITY?v0:-1;
	}
	D[v0]=0;
	Final[v0]=1;
	for(i=1; i<G.Vexnum; i++) {	//����G.Vexnum-1����������·��
		min=INFINITY;
		for(j=0; j<G.Vexnum; j++)
			if(min>D[j]&&Final[j]==0) {
				min=D[j];
				w=j;
			}
		if(w==-1)
			continue;
		Final[w]=1;//��ʾԴ�㵽�ö�������·���Ѿ��ҵ�
		for(k=0; k<G.Vexnum; k++)//���µ�ǰ���·��������
			if(Final[k]==0&&D[k]>(min+G.arcs[w][k].Value)) {
				D[k]=min+G.arcs[w][k].Value;
				for(n=0; n<G.Vexnum; n++)
					P[k][n]=P[w][n];
				P[k][k]=w;//�洢���·��ǰ�������±�
			}
	}
}
//��ӡ���·��������ͼG��Դ���±�v0,
//��������P��ӡ��Դ�㵽�������������·������������D��ӡ����·�������·������
void PrintPath(MGraph G,int v0,Path P,Dist D) {
	int i,j,k;
	int V=G.Vertex[v0].data;
	char r[MAX_NUM*2],s[MAX_NUM],t[2];
	printf("_________________________________________________\n");
	printf("Դ��\t�յ�\t���·��\t\t·������\n");
	printf("_________________________________________________\n%d",V);
	for(i=0; i<G.Vexnum; i++) {
		if(i==v0)
			continue;
		if(D[i]==INFINITY) { //���ɴ�
			printf("\t%d\t��\n",G.Vertex[i].data);
			continue;
		}
		strcpy(s,"");
		strcpy(r,"");
		for(j=i; j!=v0; j=P[i][j]) //����·��P������·���������ӵ��ַ���s��
			strcat(s,itoa(G.Vertex[j].data, t, 10));
		strcat(s,itoa(V, t, 10));
		for(j=strlen(s)-1; j>=0; j--) {//���ַ���s�����Ƶ��ַ���r��
			sprintf(t,"%c",s[j]);
			strcat(r,t);
			if(j!=0)	strcat(r,"->");
		}
		printf("\t%d\t%-15s\t\t%-5d\n",G.Vertex[i].data,r,D[i]);
	}
	printf("_________________________________________________\n");
}
//������
int main() {
	MGraph G;
	int k,index;
	printf("***************************************************\n");
	printf("*************��Դ�����·���㷨��ʵ��**************\n");
	printf("���ܣ�ʵ�ֽ�������m������n���ߵ�ͼ�㷨\n�����û�������Դ�㣬���Դ�㵽�������������·��\n") ;
	printf("***************************************************\n");
	printf("����ͼ�����ͣ���1.������/2.��������\n");
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
		printf("�������������ѡ��");
		fflush(stdin);//��ռ��̻�����
	}
	CreatGraph(G);
	VertexNode V;
	Path P;
	Dist D;
	while(1) {
		printf("����Դ��(-1�˳�)��");
		fflush(stdin);//��ռ��̻�����
		scanf("%d",&V.data);
		if(V.data==-1)//����-1��������
			break;
		index=Locate(G,V);//����Դ��v��ͼG�е�λ��
		if(index==-1) { //δ�ҵ����������Դ�㲻�Ϸ�
			printf("\n");
			continue;
		}
		ShortPath_Dijkstra(G,index,P,D);
		PrintPath(G,index,P,D);
	}
	return 0;
}
