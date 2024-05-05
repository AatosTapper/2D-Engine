#include "Scene.h"

#include <cassert>

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

std::optional<GameObject*> Scene::get_game_object(GameObject::id_t id) const
{
    if (game_object_storage.find(id) == game_object_storage.end())
    {
        return std::nullopt;
    }
    return game_object_storage.at(id).get();
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

    // TODO: update systems (think of a good spot where)
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