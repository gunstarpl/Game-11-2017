#pragma once

#include "Precompiled.hpp"

// Forward declarations.
namespace Scripting
{
    class State;
}

/*
    Script Bindings
*/

namespace Game
{
    namespace ScriptBindings
    {
        // Register structure that will hold references that will be bound.
        struct References
        {
            References();
        };

        // Registers all script bindings.
        bool Register(Scripting::State* state, const References& references);
    }
}

/*
    Entity Handle Bindings
*/

namespace Game
{
    // Forwatd declarations.
    struct EntityHandle;

    namespace ScriptBindings
    {
        namespace EntityHandle
        {
            // Registers a type metatable.
            bool Register(Scripting::State& state);

            // Metatable methods.
            int New(lua_State* state);
            int Index(lua_State* state);
            int NewIndex(lua_State* state);

            // Type helper functions.
            Game::EntityHandle* Push(lua_State* state);
            Game::EntityHandle* Push(lua_State* state, const Game::EntityHandle& object);
            Game::EntityHandle* Check(lua_State* state, int index);
        }
    }
}
