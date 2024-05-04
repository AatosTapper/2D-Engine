#pragma once

#include <memory>

#include "Scene.h"
#include "Window.h"
#include "rendering/Camera.h"

class Engine
{
public:
    Engine(int _fps_cap);

    void set_window(Window *_window);
    void set_camera(Camera *_camera);
    void set_scene(Scene *_scene);

    void run();

    static Window *get_window() { return window; }
    static Camera *get_camera() { return camera; }
    static Scene *get_scene() { return current_scene; }

private:
    static Window *window;
    static Camera *camera;
    static Scene *current_scene;

    int fps_cap;
};