#ifndef SURFACE_H
#define SURFACE_H

#include "Config.h"

using Point = Eigen::Matrix<Real, 3, 1>;

class Surface;

Surface fitSurface(const std::vector<Point> &p, const Integer &degree);

class Surface
{
private:
    Integer degree;
    std::vector<Real> coefs;

public:
    Surface(const Integer &degree);

    Integer getDegree() const;

    Real operator()(const Integer &x, const Integer &y, const Integer &z) const;
    Real &operator()(const Integer &x, const Integer &y, const Integer &z);
    bool operator()(const Point &p) const;

    Integer num(const Integer &x, const Integer &y, const Integer &z) const;
};

#endif