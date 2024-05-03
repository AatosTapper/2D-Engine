#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <optional> // google this if you intend to use "get_game_object()""

#include "GameObject.h"

class Scene
{
public:
    // the ownership of "obj" is moved to the Scene
    void add_game_object(std::unique_ptr<GameObject> &obj);

    // THIS POINTER BECOMES INVALID AFTER CURRENT FRAME
    // DON'T STORE IT ANYWHERE
    std::optional<GameObject*> get_game_object(GameObject::id_t id) const;

    void delete_game_object(GameObject::id_t id);

    void update();

private:
    std::unordered_map<GameObject::id_t, std::unique_ptr<GameObject>> game_object_storage;
    std::vector<GameObject::id_t> current_game_objects;
};
