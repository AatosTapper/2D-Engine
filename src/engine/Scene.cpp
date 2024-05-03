#include "Scene.h"

#include <cassert>

void Scene::add_game_object(std::unique_ptr<GameObject> &obj)
{
    assert(obj && "Cannot add an invalid game object to a scene");
    game_object_storage[obj->get_id()] = std::move(obj);
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
    game_object_storage.erase(id);
}