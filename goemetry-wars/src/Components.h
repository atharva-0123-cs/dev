#pragma once

#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CTrasform {

public:
  Vec2 pos = {0.f, 0.f};
  Vec2 velocity = {0.f, 0.f};
  float angle = 0;

  CTrasform(const Vec2 &p, const Vec2 &v, float a)
      : pos(p), velocity(v), angle(a) {}
};

class CShape {

public:
  sf::CircleShape circle;

  CShape(float radius, int pointCount, const sf::Color &fill,
         const sf::Color outline, float thickness)
      : circle(radius, pointCount) {
    circle.setFillColor(fill);
    circle.setOutlineColor(outline);
    circle.setOutlineThickness(thickness);
    circle.setOrigin(radius, radius);
  }
};

class CCollision {

public:
  float radius = 0.f;
  CCollision(float r) : radius(r) {}
};

class CScore {

public:
  int score = 0;
  CScore(int s) : score(s) {}
};

class CLifespan {

public:
  int remaining = 0;
  int total = 0;
  CLifespan(int total) : remaining(total), total(total) {}
};

class CInput {

public:
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;

  CInput() {}

};
