#pragma once

#include "Precompiled.hpp"
#include "Component.hpp"

// Forward declarations.
namespace Graphics
{
    class Texture;
}

namespace Game
{
    class RenderSystem;
}

/*
    Render Component
*/

namespace Game
{
    namespace Components
    {
        // Forward declarations.
        class Transform;

        // Render component class.
        class Render : public Component
        {
        public:
            // Type declarations.
            typedef std::shared_ptr<const Graphics::Texture> TexturePtr;

            // Friend declarations.
            friend RenderSystem;

        public:
            Render();
            ~Render();

            // Calculates the blend of diffuse and emmisive colors.
            glm::vec4 CalculateColor() const;

            // Sets the texture.
            void SetTexture(TexturePtr texture);

            // Sets the rectangle.
            void SetRectangle(const glm::vec4& rectangle);
            void SetRectangle(float x, float y, float width, float height);
            void SetRectangleFromTexture();

            // Set the diffuse color.
            void SetDiffuseColor(const glm::vec3& color);
            void SetDiffuseColor(const glm::vec4& color);
            void SetDiffuseColor(float r, float g, float b, float a = 1.0f);

            // Set the emissive color.
            void SetEmissiveColor(const glm::vec3& color);
            void SetEmissiveColor(const glm::vec4& color);
            void SetEmissiveColor(float r, float g, float b, float a = 1.0f);

            // Set the emissive power.
            void SetEmissivePower(float power);

            // Sets transparency state.
            void SetTransparent(bool transparent);

            // Gets the texture.
            const TexturePtr& GetTexture() const;

            // Gets the rectangle.
            const glm::vec4& GetRectangle() const;

            // Gets the diffuse color.
            const glm::vec4& GetDiffuseColor() const;

            // Gets the emissive color.
            const glm::vec4& GetEmissiveColor() const;

            // Gets the emissive power.
            float GetEmissivePower() const;

            // Checks if is transparent.
            bool IsTransparent() const;

            // Gets the transform component.
            Transform* GetTransform();

        private:
            // Texture resource.
            TexturePtr m_texture;
            glm::vec4 m_rectangle;

            // Render parameters.
            glm::vec2 m_offset;
            glm::vec4 m_diffuseColor;
            glm::vec4 m_emissiveColor;
            float m_emissivePower;
            bool m_transparent;

            // Entity components.
            Transform* m_transform;
        };
    }
}
