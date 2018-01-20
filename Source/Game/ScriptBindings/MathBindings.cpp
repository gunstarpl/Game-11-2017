#include "Precompiled.hpp"
#include "MathBindings.hpp"
#include "Scripting/State.hpp"
using namespace Game;

/*
    Vector 2D Bindings
*/

bool ScriptBindings::Vec2::Register(Scripting::State& state)
{
    Assert(state.IsValid(), "Invalid scripting state!");

    // Create a class metatable.
    luaL_newmetatable(state, "Vec2");

    lua_pushcfunction(state, ScriptBindings::Vec2::New);
    lua_setfield(state, -2, "New");

    lua_pushcfunction(state, ScriptBindings::Vec2::Index);
    lua_setfield(state, -2, "__index");

    lua_pushcfunction(state, ScriptBindings::Vec2::NewIndex);
    lua_setfield(state, -2, "__newindex");

    lua_pushcfunction(state, ScriptBindings::Vec2::Add);
    lua_setfield(state, -2, "__add");

    lua_pushcfunction(state, ScriptBindings::Vec2::Subtract);
    lua_setfield(state, -2, "__sub");

    lua_pushcfunction(state, ScriptBindings::Vec2::Multiply);
    lua_setfield(state, -2, "__mul");

    lua_pushcfunction(state, ScriptBindings::Vec2::Divide);
    lua_setfield(state, -2, "__div");

    lua_pushcfunction(state, ScriptBindings::Vec2::Equals);
    lua_setfield(state, -2, "__eq");

    lua_pushcfunction(state, ScriptBindings::Vec2::Length);
    lua_setfield(state, -2, "Length");

    lua_pushcfunction(state, ScriptBindings::Vec2::LengthSqr);
    lua_setfield(state, -2, "LengthSqr");

    lua_pushcfunction(state, ScriptBindings::Vec2::Truncate);
    lua_setfield(state, -2, "Truncate");

    lua_pushcfunction(state, ScriptBindings::Vec2::Normalize);
    lua_setfield(state, -2, "Normalize");

    // Create an inner metatable.
    lua_newtable(state);

    lua_pushcfunction(state, ScriptBindings::Vec2::Call);
    lua_setfield(state, -2, "__call");

    lua_setmetatable(state, -2);

    // Register as a global table.
    lua_setglobal(state, "Vec2");

    return true;
}

glm::vec2* ScriptBindings::Vec2::Push(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a new userdata object.
    void* memory = lua_newuserdata(state, sizeof(glm::vec2));
    Assert(memory != nullptr, "Could not allocate an userdata memory!");

    auto* instance = new (memory) glm::vec2();
    Assert(instance != nullptr, "Could not construct an userdata instance!");

    // Set the object's metatable.
    luaL_getmetatable(state, "Vec2");
    lua_setmetatable(state, -2);

    return instance;
}

glm::vec2* ScriptBindings::Vec2::Push(lua_State* state, const glm::vec2& object)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Create a new userdata object.
    void* memory = lua_newuserdata(state, sizeof(glm::vec2));
    Assert(memory != nullptr, "Could not allocate an userdata memory!");

    auto* instance = new (memory) glm::vec2(object);
    Assert(instance != nullptr, "Could not construct an userdata instance!");

    // Set the object's metatable.
    luaL_getmetatable(state, "Vec2");
    lua_setmetatable(state, -2);

    return instance;
}

glm::vec2* ScriptBindings::Vec2::Check(lua_State* state, int index)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get the userdata object.
    void* memory = luaL_checkudata(state, index, "Vec2");
    Assert(memory != nullptr, "Could not get an userdata memory!");

    auto* instance = reinterpret_cast<glm::vec2*>(memory);
    Assert(instance != nullptr, "Could not get an userdata instance!");

    return instance;
}

int ScriptBindings::Vec2::New(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Push a new instance.
    auto* vector = Vec2::Push(state);
    vector->x = (float)luaL_optnumber(state, 1, 0.0);
    vector->y = (float)luaL_optnumber(state, 2, 0.0);

    return 1;
}

int ScriptBindings::Vec2::Call(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Push a new instance.
    auto* vector = Vec2::Push(state);
    vector->x = (float)luaL_optnumber(state, 2, 0.0);
    vector->y = (float)luaL_optnumber(state, 3, 0.0);

    return 1;
}

int ScriptBindings::Vec2::Index(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Return the property.
    glm::vec2* vector = Vec2::Check(state, 1);
    std::string key = luaL_checkstring(state, 2);

    if(key == "x")
    {
        lua_pushnumber(state, vector->x);
        return 1;
    }
    else if(key == "y")
    {
        lua_pushnumber(state, vector->y);
        return 1;
    }
    else
    {
        // Push a metatable function.
        lua_getmetatable(state, 1);
        lua_pushvalue(state, 2);
        lua_rawget(state, -2);
        lua_remove(state, -2);
        return 1;
    }
}

int ScriptBindings::Vec2::NewIndex(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Set the property.
    glm::vec2* vector = Vec2::Check(state, 1);
    std::string key = luaL_checkstring(state, 2);

    if(key == "x")
    {
        vector->x = (float)luaL_checknumber(state, 3);
        return 0;
    }
    else if(key == "y")
    {
        vector->y = (float)luaL_checknumber(state, 3);
        return 0;
    }

    return 0;
}

int ScriptBindings::Vec2::Add(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);
    glm::vec2* argument = Vec2::Check(state, 2);

    // Push the result.
    glm::vec2* result = Vec2::Push(state);
    *result = *vector + *argument;

    return 1;
}

int ScriptBindings::Vec2::Subtract(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);
    glm::vec2* argument = Vec2::Check(state, 2);

    // Push the result.
    glm::vec2* result = Vec2::Push(state);
    *result = *vector - *argument;

    return 1;
}

int ScriptBindings::Vec2::Multiply(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);
    lua_Number argument = luaL_checknumber(state, 2);

    // Push the result.
    glm::vec2* result = Vec2::Push(state);
    *result = *vector * (float)argument;

    return 1;
}

int ScriptBindings::Vec2::Divide(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);
    lua_Number argument = luaL_checknumber(state, 2);

    // Push the result.
    glm::vec2* result = Vec2::Push(state);
    *result = *vector / (float)argument;

    return 1;
}

int ScriptBindings::Vec2::Equals(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);
    glm::vec2* argument = Vec2::Check(state, 2);

    // Push the result.
    bool result = *vector == *argument;
    lua_pushboolean(state, result);

    return 1;
}

int ScriptBindings::Vec2::Length(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);

    // Push the result.
    float result = glm::length(*vector);
    lua_pushnumber(state, result);

    return 1;
}

int ScriptBindings::Vec2::LengthSqr(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);

    // Push the result.
    float result = glm::length2(*vector);
    lua_pushnumber(state, result);

    return 1;
}

int ScriptBindings::Vec2::Truncate(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);
    float length = (float)luaL_checknumber(state, 2);

    // Push the result.
    glm::vec2* result = Vec2::Push(state);
    *result = glm::normalize(*vector) * glm::min(glm::length(*vector), length);

    return 1;
}

int ScriptBindings::Vec2::Normalize(lua_State* state)
{
    Assert(state != nullptr, "Scripting state is nullptr!");

    // Get arguments from the stack.
    glm::vec2* vector = Vec2::Check(state, 1);

    // Push the result.
    glm::vec2* result = Vec2::Push(state);
    *result = glm::normalize(*vector);

    return 1;
}