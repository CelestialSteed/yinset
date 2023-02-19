#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Config.h"
#include "Edge.h"

class Triangle;
class TriangleList;

bool operator==(const Triangle &f1, const Triangle &f2);

std::ostream &operator<<(std::ostream &out, const Triangle &f);

class Triangle
{
private:
    Integer vertex[3];

public:
    Triangle(const Integer &x, const Integer &y, const Integer &z);

    Integer operator()(const Integer &index) const;
    Integer &operator()(const Integer &index);
};

class TriangleList
{
private:
    std::vector<Triangle> triangle;

public:
    Integer size() const;

    void insert(const Triangle &f);

    void erase(const Integer &index);
    void erase(std::vector<Integer> index);

    Integer find(const Triangle &f) const;
    std::vector<Integer> find(const Integer &v) const;
    std::vector<Integer> find(const Edge &e) const;

    Triangle operator()(const Integer &index) const;
    Triangle &operator()(const Integer &index);
};

bool operator==(const Triangle &f1, const Triangle &f2)
{
    return (f1(0) == f2(0)) && (f1(1) == f2(1)) && (f1(2) == f2(2));
}

std::ostream &operator<<(std::ostream &out, const Triangle &f)
{
    std::cout << f(0) << " " << f(1) << " " << f(2);
    return out;
}

Triangle::Triangle(const Integer &x, const Integer &y, const Integer &z)
{
    if (x == y || y == z || z == x)
    {
        MW_ERROR
    }
    this->vertex[0] = x;
    this->vertex[1] = y;
    this->vertex[2] = z;
    std::sort(&vertex[0], &vertex[2]);
}

Integer Triangle::operator()(const Integer &index) const
{
    if (0 <= index && index <= 2)
    {
        return vertex[index];
    }
    MW_ERROR
}

Integer &Triangle::operator()(const Integer &index)
{
    if (0 <= index && index <= 2)
    {
        return vertex[index];
    }
    MW_ERROR
}

Integer TriangleList::size() const
{
    return (Integer)triangle.size();
}

void TriangleList::insert(const Triangle &f)
{
    for (Integer i = 0; i < (Integer)triangle.size(); i++)
    {
        if (triangle[i] == f)
        {
            return;
        }
    }
    triangle.push_back(f);
    return;
}

void TriangleList::erase(const Integer &index)
{
    if (index >= (Integer)triangle.size())
    {
        MW_ERROR
    }
    triangle.erase(triangle.begin() + index);
    return;
}

void TriangleList::erase(std::vector<Integer> index)
{
    std::sort(index.begin(), index.end(), std::greater<Integer>());
    for (Integer i = 0; i < (Integer)index.size(); i++)
    {
        if (index[i] < (Integer)triangle.size())
        {
            triangle.erase(triangle.begin() + index[i]);
        }
    }
    return;
}

Integer TriangleList::find(const Triangle &f) const
{
    for (Integer i = 0; i < (Integer)triangle.size(); i++)
    {
        if (triangle[i] == f)
        {
            return i;
        }
    }
    return -1;
}

std::vector<Integer> TriangleList::find(const Integer &e) const
{
    std::vector<Integer> res;
    for (Integer i = 0; i < (Integer)triangle.size(); i++)
    {
        if (triangle[i](0) == e || triangle[i](1) == e || triangle[i](2) == e)
        {
            res.push_back(i);
        }
    }
    return res;
}

std::vector<Integer> TriangleList::find(const Edge &e) const
{
    std::vector<Integer> res;
    for (Integer i = 0; i < (Integer)triangle.size(); i++)
    {
        if (triangle[i](0) == e(0) && triangle[i](1) == e(1))
        {
            res.push_back(i);
        }
        else if (triangle[i](0) == e(0) && triangle[i](2) == e(1))
        {
            res.push_back(i);
        }
        else if (triangle[i](1) == e(0) && triangle[i](2) == e(1))
        {
            res.push_back(i);
        }
    }
    return res;
}

Triangle TriangleList::operator()(const Integer &index) const
{
    if (index >= (Integer)triangle.size())
    {
        MW_ERROR
    }
    return triangle.at(index);
}

Triangle &TriangleList::operator()(const Integer &index)
{
    if (index >= (Integer)triangle.size())
    {
        MW_ERROR
    }
    return triangle.at(index);
}

#endif
