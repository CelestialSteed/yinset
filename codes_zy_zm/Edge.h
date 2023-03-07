#ifndef EDGE_H
#define EDGE_H

#include "Config.h"

struct Edge;
class EdgeList;

bool operator==(const Edge &e1, const Edge &e2);

std::ostream &operator<<(std::ostream &out, const Edge &e);

class Edge
{
private:
    Integer vertex[2];

public:
    Edge(const Integer &x, const Integer &y);

    Integer operator()(const Integer &index) const;
    Integer &operator()(const Integer &index);
    //*** length of edge
    //Real length();
};

class EdgeList
{
private:
    std::vector<Edge> edge;

public:
    Integer size() const;

    void insert(const Edge &e);

    void erase(const Integer &index);
    void erase(std::vector<Integer> index);

    Integer find(const Edge &e) const;
    std::vector<Integer> find(const Integer &v) const;

    Edge operator()(const Integer &index) const;
    Edge &operator()(const Integer &index);
};

bool operator==(const Edge &e1, const Edge &e2)
{
    return (e1(0) == e2(0)) && (e1(1) == e2(1));
}

std::ostream &operator<<(std::ostream &out, const Edge &e)
{
    std::cout << e(0) << " " << e(1);
    return out;
}

Edge::Edge(const Integer &x, const Integer &y)
{
    if (x == y)
    {
        MW_ERROR
    }
    this->vertex[0] = std::min(x, y);
    this->vertex[1] = std::max(x, y);
}

Integer Edge::operator()(const Integer &index) const
{
    if (0 <= index && index <= 1)
    {
        return vertex[index];
    }
    MW_ERROR
}

Integer &Edge::operator()(const Integer &index)
{
    if (0 <= index && index <= 1)
    {
        return vertex[index];
    }
    MW_ERROR
}

/*
Real Edge::length()
{
    return distance()
}
*/

Integer EdgeList::size() const
{
    return (Integer)edge.size();
}

void EdgeList::insert(const Edge &e)
{
    for (Integer i = 0; i < (Integer)edge.size(); i++)
    {
        if (edge[i] == e)
        {
            return;
        }
    }
    edge.push_back(e);
    return;
}

void EdgeList::erase(const Integer &index)
{
    if (index >= (Integer)edge.size())
    {
        MW_ERROR
    }
    edge.erase(edge.begin() + index);
    return;
}

void EdgeList::erase(std::vector<Integer> index)
{
    std::sort(index.begin(), index.end(), std::greater<Integer>());
    for (Integer i = 0; i < (Integer)index.size(); i++)
    {
        if (index[i] < (Integer)edge.size())
        {
            edge.erase(edge.begin() + index[i]);
        }
    }
    return;
}

Integer EdgeList::find(const Edge &e) const
{
    for (Integer i = 0; i < (Integer)edge.size(); i++)
    {
        if (edge[i] == e)
        {
            return i;
        }
    }
    return -1;
}

std::vector<Integer> EdgeList::find(const Integer &v) const
{
    std::vector<Integer> res;
    for (Integer i = 0; i < (Integer)edge.size(); i++)
    {
        if (edge[i](0) == v || edge[i](1) == v)
        {
            res.push_back(i);
        }
    }
    return res;
}

Edge EdgeList::operator()(const Integer &index) const
{
    if (index >= (Integer)edge.size())
    {
        MW_ERROR
    }
    return edge.at(index);
}

Edge &EdgeList::operator()(const Integer &index)
{
    if (index >= (Integer)edge.size())
    {
        MW_ERROR
    }
    return edge.at(index);
}

#endif
