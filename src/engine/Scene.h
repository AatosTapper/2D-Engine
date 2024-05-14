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
    void add_system(Ptr<System> system);

    [[nodiscard]] std::optional<Ptr<GameObject>> get_game_object(GameObject::id_t id) const; // this reference becomes invalid after current frame
    [[nodiscard]] std::vector<Ptr<GameObject>> get_all_game_objects() const;
    [[nodiscard]] std::vector<Ptr<GameObject>> get_all_game_objects_with_flags(ObjectFlags flag) const;
    [[nodiscard]] std::vector<Ptr<GameObject>> get_all_game_objects_except_flags(ObjectFlags flag) const;

    void delete_game_object(GameObject::id_t id); // defers the delete until the start of the next frame

    void update();

private:
    std::unordered_map<GameObject::id_t, std::unique_ptr<GameObject>> game_object_storage;
    std::vector<GameObject::id_t> current_game_objects;
    std::vector<GameObject::id_t> delete_queue;

    std::vector<Ptr<System>> game_systems;

    void handle_deletions();
};
