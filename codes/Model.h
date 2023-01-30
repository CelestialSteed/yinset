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
};

void Model::fixEdge(const Integer &n)
{
    // TODO.
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