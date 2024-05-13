#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <optional> // google this if you intend to use "get_game_object()""

#include "engine/GameObject.h"
#include "engine/System.h"
#include "Ref.h"

class Scene
{
public:
    Scene();

    void add_game_object(std::unique_ptr<GameObject> obj);
    std::optional<Ptr<GameObject>> get_game_object(GameObject::id_t id) const; // this reference becomes invalid after current frame
    void delete_game_object(GameObject::id_t id); // defers the delete until the start of the next frame

    void update();

    void add_system(Ptr<System> system);

private:
    std::unordered_map<GameObject::id_t, std::unique_ptr<GameObject>> game_object_storage;
    std::vector<GameObject::id_t> current_game_objects;
    std::vector<GameObject::id_t> delete_queue;

    std::vector<Ptr<System>> game_systems;

    void handle_deletions();
};
