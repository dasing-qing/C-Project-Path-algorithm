#define MAX_NUM 20//��󶥵���Ŀ
#define INFINITY 65535//�������� 
typedef enum { DN, UDN } GraphKind;//ͼ���ͱ�־:������,������
typedef struct {
	int data;
} VertexNode; //ͼ�ж���ṹ����
typedef struct {
	int Value;//Ȩֵ
} ArcCell, AdjMatrix[MAX_NUM][MAX_NUM]; //�߻򻡽ṹ�Ķ���
typedef struct {
	VertexNode Vertex[MAX_NUM];//�洢��������
	AdjMatrix arcs;//�洢����֮��Ĺ�ϵ�����߻�(�ڽӾ���)
	int Vexnum, Arcnum;//��ǰ;�ж�����Ŀ���߻���Ŀ
	GraphKind kind;//ͼ������
} MGraph; //ͼ�ṹ�Ķ���