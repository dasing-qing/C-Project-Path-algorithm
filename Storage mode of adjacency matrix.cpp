#define MAX_NUM 20//最大顶点数目
#define INFINITY 65535//无穷大的数 
typedef enum { DN, UDN } GraphKind;//图类型标志:有向网,无向网
typedef struct {
	int data;
} VertexNode; //图中顶点结构定义
typedef struct {
	int Value;//权值
} ArcCell, AdjMatrix[MAX_NUM][MAX_NUM]; //边或弧结构的定义
typedef struct {
	VertexNode Vertex[MAX_NUM];//存储顶点数组
	AdjMatrix arcs;//存储顶点之间的关系，即边或弧(邻接矩阵)
	int Vexnum, Arcnum;//当前途中顶点数目、边或弧数目
	GraphKind kind;//图的类型
} MGraph; //图结构的定义