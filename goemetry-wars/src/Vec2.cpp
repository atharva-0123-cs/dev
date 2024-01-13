#include "Vec2.h"
#include <iostream>


Vec2::Vec2() {}

Vec2::Vec2(float xin, float yin) : x(xin) , y(yin) {}

bool Vec2::operator == (const Vec2& rsh) const
{
    return ( this->x == rsh.x && this->y == rsh.y);
}

bool Vec2::operator != (const Vec2& rsh) const
{
    return !( this->x == rsh.x && this->y == rsh.y);
}

Vec2 Vec2::operator + (const Vec2& rsh) const
{
    return Vec2(
        this->x + rsh.x,
        this->y + rsh.y
    );
}

Vec2 Vec2::operator - (const Vec2& rsh) const
{
    return Vec2(
        this->x - rsh.x,
        this->y - rsh.y
    );
}

Vec2 Vec2::operator * (const Vec2& rsh) const
{
    return Vec2(
        this->x * rsh.x,
        this->y * rsh.y
    );
}

Vec2 Vec2::operator / (const Vec2& rsh) const
{
    return Vec2(
        this->x / rsh.x,
        this->y / rsh.y
    );
}

void Vec2::operator += (const Vec2& rsh)
{
    this->x += rsh.x;
    this->y += rsh.y;
}

void Vec2::operator -= (const Vec2& rsh)
{
    this->x -= rsh.x;
    this->y -= rsh.y;
}

void Vec2::operator *= (const float value)
{
    this->x *= value;
    this->y *= value;
}

void Vec2::operator /= (const float value)
{
    this->x /= value;
    this->y /= value;
}


void Vec2::print() const
{
    std::cout<<" "<<x<<" "<<y<<std::endl;
}


