#pragma once

class Vec2
{
public:

    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float xin, float yin);

    bool operator == (const Vec2& rsh) const;
    bool operator != (const Vec2& rsh) const;

    Vec2 operator + (const Vec2& rsh) const;
    Vec2 operator - (const Vec2& rsh) const;
    Vec2 operator * (const Vec2& rsh) const;
    Vec2 operator / (const Vec2& rsh) const;
    
    void operator += (const Vec2& rsh);
    void operator -= (const Vec2& rsh);
    void operator *= (const float value);
    void operator /= (const float value);

    void print() const;

};