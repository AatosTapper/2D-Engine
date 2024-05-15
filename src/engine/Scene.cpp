#include "Scene.h"

#include <cassert>
#include <stdexcept>

#include "engine/systems/TimerSystem.h"

Scene::Scene()
{
    add_system(&TimerSystem::get_base_instance());
}

void Scene::add_entity(std::unique_ptr<Entity> obj)
{
    assert(obj && "Cannot add an invalid game object to a scene");
    const Entity::id_t id = obj->get_id();

    entity_storage[id] = std::move(obj);
    if (std::find(current_entities.begin(), current_entities.end(), id) == current_entities.end()) 
    {
        current_entities.push_back(id);
    }

    entity_storage.at(id)->on_attach();
}

void Scene::add_system(Ptr<System> system)
{
    if (std::find(game_systems.begin(), game_systems.end(), system) != game_systems.end()) 
    {
        std::runtime_error("Tried to add an already existing game system to a scene");;
        return;
    }

    game_systems.push_back(system);
}

std::optional<Ptr<Entity>> Scene::get_entity(Entity::id_t id) const
{
    if (entity_storage.find(id) == entity_storage.end())
    {
        return std::nullopt;
    }
    return Ptr<Entity>(entity_storage.at(id).get());
}

std::vector<Ptr<Entity>> Scene::get_all_entities() const
{
    std::vector<Ptr<Entity>> output;
    output.reserve(entity_storage.size());
    for (const auto &it : entity_storage)
    {
        output.push_back(it.second.get());
    }
    return output;
}

std::vector<Ptr<Entity>> Scene::get_all_entities_with_flags(EntityFlags flag) const
{
    std::vector<Ptr<Entity>> output;
    for (const auto &it : entity_storage)
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
    for (const auto &it : entity_storage)
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
    if (std::find(delete_queue.begin(), delete_queue.end(), id) == delete_queue.end()) 
    {
        delete_queue.push_back(id);
    }
}

void Scene::update()
{
    handle_deletions();
    
    for (auto id : current_entities)
    {
        entity_storage.at(id)->on_update();
    }

    for (auto id : current_entities)
    {
        entity_storage.at(id)->update_components();
    }

    for (auto system : game_systems)
    {
        system->update();
    }
}

void Scene::handle_deletions()
{
    // first run all on_destroy()s
    for (auto id : delete_queue)
    {
        entity_storage.at(id)->on_destroy();
    }

    // only after that can we delete them
    for (auto id : delete_queue)
    {   
        entity_storage.erase(id);
        current_entities.erase(
            std::remove(current_entities.begin(), current_entities.end(), id), 
            current_entities.end()
        );
    }

    delete_queue.clear();
}