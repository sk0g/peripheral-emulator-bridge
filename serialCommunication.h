
#include <string>
#include <vector>
#include <deque>

using std::deque, std::string;

namespace SerialCommunication
{
    extern deque<string> commandsRead;
    extern deque<string> commandsToWrite;

    // input/ serial reads
    bool canReadMessage();

    string popReadMessage();

    void addReadMessage( const string& message );

    // outputs/ serial writes
    void addMessageToWrite( const string& message );

    string popMessageToWrite();

    bool hasMessageToWrite();
};
