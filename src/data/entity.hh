#pragma once
#include <map>
#include <vector>
#include "data/entity.hh"

namespace fargo
{

    class Entity 
    {

    public:
        unsigned long uid;
        unsigned long month_age;
        bool fertile;

        Entity();
        ~Entity();

    };

    class EntityCollection
    {
    
    public:
        EntityCollection();
        ~EntityCollection();

        void create(const unsigned long uid);
        void destroy(const unsigned long uid);

        Entity& get_by_index(const unsigned long index) const {
            return *(this->entity_map->at(this->ordered_uids->at(index)));
        }
        Entity& get_by_uid(const unsigned long uid) const {
            return *(this->entity_map->at(uid));
        }

        const unsigned long count() const {
            return this->entity_map->size();
        }

    private:
        std::vector<unsigned long>* ordered_uids;
        std::map<unsigned long, Entity*>* entity_map;

    };

}
