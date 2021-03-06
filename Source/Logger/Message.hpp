#pragma once

#include "Precompiled.hpp"

/*
    Logger Message

    Object that holds a messages along with its metadata.

    void ExampleLoggerMessage(Logger::Sink& sink)
    {
        // Simply use a log macro.
        Log() << "Hello world!";

        // Above macro may equal to the following:
        Logger::Message() message;
        message.SetSource(__FILE__);
        message.SetLine(__LINE__);
        message << "Hello world!";
        sink.Write(message);
    }
*/

namespace Logger
{
    // Message severity.
    struct Severity
    {
        enum Type
        {
            Invalid,

            Info,
            Debug,
            Warning,
            Error,

            Count,
        };
    };

    // Message class.
    class Message : private NonCopyable, public std::ostream
    {
    public:
        Message();
        Message(Message&& other);
        virtual ~Message();

        // Sets the message severity.
        Message& SetSeverity(Severity::Type severity);

        // Sets the message text.
        Message& SetText(const char* text);

        // Sets the message source.
        Message& SetSource(const char* source);

        // Sets the message line.
        Message& SetLine(int line);

        // Gets the message severity.
        Severity::Type GetSeverity() const;

        // Gets the message text.
        std::string GetText() const;

        // Gets the message source.
        std::string GetSource() const;

        // Gets the message line.
        int GetLine() const;

        // Checks if the message is empty.
        bool IsEmpty() const;

    private:
        // Message state.
        Severity::Type m_severity;
        std::stringbuf m_text;
        std::string    m_source;
        int            m_line;
    };
}

/*
    Logger Scoped Message

    Logger message object that writes to a sink at the end of its lifetime.
    Extensively used by Log() macro to write to the sink at the end of scope.
    Using anynomous instantiation, its scope ends at the next semicolon (';').
*/

namespace Logger
{
    // Forward declarations.
    class Sink;

    // Scoped message class.
    class ScopedMessage : public Message
    {
    public:
        ScopedMessage(Sink* sink);
        ScopedMessage(ScopedMessage&& other);
        ~ScopedMessage();

    private:
        // Message sink output.
        Logger::Sink* m_sink;
    };
}
