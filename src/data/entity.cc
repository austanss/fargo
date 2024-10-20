#include "data/entity.hh"

using namespace fargo;

Entity::Entity() 
{
    this->uid = 0;
    this->month_age = 0;
}

Entity::~Entity() {}

EntityCollection::EntityCollection() 
{
    this->entity_map = new std::map<unsigned long, Entity*>();
    this->ordered_uids = new std::vector<unsigned long>();
}

EntityCollection::~EntityCollection() 
{
    for (unsigned long i = 0; i < this->ordered_uids->size(); i++) {
        delete this->entity_map->at(this->ordered_uids->at(i));
    }

    delete this->entity_map;
    delete this->ordered_uids;
}

// Please do not attempt to create an entity with a UID that already exists
// Trying to check for that would be very painful to compute
void EntityCollection::create(const unsigned long uid) 
{
    Entity* new_entity = new Entity();
    new_entity->uid = uid;
    this->entity_map->insert(std::pair<unsigned long, Entity*>(uid, new_entity));
    this->ordered_uids->push_back(uid);
}

void EntityCollection::destroy(const unsigned long uid) 
{
    delete this->entity_map->at(uid);
    this->entity_map->erase(uid);
    for (unsigned long i = 0; i < this->ordered_uids->size(); i++) {
        if (this->ordered_uids->at(i) == uid) {
            this->ordered_uids->erase(this->ordered_uids->begin() + i);
            break;
        }
    }
}
