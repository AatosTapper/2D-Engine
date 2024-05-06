#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <optional> // google this if you intend to use "get_game_object()""

#include "GameObject.h"
#include "System.h"

#define CREATE_GAME_OBJECT(T) std::make_unique<T>()
#define CREATE_GAME_OBJECT_WITH_ARGS(T, args) std::make_unique<T>(args)

class Scene
{
public:
    // the ownership of "obj" is moved to the Scene
    void add_game_object(std::unique_ptr<GameObject> obj);

    // this pointer becomes invalid after current frame
    std::optional<GameObject*> get_game_object(GameObject::id_t id) const;

    // defers the delete until the start of the next frame
    void delete_game_object(GameObject::id_t id);

    void update();

    void add_system(System *system);

private:
    std::unordered_map<GameObject::id_t, std::unique_ptr<GameObject>> game_object_storage;
    std::vector<GameObject::id_t> current_game_objects;
    std::vector<GameObject::id_t> delete_queue;

    std::vector<System*> game_systems;

    void handle_deletions();
};
