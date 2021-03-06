#include "Precompiled.hpp"
#include "Output.hpp"
#include "Message.hpp"
#include "Format.hpp"
#include "Sink.hpp"
using namespace Logger;

/*
    File Output
*/

FileOutput::FileOutput()
{
}

FileOutput::~FileOutput()
{
    // Close the file stream.
    if(m_file.is_open())
    {
        // Write session end.
        m_file << DefaultFormat::ComposeSessionEnd();
        m_file.flush();

        // Close the file.
        m_file.close();
    }
}

bool FileOutput::Open(std::string filename)
{
    // Check if the file stream is already open.
    Verify(!m_file.is_open(), "File stream is already open!");

    // Open the file stream for writing.
    m_file.open(filename);

    if(!m_file.is_open())
    {
        LogError() << "Could not open a log file!";
        return false;
    }

    // Write session start.
    m_file << DefaultFormat::ComposeSessionStart();
    m_file.flush();

    // Success!
    return true;
}

void FileOutput::Write(const Message& message, const SinkContext& context)
{
    Verify(m_file.is_open(), "File stream is not open!");

    // Write a log message.
    m_file << DefaultFormat::ComposeMessage(message, context);
    m_file.flush();
}

/*
    Console Output
*/

ConsoleOutput::ConsoleOutput()
{
    // Write session start.
    std::cout << DefaultFormat::ComposeSessionStart();
    std::cout.flush();
}

ConsoleOutput::~ConsoleOutput()
{
    // Write session end.
    std::cout << DefaultFormat::ComposeSessionStart();
    std::cout.flush();
}

void ConsoleOutput::Write(const Message& message, const SinkContext& context)
{
    // Write a log message.
    std::cout << DefaultFormat::ComposeMessage(message, context);
    std::cout.flush();
}

/*
    Debugger Output
*/

DebuggerOutput::DebuggerOutput()
{
}

DebuggerOutput::~DebuggerOutput()
{
}

void DebuggerOutput::Write(const Message& message, const SinkContext& context)
{
    #ifdef WIN32
        // Check if debugger is attached.
        if(!IsDebuggerPresent())
            return;

        // Write a log message.
        std::string output = DefaultFormat::ComposeMessage(message, context);
        OutputDebugStringA(output.c_str());
    #endif
}
