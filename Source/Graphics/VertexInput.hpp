#pragma once

#include "Precompiled.hpp"

/*
    Graphics Vertex Input

    Creates a vertex layout that binds vertex buffers to shader inputs on the pipeline.

    void ExampleGraphicsVertexInput()
    {
        // Define the layout of vertex attributes.
        const Graphics::VertexAttribute vertexAttributes[] =
        {
            { &vertexBuffer, Graphics::VertexAttributeTypes::Float2 }, // Position
            { &vertexBuffer, Graphics::VertexAttributeTypes::Float2 }, // Texture
            { &vertexBuffer, Graphics::VertexAttributeTypes::Float4 }, // Color
        };

        Graphics::VertexInputInfo vertexInputInfo;
        vertexInputInfo.attributeCount = Utility::ArraySize(vertexAttributes);
        vertexInputInfo.attributes = &vertexAttributes[0];
    
        // Create a vertex input instance.
        Graphics::VertexInput vertexInput;
        vertexInput.Create(vertexInputInfo);
    
        // Bind vertex array inpuy.
        glBindVertexArray(vertexInput.GetHandle());
    }
*/

namespace Graphics
{
    // Forward declarations.
    class Buffer;

    // Vertex attribute types.
    enum class VertexAttributeTypes
    {
        Invalid,

        Float1,
        Float2,
        Float3,
        Float4,

        Float4x4,

        Count,
    };

    // Vertex attribute structure.
    struct VertexAttribute
    {
        VertexAttribute();
        VertexAttribute(const Buffer* buffer, VertexAttributeTypes type);

        const Buffer* buffer;
        VertexAttributeTypes type;
    };

    // Vertex input info structure.
    struct VertexInputInfo
    {
        VertexInputInfo();
        VertexInputInfo(const VertexAttribute* attributes, int attributeCount);

        const VertexAttribute* attributes;
        int attributeCount;
    };

    // Vertex input class.
    class VertexInput
    {
    public:
        VertexInput();
        ~VertexInput();

        // Initializes the vertex input instance.
        bool Create(const VertexInputInfo& info);

        // Gets the vertex array object handle.
        GLuint GetHandle() const;

        // Checks if instance is valid.
        bool IsValid() const;

    private:
        // Destroys the internal handle.
        void DestroyHandle();

    private:
        // Vertex array handle.
        GLuint m_handle;
    };
}