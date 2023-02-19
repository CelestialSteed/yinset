#ifndef MODEL_H
#define MODEL_H

#include "Config.h"
#include "Vertex.h"
#include "Edge.h"
#include "Triangle.h"
#include "Surface.h"

class Model;

class Model
{
private:
    std::pair<Real, Real> range;

private:
    VertexList vertex;
    EdgeList edge;
    TriangleList triangle;

private:
    void triangulate(const std::vector<Integer> &list);
    void fixEdge(const Integer &n);
    std::vector<std::vector<Integer>> findHoles() const;
    void fillHoles(const std::vector<Integer> &v, const Integer &n);

public:
    Model(const std::pair<Real, Real> &range);
    void loadObjFile(const std::string &filename);
    void saveObjFile(const std::string &filename) const;
    void deleteVertex(const Integer &index);
    void deleteEdge(const Integer &index);
    void fix(const Integer &n);

//***
private:    //need in fixEdge
    bool isFit();
    void fixAnEdge();
    void fixLongEdge(Integer i);
    void fixShortEdge(Integer i);

//***
public:
    void test(const Integer &n);

};

//***
void Model::fixEdge(const Integer &n)
{
    Integer cnt = 0;
    while (!isFit() && cnt++ < n)
    {
        fixAnEdge();
    }
}

void Model::fixAnEdge()
{
    std::cout << "fixAnEdge" << std::endl;

    for (Integer i = 0; i < (Integer)edge.size(); i++)
    {
        Real length = distance(vertex(edge(i)(0)),vertex(edge(i)(1)));
        if (length > range.second)
        {
            std::cout << "fixLongEdge" << i << " , length = " << length << std::endl;
            fixLongEdge(i);
            return;
        }else if (length < range.first)
        {
            fixShortEdge(i);
            return;
        }
    }

    std::cout << "Error : fixed" << std::endl;

}

void Model::fixLongEdge(Integer i)
{
    Integer v1 = edge(i)(0), v2 = edge(i)(1);
    std::cout << "v1 = " << v1 << ", v2 = " << v2 << std::endl;

    //build new vertex v0
    Real newcoor[3];
    newcoor[0] = (vertex(v1)(0) + vertex(v2)(0)) / 2;
    newcoor[1] = (vertex(v1)(1) + vertex(v2)(1)) / 2;
    newcoor[2] = (vertex(v1)(2) + vertex(v2)(2)) / 2;
    Vertex newvert(newcoor[0],newcoor[1],newcoor[2]);
    vertex.insert(newvert);
    Integer v0 = vertex.find(newvert);      //v0是新点的序号

    std::cout << "v0 = " << v0 << std::endl;

    std::cout << "v1 = " << vertex(v1)(0) << "\t" << vertex(v1)(1) << "\t" << vertex(v1)(2) << std::endl;
    std::cout << "v2 = " << vertex(v2)(0) << "\t" << vertex(v2)(1) << "\t" << vertex(v2)(2) << std::endl;
    std::cout << "v0 = " << vertex(v0)(0) << "\t" << vertex(v0)(1) << "\t" << vertex(v0)(2) << std::endl;

    //find the triangle to be delete, 如果一边连接超过两个面会提示警告
    std::vector<Integer> exTris = triangle.find(edge(i));
    if (exTris.size() > 2)
    {
        std::cout << "警告：一边连接了两个面。" <<std::endl;
    }
    std::cout << "exTris.size() = " << exTris.size() << std::endl;
    std::cout << "开始找v3v4" << std::endl;
    //找面的顶点
    std::vector<Integer> exvert;
    for (Integer k = 0; k < exTris.size(); k++)
    {
        for (Integer j = 0; j < 3; j++)
        {
            Integer idx = triangle(exTris[k])(j);
            if (idx != v1 && idx != v2)
            {
                exvert.push_back(idx);
                break;
            }
        }
    }
    std::cout << "delete the old" << std::endl;
    //delete the old
    edge.erase(i);
    triangle.erase(exTris);
    std::cout << "build edge" << std::endl;
    //build the new edge
    Edge e1(v0,v1), e2(v0,v2);
    edge.insert(e1);
    edge.insert(e2);
    for (Integer j = 0; j < exvert.size(); j++)
    {
        Edge newedge(v0,exvert[j]);
        edge.insert(newedge);
    }
    std::cout << "build face" << std::endl;
    std::cout << "exvert.size() = " << exvert.size() << std::endl;
    //new triangle
    for (Integer j = 0; j < exvert.size(); j++)
    {
        Triangle newtri1(exvert[j],v1,v0);
        Triangle newtri2(exvert[j],v2,v0);
        triangle.insert(newtri1);
        triangle.insert(newtri2);
        std::cout << "tri.size = "  << triangle.size() << std::endl;
    }


}

void Model::fixShortEdge(Integer i)
{

}

bool Model::isFit()
{
    //std::cout << "size = " << edge.size() << std::endl;
    for (Integer i = 0; i < (Integer)edge.size(); i++)
    {
        Real length = distance(vertex(edge(i)(0)),vertex(edge(i)(1)));
        //std::cout << length << "\t";
        if (length < range.first || length > range.second)
        {
            return false;
        }
    }
    return true;
}

void Model::test(const Integer &n)
{
    fixAnEdge();
}

std::vector<std::vector<Integer>> Model::findHoles() const
{
    // TODO.
}

void Model::fillHoles(const std::vector<Integer> &v, const Integer &n)
{
    // TODO.
}

Model::Model(const std::pair<Real, Real> &range)
{
    this->range = range;
}

void Model::loadObjFile(const std::string &filename)
{
    std::ifstream fp(filename, std::ios::in);
    std::string s;
    while (!fp.eof())
    {
        std::getline(fp, s);
        auto tmp = split(s, ' ');
        if (tmp[0] == "v")
        {
            Vertex v((Real)std::stof(tmp[1]), (Real)std::stof(tmp[2]), (Real)std::stof(tmp[3]));
            vertex.insert(v);
        }
        else if (tmp[0] == "f")
        {
            Triangle f((Integer)std::stol(tmp[1]) - 1, (Integer)std::stol(tmp[2]) - 1, (Integer)std::stol(tmp[3]) - 1);
            triangle.insert(f);
            edge.insert(Edge(f(0), f(1)));
            edge.insert(Edge(f(1), f(2)));
            edge.insert(Edge(f(2), f(0)));
        }
    }
    fp.close();
    return;
}

void Model::saveObjFile(const std::string &filename) const
{
    std::ofstream fp(filename, std::ios::out);
    for (Integer i = 0; i < (Integer)vertex.size(); i++)
    {
        Vertex v = vertex(i);
        fp << "v " << v(0) << " " << v(1) << " " << v(2) << std::endl;
    }
    for (Integer i = 0; i < (Integer)triangle.size(); i++)
    {
        Triangle f = triangle(i);
        fp << "f " << f(0) + 1 << " " << f(1) + 1 << " " << f(2) + 1 << std::endl;
    }
    fp.close();
    return;
}

void Model::deleteVertex(const Integer &index)
{
    vertex.erase(index);
    edge.erase(edge.find(index));
    triangle.erase(triangle.find(index));
    for (Integer i = 0; i < (Integer)edge.size(); i++)
    {
        edge(i)(0) = edge(i)(0) > index ? edge(i)(0) - 1 : edge(i)(0);
        edge(i)(1) = edge(i)(1) > index ? edge(i)(1) - 1 : edge(i)(1);
    }
    for (Integer i = 0; i < (Integer)triangle.size(); i++)
    {
        triangle(i)(0) = triangle(i)(0) > index ? triangle(i)(0) - 1 : triangle(i)(0);
        triangle(i)(1) = triangle(i)(1) > index ? triangle(i)(1) - 1 : triangle(i)(1);
        triangle(i)(2) = triangle(i)(2) > index ? triangle(i)(2) - 1 : triangle(i)(2);
    }
    return;
}

void Model::deleteEdge(const Integer &index)
{
    triangle.erase(triangle.find(edge(index)));
    edge.erase(index);
    return;
}

void Model::fix(const Integer &n)
{
    fixEdge(n);
    std::vector<std::vector<Integer>> holes = findHoles();
    Integer m = holes.size();
    for (Integer i = 0; i < m; i++)
    {
        fillHoles(holes[i], n);
    }
    return;
}

#endif