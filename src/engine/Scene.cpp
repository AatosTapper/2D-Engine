#include "Scene.h"

#include <cassert>

void Scene::add_game_object(std::unique_ptr<GameObject> &obj)
{
    assert(obj && "Cannot add an invalid game object to a scene");
    const GameObject::id_t id = obj->get_id();

    game_object_storage[id] = std::move(obj);
    if (std::find(current_game_objects.begin(), current_game_objects.end(), id) == current_game_objects.end()) 
    {
        current_game_objects.push_back(id);
    }

    game_object_storage.at(id)->on_create(this);
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
    // WARNING, this doesn't work if something get's deleted
    for (auto id : current_game_objects)
    {
        game_object_storage.at(id)->on_update(this);
    }
}

void Scene::handle_deletions()
{
    // first run all on_destroy()s
    for (auto id : delete_queue)
    {
        game_object_storage.at(id)->on_destroy(this);
    }

    // only after running them all can we delete them
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