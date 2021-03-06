#include "Precompiled.hpp"
#include "GameBindings.hpp"
#include "Scripting/State.hpp"
#include "Scripting/Helpers.hpp"
#include "Game/EntityHandle.hpp"
#include "Game/TransformComponent.hpp"
#include "Game/ComponentSystem.hpp"
using namespace Game;

/*
    Entity Handle Bindings
*/

bool ScriptBindings::EntityHandle::Register(Scripting::State& state)
{
    Assert(state.IsValid(), "Invalid scripting state!");

    // Create a stack cleanup guard.
    Scripting::StackGuard guard(state);

    // Create a class metatable.
    luaL_newmetatable(state, typeid(Game::EntityHandle).name());

    lua_pushcfunction(state, ScriptBindings::EntityHandle::New);
    lua_setfield(state, -2, "New");

    lua_pushcfunction(state, ScriptBindings::EntityHandle::Index);
    lua_setfield(state, -2, "__index");

    lua_pushcfunction(state, ScriptBindings::EntityHandle::NewIndex);
    lua_setfield(state, -2, "__newindex");

    // Create an inner metatable.
    lua_newtable(state);

    lua_pushcfunction(state, ScriptBindings::EntityHandle::New);
    lua_setfield(state, -2, "__call");

    lua_setmetatable(state, -2);

    // Register as a global variable.
    Scripting::SetGlobalField(state, "Game.EntityHandle", Scripting::StackValue(-1), true);

    return true;
}

int ScriptBindings::EntityHandle::New(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a scripting state proxy.
    Scripting::State stateProxy(state);

    // Push a new object.
    Scripting::Push<Game::EntityHandle>(stateProxy);

    return 1;
}

int ScriptBindings::EntityHandle::Index(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a scripting state proxy.
    Scripting::State stateProxy(state);

    // Get arguments from the stack.
    Game::EntityHandle* handle = Scripting::Check<Game::EntityHandle>(stateProxy, 1);
    std::string key = Scripting::Check<std::string>(stateProxy, 2);

    // Return a property.
    if(key == "identifier")
    {
        Scripting::Push<Game::EntityHandle::ValueType>(stateProxy, handle->identifier);
        return 1;
    }
    else if(key == "version")
    {
        Scripting::Push<Game::EntityHandle::ValueType>(stateProxy, handle->version);
        return 1;
    }
    else
    {
        Scripting::Push<std::nullptr_t>(stateProxy);
        return 1;
    }
}

int ScriptBindings::EntityHandle::NewIndex(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a scripting state proxy.
    Scripting::State stateProxy(state);

    // Get arguments from the stack.
    Game::EntityHandle* handle = Scripting::Check<Game::EntityHandle>(stateProxy, 1);
    std::string key = Scripting::Check<std::string>(stateProxy, 2);

    // Set a property.
    if(key == "identifier")
    {
        handle->identifier = Scripting::Check<Game::EntityHandle::ValueType>(stateProxy, 3);
        return 0;
    }
    else if(key == "version")
    {
        handle->version = Scripting::Check<Game::EntityHandle::ValueType>(stateProxy, 3);
        return 0;
    }

    return 0;
}

/*
    Transform Component Bindings
*/

bool ScriptBindings::TransformComponent::Register(Scripting::State& state)
{
    Assert(state.IsValid(), "Invalid scripting state!");

    // Create a stack cleanup guard.
    Scripting::StackGuard guard(state);

    // Create a class metatable.
    luaL_newmetatable(state, typeid(Game::Components::Transform).name());

    lua_pushliteral(state, "__index");
    lua_pushvalue(state, -2);
    lua_rawset(state, -3);

    lua_pushcfunction(state, ScriptBindings::TransformComponent::GetPosition);
    lua_setfield(state, -2, "GetPosition");

    lua_pushcfunction(state, ScriptBindings::TransformComponent::SetPosition);
    lua_setfield(state, -2, "SetPosition");

    // Register as a global variable.
    Scripting::SetGlobalField(state, "Game.Components.Transform", Scripting::StackValue(-1), true);

    return true;
}

int ScriptBindings::TransformComponent::GetPosition(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a scripting state proxy.
    Scripting::State stateProxy(state);

    // Get arugments from the stack.
    Game::Components::Transform* transform = *Scripting::Check<Game::Components::Transform*>(stateProxy, 1);

    // Push a position vector.
    Scripting::Push<glm::vec3>(stateProxy, transform->GetPosition());

    return 1;
}

int ScriptBindings::TransformComponent::SetPosition(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a scripting state proxy.
    Scripting::State stateProxy(state);

    // Get arugments from the stack.
    Game::Components::Transform* transform = *Scripting::Check<Game::Components::Transform*>(stateProxy, 1);
    glm::vec3* position = Scripting::Check<glm::vec3>(stateProxy, 2);

    // Set the transform position.
    transform->SetPosition(*position);

    return 0;
}

/*
    Component System Bindings
*/

bool ScriptBindings::ComponentSystem::Register(Scripting::State& state, Game::ComponentSystem* reference)
{
    Assert(state.IsValid(), "Invalid scripting state!");

    // Create a stack cleanup guard.
    Scripting::StackGuard guard(state);

    // Create a type metatable.
    luaL_newmetatable(state, typeid(Game::ComponentSystem).name());

    lua_pushliteral(state, "__index");
    lua_pushvalue(state, -2);
    lua_rawset(state, -3);

    lua_pushcfunction(state, ScriptBindings::ComponentSystem::GetTransform);
    lua_setfield(state, -2, "GetTransform");

    // Push a reference to the component system.
    Scripting::Push<Game::ComponentSystem*>(state, reference);

    // Register as a global variable.
    Scripting::SetGlobalField(state, "Game.ComponentSystem", Scripting::StackValue(-1), true);

    return true;
}

int ScriptBindings::ComponentSystem::GetTransform(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a scripting state proxy.
    Scripting::State stateProxy(state);

    // Push an input system reference as the first argument.
    Scripting::GetGlobalField(stateProxy, "Game.ComponentSystem", false);
    Scripting::Insert(stateProxy, 1);

    // Get arguments from the stack.
    Game::ComponentSystem* componentSystem = *Scripting::Check<Game::ComponentSystem*>(stateProxy, 1);
    Game::EntityHandle* entityHandle = Scripting::Check<Game::EntityHandle>(stateProxy, 2);

    // Retrieve a transform component.
    Game::Components::Transform* transform = componentSystem->Lookup<Game::Components::Transform>(*entityHandle);

    // Push a reference to the transform component.
    Scripting::Push<Game::Components::Transform*>(stateProxy, transform);

    return 1;
}
