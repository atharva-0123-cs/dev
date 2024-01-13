#pragma once

#include<memory>
#include<string>
#include"Components.h"


class Entity 
{

    friend class EntityManger;

    bool        m_active   = true;
    size_t      m_id       = 0;
    std::string m_tag      = "default";

    //constructor
    Entity(const size_t id, const std::string& tag);

public:

    //component pointers
    std::shared_ptr<CTrasform>  cTransform;
    std::shared_ptr<CShape>     cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput>     cInput;
    std::shared_ptr<CScore>     cScore;
    std::shared_ptr<CLifespan>  cLifespan;

private:

    //private member access functions
    bool isActive() const;
    const  std::string& tag() const;
    const size_t id() const;
    
public:    
    void destroy();

};