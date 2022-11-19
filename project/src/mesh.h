#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

struct Triangle
{
	int idx; //tris[idx] is this triangle
	int v1i, v2i, v3i; //verts[v1i]-verts[v2i]-verts[v3i] forms this triangle
	float area, *normal;

	Triangle(int i, int a, int b, int c) : idx(i), v1i(a), v2i(b), v3i(c) {};
};

struct Vertex
{
	int idx; //verts[idx] is this veryex
	float* coords, //coords[0] ~ x coordinate, ..
		 * normal;
	Vertex(int i, float* c) : idx(i), coords(c) {};

	vector< int > vertList; //adjacent verts
	vector< int > edgeList; //adjacent edges
	vector< int > triList; //adjacent tris
};

struct Edge
{
	int idx; //edges[idx] is this edge
	int v1i, v2i; //verts[v1i]-verts[v2i] are the endpnts of this edge
	float length;
	Edge(int i, int a, int b, float l) : idx(i), v1i(a), v2i(b), length(l) {};
};

class Mesh
{
private:

public:
	vector< Triangle* > tris;
	vector< Vertex* > verts;
	vector< Edge* > edges;
	void loadObjFile(string fName);
    void loadModel();
    void makeObj(string fName);
	//void createCube(float sideLength);

    float distanceBetween(float* a, float* b);
    int addVertex(float* coords);
    void addTriangle(int v1i, int v2i, int v3i);
    void removeTriangle(int v1i, int v2i, int v3i);
    bool triangleExists(int v1i, int v2i, int v3i);
    void splitTriangle(int idx);
    bool makeVertsNeighbors(int v, int w);
    bool makeVertsUnneighbors(int v, int w);
    void addEdge(int a, int b);
    void removeEdge(int a, int b);

	char* filename;     //文件名
    char* cache;        //缓存
    size_t size;        //文件大小
    int nVertex = 0;
    int nFaces = 0;
};


void Mesh::loadObjFile(string fName)
{
    std::cout << "loading obj file ... " << std::endl;

    int m = fName.size();
    char* pstr = (char*)malloc(m+1);
    strcpy(pstr,(char*)fName.c_str());

    size_t bytes = 0;                      //size_t它是一种“整型”类型，里面保存的是一个整数
    FILE* file = fopen((char*) pstr, "rt");

    if (file != NULL) {
        fseek(file, 0, SEEK_END);     //把file指针退回到离文件结尾0字节处
        size_t end = ftell(file);     //函数 ftell() 用于得到文件指针当前位置相对于文件首的偏移字节数。
        fseek(file, 0, SEEK_SET);

        cache = (char*) malloc(end);
        bytes = fread(cache, sizeof(char), end, file);  //缓冲区、基本单元字节大小、基本单元个数、文件指针，bytes为基本单元个数

        fclose(file);
    }

    size = bytes;

}

void Mesh::loadModel()
{
    std::cout << "loading obj model ... " << std::endl;

    char* p = NULL, * e = NULL;
    bool start = true;
    char mtl[50];
    p = cache;
    e = cache + size;

	//cout << "want to get n" << endl;

    while (p != e) {
            if (memcmp(p, "v",  1) == 0) nVertex++;
            else if (memcmp(p, "f",  1) == 0) nFaces++;

            while (*p++ != '\n');    //换行
    }

	//cout << "get n" << endl;

    p = cache;
    int nV = 0, nF = 0;
    int a, b, c, d;
    float x,y,z;

    while (p != e) {
            if (memcmp(p, "v", 1) == 0) {     //memcmp比较内存区域buf1和buf2的前count个字节
                    sscanf(p, "v %f %f %f", &x, &y, &z); //p读到右边
                    float* coords = new float[3];
                    coords[0] = x;
                    coords[1] = y;
                    coords[2] = z;
                    addVertex(coords); //ND: no duplicate check
                    //std::cout << "get a vertex ... " << std::endl;
                    nV++;
            } else if (memcmp(p, "f", 1) == 0) {
                    sscanf(p, "f %d %d %d", &a, &b, &c);
					a--;b--;c--;
                    addTriangle((int) a, (int) b, (int) c);
                    //std::cout << "get a triangle ... " << std::endl;
                    nF++;
            } else if (memcmp(p, "usemtl", 6) == 0) {
                    sscanf(p, "usemtl %s", mtl);
            }
            while (*p++ != (char) 0x0A);  //换行
    }

	cout << "Mesh has " << (int) tris.size() << " tris, " << (int) verts.size() << " verts, " << (int) edges.size() << " edges\nInitialization done\n";
}

////

void Mesh::makeObj(string fName)
{
    std::cout << "makeing obj file ... " << std::endl;
	fName = "../output/" + fName + ".obj";
    ofstream location_out;
    location_out.open(fName, ios::out | ios::app);
	float x,y,z;
	int a,b,c;

	for (int i = 0; i < verts.size(); i++)
	{
       location_out << "v" <<"  ";
       x=verts[i]->coords[0];
	   y=verts[i]->coords[1];
	   z=verts[i]->coords[2];
       location_out << x << " " << y <<" " << z <<"\n";
	}
	for (int i = 0; i < tris.size(); i++)
	{
       location_out << "f" <<"  ";
       a=tris[i]->v1i + 1;
	   b=tris[i]->v2i + 1;
	   c=tris[i]->v3i + 1;
       location_out << a << " " << b <<" " << c <<"\n";
	}

    std::cout << "Output " << fName << " successfully" << std::endl; 
}

int Mesh::addVertex(float* coords)
{
	//cout << "adding vertex : " << coords[0] << " " << coords[1] << " " << coords[2] << endl;
	int idx;
	if (verts.size() == 0)
		idx = 0;
	else
		idx = (int) verts[verts.size()-1]->idx + 1;
	verts.push_back(new Vertex(idx, coords));
	return idx;
}

void Mesh::addTriangle(int v1i, int v2i, int v3i)
{
	int idx;
	if (tris.size() == 0)
		idx = 0;
	else
		idx = (int)tris[tris.size() - 1]->idx + 1;

	tris.push_back(new Triangle(idx, v1i, v2i, v3i));

	verts[v1i]->triList.push_back(idx);
	verts[v2i]->triList.push_back(idx);
	verts[v3i]->triList.push_back(idx);

	if (!makeVertsNeighbors(v1i, v2i))
		addEdge(v1i, v2i);

	if (!makeVertsNeighbors(v1i, v3i))
		addEdge(v1i, v3i);

	if (!makeVertsNeighbors(v2i, v3i))
		addEdge(v2i, v3i);
}

bool Mesh::triangleExists(int v1i, int v2i, int v3i) {
	int idx = -1;
	for (int i = 0; i < tris.size(); i++) {
		if (tris[i]->v1i == v1i && tris[i]->v2i == v2i && tris[i]->v3i == v3i) {
			idx = tris[i]->idx;
		}
	}
	return idx != -1;
}

void Mesh::removeTriangle(int v1i, int v2i, int v3i)
{
	int idx = -1;
	for (int i = 0; i < tris.size(); i++) {
		if (tris[i]->v1i == v1i && tris[i]->v2i == v2i && tris[i]->v3i == v3i) {
			idx = tris[i]->idx;
			tris.erase(tris.begin() + i);
		}
	}

	if (idx == -1) {
		cout << "no such triangle " << endl;
		return;
	}

	for (int i = 0; i < verts[v1i]->triList.size(); i++) {
		if (idx == verts[v1i]->triList[i]) {
			verts[v1i]->triList.erase(verts[v1i]->triList.begin() + i);
		}
	}
	for (int i = 0; i < verts[v2i]->triList.size(); i++) {
		if (idx == verts[v2i]->triList[i]) {
			verts[v2i]->triList.erase(verts[v2i]->triList.begin() + i);
		}
	}
	for (int i = 0; i < verts[v3i]->triList.size(); i++) {
		if (idx == verts[v3i]->triList[i]) {
			verts[v3i]->triList.erase(verts[v3i]->triList.begin() + i);
		}
	}

	if (!makeVertsUnneighbors(v1i, v2i))
		removeEdge(v1i, v2i);

	if (!makeVertsUnneighbors(v1i, v3i))
		removeEdge(v1i, v3i);

	if (!makeVertsUnneighbors(v2i, v3i))
		removeEdge(v2i, v3i);
}

void Mesh::splitTriangle(int idx) {
	Triangle *tri = tris[10];

	float coord_centroid[3] = {
		(verts[tri->v1i]->coords[0] + verts[tri->v2i]->coords[0] + verts[tri->v3i]->coords[0]) / 3,
		(verts[tri->v1i]->coords[1] + verts[tri->v2i]->coords[1] + verts[tri->v3i]->coords[1]) / 3,
		(verts[tri->v1i]->coords[2] + verts[tri->v2i]->coords[2] + verts[tri->v3i]->coords[2]) / 3 };

	int idx_centroid = addVertex(coord_centroid);

	cout << coord_centroid[0] << " " << coord_centroid[1] << " " << coord_centroid[2] << " " << idx_centroid << endl;

	addTriangle(verts[tri->v3i]->idx, verts[tri->v1i]->idx, idx_centroid);
	addTriangle(verts[tri->v2i]->idx, verts[tri->v3i]->idx, idx_centroid);
	addTriangle(verts[tri->v1i]->idx, verts[tri->v2i]->idx, idx_centroid);

	removeTriangle(verts[tri->v1i]->idx, verts[tri->v2i]->idx, verts[tri->v3i]->idx);
}

bool Mesh::makeVertsNeighbors(int v, int w)
{
	//try to make v and w neighbors; return true if already neigbors

	for (int check = 0; check < (int)verts[v]->vertList.size(); check++)
		if (verts[v]->vertList[check] == w)
			return true;

	verts[v]->vertList.push_back(w);
	verts[w]->vertList.push_back(v);
	return false;
}

bool Mesh::makeVertsUnneighbors(int v, int w)
{
	//try to make v and w unneighbors; return true if not neigbors

	for (int check = 0; check < (int)verts[v]->vertList.size(); check++)
		if (verts[v]->vertList[check] == w) {
			verts[v]->vertList.erase(verts[v]->vertList.begin() + check);
		}

	for (int check = 0; check < (int)verts[w]->vertList.size(); check++)
		if (verts[w]->vertList[check] == v) {
			verts[w]->vertList.erase(verts[w]->vertList.begin() + check);
			return false;
		}

	return true;
}

float Mesh::distanceBetween(float* a, float* b)
{
	return sqrt( (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2]));
}

void Mesh::addEdge(int a, int b)
{
	int idx;
	if (edges.size() == 0)
		idx = 0;
	else
		idx = (int)edges[edges.size() - 1]->idx + 1;

	edges.push_back(new Edge(idx, a, b, distanceBetween(verts[a]->coords, verts[b]->coords)));

	verts[a]->edgeList.push_back(idx);
	verts[b]->edgeList.push_back(idx);
}
void Mesh::removeEdge(int a, int b)
{
	int idx = -1;
	for (int i = 0; i < edges.size(); i++) {
		if ((edges[i]->v1i == a && edges[i]->v2i == b) || (edges[i]->v1i == b && edges[i]->v2i == a)) {
			idx = edges[i]->idx;
			edges.erase(edges.begin() + i);
		}
	}
	if (idx == -1)
		return;

	for (int i = 0; i < verts[a]->edgeList.size(); i++) {
		if (verts[a]->edgeList[i] == idx)
			verts[a]->edgeList.erase(verts[a]->edgeList.begin() + i);
	}
	for (int i = 0; i < verts[b]->edgeList.size(); i++) {
		if (verts[b]->edgeList[i] == idx)
			verts[b]->edgeList.erase(verts[b]->edgeList.begin() + i);
	}
}


#endif