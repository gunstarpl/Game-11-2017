#pragma once

#include "Precompiled.hpp"

/*
    System Window

    Creates and manages an application window with OpenGL context.
    Supports multiple windows and OpenGL contextes.

    void ExampleSystemWindow()
    {
        // Describe a window.
        WindowInfo windowInfo;
        windowInfo.width = 1024;
        windowInfo.height = 576;

        // Open a new window.
        System::Window window;
        if(!window.Open(windowInfo))
            return;

        // Run a window loop.
        while(window.IsOpen())
        {
            window.ProcessEvents();

            // Update and draw here.

            window.Present();
        }
    }

    void ExampleEvents(Class& instance)
    {
        // Create an event receiver with a signature matching the dispatcher.
        Receiver<void(const Window::Events::KeyboardKey&)> receiver;

        // Bind a class method with the same signature as both receiver and dispatcher.
        receiver.Bind<Instance, &Instance::HandleWindowEvent>(&instance);

        // Subscribe to window's event dispatcher.
        receiver.Subscribe(window.events.keyboardKey);
    }
*/

namespace System
{
    // Window info structure.
    struct WindowInfo
    {
        WindowInfo();

        std::string title;
        int width;
        int height;
        bool vsync;

        int minWidth;
        int minHeight;
        int maxWidth;
        int maxHeight;
    };

    // Window class.
    class Window : private NonCopyable
    {
    public:
        Window();
        ~Window();

        // Open the window.
        bool Open(const WindowInfo& info = WindowInfo());

        // Makes window's context current.
        void MakeContextCurrent();

        // Processes window events.
        void ProcessEvents();

        // Presents backbuffer's content in the window.
        void Present();

        // Closes the window.
        void Close();

        // Checks if the window is open.
        bool IsOpen() const;

        // Checks if the window is focused.
        bool IsFocused() const;

        // Sets the window's title.
        void SetTitle(std::string title);

        // Gets the window's title.
        std::string GetTitle() const;

        // Gets the window's width.
        int GetWidth() const;

        // Gets the window's height.
        int GetHeight() const;

        // Gets the window's private handle.
        GLFWwindow* GetPrivateHandle();

    public:
        // Window events.
        struct Events
        {
            // Move event.
            struct Move
            {
                int x;
                int y;
            };

            Dispatcher<void(const Move&)> move;

            // Resize event.
            struct Resize
            {
                int width;
                int height;
            };

            Dispatcher<void(const Resize&)> resize;

            // Focus event.
            struct Focus
            {
                bool focused;
            };

            Dispatcher<void(const Focus&)> focus;

            // Close event.
            struct Close
            {
            };

            Dispatcher<void(const Close&)> close;

            // Keyboard key event.
            struct KeyboardKey
            {
                int key;
                int scancode;
                int action;
                int mods;
            };

            Dispatcher<void(const KeyboardKey&)> keyboardKey;

            // Text input event.
            struct TextInput
            {
                unsigned int character;
            };

            Dispatcher<void(const TextInput&)> textInput;

            // Mouse button event.
            struct MouseButton
            {
                int button;
                int action;
                int mods;
            };

            Dispatcher<void(const MouseButton&)> mouseButton;

            // Mouse scroll event.
            struct MouseScroll
            {
                double offset;
            };

            Dispatcher<void(const MouseScroll&)> mouseScroll;

            // Cursor position event.
            struct CursorPosition
            {
                double x;
                double y;
            };

            Dispatcher<void(const CursorPosition&)> cursorPosition;

            // Cursor enter event.
            struct CursorEnter
            {
                bool entered;
            };

            Dispatcher<void(const CursorEnter&)> cursorEnter;
        } events;

    private:
        // Called when the window gets moved.
        static void MoveCallback(GLFWwindow* window, int x, int y);

        // Called when the window gets resized.
        static void ResizeCallback(GLFWwindow* window, int width, int height);

        // Called when the window gets focused.
        static void FocusCallback(GLFWwindow* window, int focused);

        // Called when the window gets closed.
        static void CloseCallback(GLFWwindow* window);

        // Called when a keyboard key state changes.
        static void KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        // Called when a text character is entered on the keyboard.
        static void TextInputCallback(GLFWwindow* window, unsigned int character);

        // Called when a state of a mouse button changes.
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

        // Called when the mouse scroll moves.
        static void MouseScrollCallback(GLFWwindow* window, double offsetx, double offsety);

        // Called when the mouse cursor moves.
        static void CursorPositionCallback(GLFWwindow* window, double x, double y);

        // Called when the mouse cursor enters or leaves the window.
        static void CursorEnterCallback(GLFWwindow* window, int entered);

    private:
        // Destroy the window handle immediately.
        void DestroyWindow();

    private:
        // Window handle.
        GLFWwindow* m_window;

        // Window title.
        std::string m_title;

        // Intermediate state.
        bool m_sizeChanged;
    };
}
