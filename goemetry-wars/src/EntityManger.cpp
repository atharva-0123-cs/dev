#include"EntityManger.h"
#include "Entity.h"


EntityManger::EntityManger()
{

}

void EntityManger::update()
{
    //  TODO : add entities from m_entitiesToAdd to the proper location(s)
            //  - add them to the vector of all entities
            for(auto& e : m_entitiesToAdd)
            {
                m_entities.push_back(e);
            }
            //  - add them to the vector inside the map, with the tag as key
            for(auto& e : m_entitiesToAdd)
            {
                m_entityMap[e->tag()].push_back(e);
            }

            m_entitiesToAdd.clear();

    //  remove dead entities form  vectoe of all entities
    removeDeadEntities(m_entities);

    //  remove the dead entities for each vector of the emtity map
    // C++17 ways of iterting through [key,value] pair in a map
    for(auto& [tag,entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }

}

void EntityManger::removeDeadEntities(EntityVec& vec)
{
    //  TODO : remove all  dead entites form the input vector
    //         - this is called by update function
    for(auto& e : vec)
    {   
        auto condition = [](auto e){ return !e->isActive();};
        // bool condition = !e->isActive();
        
        vec.erase(std::remove_if(vec.begin(), vec.end(), condition), vec.end());
    }
}

std::shared_ptr<Entity> EntityManger::addEntity(const std::string& tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

    m_entitiesToAdd.push_back(entity);

    return entity;
}

const EntityVec& EntityManger::getEntities()
{
    return m_entities;
}

const EntityVec& EntityManger::getEntities(std::string tag)
{
    return m_entityMap[tag];
}