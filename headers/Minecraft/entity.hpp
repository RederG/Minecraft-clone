#ifndef __ENTITY_HPP__
    #define __ENTITY_HPP__
    
    #include "../tool.hpp"

    namespace Minecraft{

        class Entity{
            public:
                Entity();
                Entity(std::string name);
                virtual void update(GLFWwindow* window);
            protected:
                std::string name;
                glm::vec3 position;
                long long id;
        };

        void init_entities();
        void terminate_entities();
        void add_entity(Entity* entity);
        long long generate_entity_id();
    };

#endif