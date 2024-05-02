#pragma once

class Sprite;
class Shader;

class Renderer
{
public:
    Renderer() = delete;

    static void init();
    static void start_frame();
    static void end_frame();
    static void set_shader(Shader *shader);
    static void draw_sprite(const Sprite &sprite);
};
