#pragma once

#include "Precompiled.hpp"

/*
    System Resource Pool

    Manages an instance pool for a single type of resource.
    See ResourceManager class for more context.

    void ExampleSystemResourcePool()
    {
        // Create a resource pool instance.
        System::ResourcePool<Texture> texturePool;

        // Set a default resource that will be returned on failed loads.
        std::shared_ptr<Texture> defaultTexture = std::make_shared<Texture>();
        texturePool->SetDefault(defaultTexture);

        // Create resources in a scope so they can be released when unused.
        {
            // Load a resource from the pool. Returns an existing resource if exist.
            // Resource type must provide Load(std::string, ...) method for the template.
            std::shared_ptr<const Texture> textureA = texture->Load("Data/Textures/checkerboard.png");

            // This will return the previously loaded resource.
            std::shared_ptr<const Texture> textureB = texture->Load("Data/Textures/checkerboard.png");
        }

        // Release resources that are no longer referenced.
        resourceManager.ReleaseUnused();
    }
*/

namespace System
{
    // Resource pool interface.
    class ResourcePoolInterface
    {
    protected:
        ResourcePoolInterface()
        {
        }

    public:
        virtual ~ResourcePoolInterface()
        {
        }

        virtual void ReleaseUnused() = 0;
    };

    // Resource pool class.
    template<typename Type>
    class ResourcePool : public ResourcePoolInterface
    {
    public:
        // Type declarations.
        typedef std::shared_ptr<Type>                        ResourcePtr;
        typedef std::unordered_map<std::string, ResourcePtr> ResourceList;
        typedef typename ResourceList::value_type            ResourceListPair;

    public:
        ResourcePool();
        ~ResourcePool();

        // Sets the default resource.
        void SetDefault(std::shared_ptr<const Type> resource);

        // Gets the default resource.
        std::shared_ptr<const Type> GetDefault() const;

        // Loads a resource by name.
        // Name argument does not have to refer to a file path.
        // Resource type must have Load(std::string, ...) method implemented.
        template<typename... Arguments>
        std::shared_ptr<const Type> Load(std::string name, Arguments... arguments);

        // Releases unused resources.
        void ReleaseUnused();

        // Releases all resources.
        void ReleaseAll();

    private:
        // Default resource.
        std::shared_ptr<const Type> m_default;

        // List of resources.
        ResourceList m_resources;
    };

    // Template definitions.
    template<typename Type>
    ResourcePool<Type>::ResourcePool() :
        m_default(std::make_shared<Type>())
    {
    }

    template<typename Type>
    ResourcePool<Type>::~ResourcePool()
    {
        // Release all resources now.
        this->ReleaseAll();
    }

    template<typename Type>
    void ResourcePool<Type>::SetDefault(std::shared_ptr<const Type> resource)
    {
        Verify(it->second != nullptr, "Default resource cannot be null!");

        m_default = resource;
    }

    template<typename Type>
    std::shared_ptr<const Type> ResourcePool<Type>::GetDefault() const
    {
        Verify(it->second != nullptr, "Default resource is null!");

        return m_default;
    }

    template<typename Type>
    template<typename... Arguments>
    std::shared_ptr<const Type> ResourcePool<Type>::Load(std::string name, Arguments... arguments)
    {
        // Return an existing resource if loaded.
        auto it = m_resources.find(name);
        if(it != m_resources.end())
        {
            Assert(it->second != nullptr, "Found resource is null!");

            // Return found resource.
            return it->second;
        }

        // Create and load a new resource instance.
        std::shared_ptr<Type> resource = std::make_shared<Type>();
        if(!resource->Load(name, std::forward<Arguments>(arguments)...))
            return m_default;

        // Add resource to the list.
        auto result = m_resources.emplace(name, std::move(resource));
        Assert(result.second, "Failed to emplace a new resource in the resource pool!");

        // Return the resource pointer.
        return result.first->second;
    }

    template<typename Type>
    void ResourcePool<Type>::ReleaseUnused()
    {
        // Release unused resources.
        auto it = m_resources.begin();
        while(it != m_resources.end())
        {
            if(it->second.use_count() == 1)
            {
                // Retrieve the name to print it later.
                std::string name = it->first;

                // Release the resource.
                it = m_resources.erase(it);

                // Print a log message.
                LogInfo() << "Released \"" << name << "\" resource.";
            }
            else
            {
                ++it;
            }
        }
    }

    template<typename Type>
    void ResourcePool<Type>::ReleaseAll()
    {
        // Release all resources.
        auto it = m_resources.begin();
        while(it != m_resources.end())
        {
            // Retrieve the name to print it later.
            std::string name = it->first;

            // Release the resource.
            it = m_resources.erase(it);

            // Print a log message.
            LogInfo() << "Released \"" << name << "\" resource.";
        }

        Assert(m_resources.empty(), "Resource pool is not empty after releasing all resources!");
    }
}
