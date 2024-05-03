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

    game_object_storage.at(id)->on_create();
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
    game_object_storage.at(id)->on_destroy();
    game_object_storage.erase(id);
    current_game_objects.erase(
        std::remove(current_game_objects.begin(), current_game_objects.end(), id), 
        current_game_objects.end()
    );
}

void Scene::update()
{
    // WARNING, this doesn't work if something get's deleted
    for (auto id : current_game_objects)
    {
        game_object_storage.at(id)->on_update();
    }
}