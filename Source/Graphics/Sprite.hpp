#pragma once

#include "Precompiled.hpp"

/*
    Graphics Sprite

    Structure that defines a textured quad. Consists of two parts - information
    that can be shared between different instances of sprites and data that
    is unique for each sprite. This is done to support efficient sprite
    rendering using geometry instancing.

    void ExampleGraphicsSprite(const Texture* texture)
    {
        // Get texture size.
        float width = texture->GetWidth();
        float height = texture->GetHeight();

        // Define a sprite in two parts.
        Graphics::Sprite sprite;
        sprite.info.texture = texture;
        sprite.info.transparent = true;
        sprite.info.filter = false;
        sprite.data.transform = glm::mat4(1.0f);
        sprite.data.rectangle = glm::vec4(0.0f, 0.0f, width, height);
        sprite.data.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
*/

namespace Graphics
{
    // Forward declarations.
    class Texture;

    // Sprite structure.
    struct Sprite
    {
        // Info structure shared per batch.
        struct Info
        {
            Info();

            bool operator==(const Info& other) const;
            bool operator!=(const Info& other) const;

            const Texture* texture;
            bool transparent;
            bool filter;
        } info;

        // Data structure of each sprite.
        struct Data
        {
            Data();

            glm::mat4 transform;
            glm::vec4 rectangle;
            glm::vec4 color;
        } data;
    };
}
