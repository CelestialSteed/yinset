#ifndef VERTEX_H
#define VERTEX_H

#include "Config.h"

class Vertex;
class VertexList;

bool operator==(const Vertex &v1, const Vertex &v2);

Real distance(const Vertex &v1, const Vertex &v2);

std::ostream &operator<<(std::ostream &out, const Vertex &v);

class Vertex
{
private:
    Real coordinate[3];

public:
    Vertex(const Real &x, const Real &y, const Real &z);

    Real operator()(const Integer &index) const;
};

class VertexList
{
private:
    std::vector<Vertex> vertex;

public:
    Integer size() const;

    void insert(const Vertex &v);

    void erase(const Integer &index);
    void erase(std::vector<Integer> index);

    Integer find(const Vertex &v) const;

    Vertex operator()(const Integer &index) const;
};

bool operator==(const Vertex &v1, const Vertex &v2)
{
    return distance(v1, v2) <= DELTA;
}

Real distance(const Vertex &v1, const Vertex &v2)
{
    Real x = v1(0) - v2(0);
    Real y = v1(1) - v2(1);
    Real z = v1(2) - v2(2);
    return std::sqrt(x * x + y * y + z * z);
}

std::ostream &operator<<(std::ostream &out, const Vertex &v)
{
    std::cout << v(0) << " " << v(1) << " " << v(2);
    return out;
}

Vertex::Vertex(const Real &x, const Real &y, const Real &z)
{
    this->coordinate[0] = x;
    this->coordinate[1] = y;
    this->coordinate[2] = z;
}

Real Vertex::operator()(const Integer &index) const
{
    if (0 <= index && index <= 2)
    {
        return coordinate[index];
    }
    MW_ERROR
}

Integer VertexList::size() const
{
    return (Integer)vertex.size();
}

void VertexList::insert(const Vertex &v)
{
    for (Integer i = 0; i < (Integer)vertex.size(); i++)
    {
        if (vertex.at(i) == v)
        {
            return;
        }
    }
    vertex.push_back(v);
    return;
}

void VertexList::erase(const Integer &index)
{
    if (index >= (Integer)vertex.size())
    {
        MW_ERROR
    }
    vertex.erase(vertex.begin() + index);
    return;
}

void VertexList::erase(std::vector<Integer> index)
{
    std::sort(index.begin(), index.end(), std::greater<Integer>());
    for (Integer i = 0; i < (Integer)index.size(); i++)
    {
        if (index[i] < (Integer)vertex.size())
        {
            vertex.erase(vertex.begin() + index[i]);
        }
    }
    return;
}

Integer VertexList::find(const Vertex &v) const
{
    for (Integer i = 0; i < (Integer)vertex.size(); i++)
    {
        if (vertex.at(i) == v)
        {
            return i;
        }
    }
    return -1;
}

Vertex VertexList::operator()(const Integer &index) const
{
    if (index >= (Integer)vertex.size())
    {
        MW_ERROR
    }
    return vertex.at(index);
}

#endif
