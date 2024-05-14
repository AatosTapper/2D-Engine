#include "Scene.h"

#include <cassert>
#include <stdexcept>

#include "engine/systems/TimerSystem.h"

Scene::Scene()
{
    add_system(&TimerSystem::get_base_instance());
}

void Scene::add_game_object(std::unique_ptr<GameObject> obj)
{
    assert(obj && "Cannot add an invalid game object to a scene");
    const GameObject::id_t id = obj->get_id();

    game_object_storage[id] = std::move(obj);
    if (std::find(current_game_objects.begin(), current_game_objects.end(), id) == current_game_objects.end()) 
    {
        current_game_objects.push_back(id);
    }

    game_object_storage.at(id)->on_attach();
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

std::optional<Ptr<GameObject>> Scene::get_game_object(GameObject::id_t id) const
{
    if (game_object_storage.find(id) == game_object_storage.end())
    {
        return std::nullopt;
    }
    return Ptr<GameObject>(game_object_storage.at(id).get());
}

std::vector<Ptr<GameObject>> Scene::get_all_game_objects() const
{
    std::vector<Ptr<GameObject>> output;
    output.reserve(game_object_storage.size());
    for (const auto &it : game_object_storage)
    {
        output.push_back(it.second.get());
    }
    return output;
}

std::vector<Ptr<GameObject>> Scene::get_all_game_objects_with_flags(ObjectFlags flag) const
{
    std::vector<Ptr<GameObject>> output;
    for (const auto &it : game_object_storage)
    {
        if (it.second->has_flags(flag))
        {
            output.push_back(it.second.get());
        }
    }
    return output;
}

std::vector<Ptr<GameObject>> Scene::get_all_game_objects_except_flags(ObjectFlags flag) const
{
    std::vector<Ptr<GameObject>> output;
    for (const auto &it : game_object_storage)
    {
        if (!it.second->has_flags(flag))
        {
            output.push_back(it.second.get());
        }
    }
    return output;
}

void Scene::delete_game_object(GameObject::id_t id)
{
    if (std::find(delete_queue.begin(), delete_queue.end(), id) == delete_queue.end()) 
    {
        delete_queue.push_back(id);
    }
}

void Scene::update()
{
    handle_deletions();
    
    for (auto id : current_game_objects)
    {
        game_object_storage.at(id)->on_update();
    }

    for (auto id : current_game_objects)
    {
        game_object_storage.at(id)->update_components();
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
        game_object_storage.at(id)->on_destroy();
    }

    // only after that can we delete them
    for (auto id : delete_queue)
    {   
        game_object_storage.erase(id);
        current_game_objects.erase(
            std::remove(current_game_objects.begin(), current_game_objects.end(), id), 
            current_game_objects.end()
        );
    }

    delete_queue.clear();
}