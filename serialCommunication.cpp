
#include "serialCommunication.h"


bool serialCommunication::canReadMessage()
{
    return commandsRead.size() > 0;
}

string serialCommunication::readMessage()
{
    std::string message = commandsRead.front();
    commandsRead.pop_front();
    return message;
}

void serialCommunication::addReadMessage( string message )
{
    commandsRead.push_back( message );
}

void serialCommunication::writeMessage( string message )
{
    commandsToWrite.push_back( message );
}

void serialCommunication::startCommunication()
{
    return;
}

string serialCommunication::serialRead()
{
    return std::string();
}

void serialCommunication::serialWrite( string message )
{

}
