
#include <iostream>
#include "serialCommunication.h"

namespace SerialCommunication
{
    deque<string> commandsRead;
    deque<string> commandsToWrite;

    bool canReadMessage()
    {
        return !commandsRead.empty();
    }

    string popReadMessage()
    {
        std::string message = commandsRead.front();
        commandsRead.pop_front();
        return message;
    }

    void addReadMessage( const string &message )
    {
        commandsRead.push_back( message );
    }

    bool hasMessageToWrite()
    {
        return !commandsToWrite.empty();
    }

    string popMessageToWrite()
    {
        std::string message = commandsToWrite.front();
        commandsToWrite.pop_front();
        return message;
    }

    void addMessageToWrite( const string &message )
    {
        commandsToWrite.push_back( message );
    }
}