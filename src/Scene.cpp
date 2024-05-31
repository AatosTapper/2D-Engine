#include "Scene.h"

#include <cassert>
#include <stdexcept>

#include "systems/TimerSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/CameraControllerSystem.h"

Scene::Scene()
{
    add_system(&TimerSystem::get_base_instance());
    add_system(&PhysicsSystem::get_base_instance());
}

void Scene::add_entity(std::unique_ptr<Entity> obj)
{
    assert(obj && "Cannot add an invalid game object to a scene");
    const Entity::id_t id = obj->get_id();

    m_entity_storage[id] = std::move(obj);
    if (std::find(m_current_entities.begin(), m_current_entities.end(), id) == m_current_entities.end()) 
    {
        m_current_entities.push_back(id);
    }

    m_entity_storage.at(id)->on_attach();
}

void Scene::add_system(Ptr<System> system)
{
    if (std::find(m_game_systems.begin(), m_game_systems.end(), system) != m_game_systems.end()) 
    {
        std::runtime_error("Tried to add an already existing game system to a scene");;
        return;
    }

    m_game_systems.push_back(system);
}

std::optional<Ptr<Entity>> Scene::get_entity(Entity::id_t id) const
{
    if (m_entity_storage.find(id) == m_entity_storage.end())
    {
        return std::nullopt;
    }
    return Ptr<Entity>(m_entity_storage.at(id).get());
}

std::vector<Ptr<Entity>> Scene::get_all_entities() const
{
    std::vector<Ptr<Entity>> output;
    output.reserve(m_entity_storage.size());
    for (const auto &it : m_entity_storage)
    {
        output.push_back(it.second.get());
    }
    return output;
}

std::vector<Ptr<Entity>> Scene::get_all_entities_with_flags(EntityFlags flag) const
{
    std::vector<Ptr<Entity>> output;
    for (const auto &it : m_entity_storage)
    {
        if (it.second->has_flags(flag))
        {
            output.push_back(it.second.get());
        }
    }
    return output;
}

std::vector<Ptr<Entity>> Scene::get_all_entities_except_flags(EntityFlags flag) const
{
    std::vector<Ptr<Entity>> output;
    for (const auto &it : m_entity_storage)
    {
        if (!it.second->has_flags(flag))
        {
            output.push_back(it.second.get());
        }
    }
    return output;
}

void Scene::delete_entity(Entity::id_t id)
{
    if (std::find(m_delete_queue.begin(), m_delete_queue.end(), id) == m_delete_queue.end()) 
    {
        m_delete_queue.push_back(id);
    }
}

void Scene::update()
{   
    handle_deletions();
    
    for (auto id : m_current_entities)
    {
        m_entity_storage.at(id)->on_update();
    }

    for (auto id : m_current_entities)
    {
        m_entity_storage.at(id)->update_components();
    }

    for (auto system : m_game_systems)
    {
        system->update();
    }
}

void Scene::handle_deletions()
{
    // first run all on_destroy()s
    for (auto id : m_delete_queue)
    {
        m_entity_storage.at(id)->on_destroy();
    }

    // only after that can we delete them
    for (auto id : m_delete_queue)
    {   
        m_entity_storage.erase(id);
        m_current_entities.erase(
            std::remove(m_current_entities.begin(), m_current_entities.end(), id), 
            m_current_entities.end()
        );
    }

    m_delete_queue.clear();
}