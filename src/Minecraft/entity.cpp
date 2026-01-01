#include "../../headers/Minecraft/entity.hpp"

const std::string ENTITY_ID_CREATOR_TIMER = "entity_id_creator_timer";
int entity_number = 0;
std::vector<Minecraft::Entity*> all_entities;

namespace Minecraft{

    Entity::Entity(std::string name)
    : name(name){
        this->id = generate_entity_id();
        add_entity(this);
    }

    void init_entities(){
        Tool::Timer::create(ENTITY_ID_CREATOR_TIMER);
        Tool::Timer::start(ENTITY_ID_CREATOR_TIMER);

        for(auto& entity : all_entities){
            delete entity;
            entity = nullptr;
        }
        all_entities.clear();
    }

    void terminate_entities(){
        Tool::Timer::stop(ENTITY_ID_CREATOR_TIMER);

        for(auto& entity : all_entities){
            delete entity;
            entity = nullptr;
        }
        all_entities.clear();
    }

    void add_entity(Entity* entity){
        all_entities.push_back(entity);
    }

    long long generate_entity_id(){
        entity_number++;
        float duration = Tool::Timer::get_duration(ENTITY_ID_CREATOR_TIMER);
        return (entity_number % int(duration)) + int(entity_number * duration);
    }
};