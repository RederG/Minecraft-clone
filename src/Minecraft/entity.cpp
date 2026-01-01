#include "../../headers/Minecraft/entity.hpp"

const std::string ENTITY_ID_CREATOR_TIMER = "entity_id_creator_timer";
int entity_number = 0;
std::vector<Minecraft::Entity*> all_entities;

namespace Minecraft{

    Entity::Entity(){
        this->name = "";
        this->position = {0, 0, 0};
        this->id = 0;
        add_entity(this);
    }

    Entity::Entity(std::string name)
    : name(name){
        this->id = generate_entity_id();
        this->position = {0, 0, 0};
        add_entity(this);
    }

    void Entity::update(GLFWwindow* window){}

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
        if(std::find(all_entities.begin(), all_entities.end(), entity) == all_entities.end())
            all_entities.push_back(entity);
    }

    long long generate_entity_id(){
        entity_number++;
        float duration = Tool::Timer::get_duration(ENTITY_ID_CREATOR_TIMER);
        return (int(duration) % entity_number) + int(entity_number * duration);
    }
};