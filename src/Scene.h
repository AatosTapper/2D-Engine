#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <optional> // google this if you intend to use "get_entity()"

#include "Entity.h"
#include "System.h"
#include "Ref.h"

class Scene
{
public:
    Scene();

    void add_entity(std::unique_ptr<Entity> obj);
    void add_system(Ptr<System> system);

    [[nodiscard]] std::optional<Ptr<Entity>> get_entity(Entity::id_t id) const; // this reference becomes invalid after current frame
    [[nodiscard]] std::vector<Ptr<Entity>> get_all_entities() const;
    [[nodiscard]] std::vector<Ptr<Entity>> get_all_entities_with_flags(EntityFlags flag) const;
    [[nodiscard]] std::vector<Ptr<Entity>> get_all_entities_except_flags(EntityFlags flag) const;

    void delete_entity(Entity::id_t id); // defers the delete until the start of the next frame

    void update();

private:
    std::unordered_map<Entity::id_t, std::unique_ptr<Entity>> m_entity_storage;
    std::vector<Entity::id_t> m_current_entities;
    std::vector<Entity::id_t> m_delete_queue;

    std::vector<Ptr<System>> m_game_systems;

    void handle_deletions();
};
