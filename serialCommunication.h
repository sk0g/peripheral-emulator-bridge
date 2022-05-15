
#include <string>
#include <vector>
#include <deque>

using std::deque, std::string;

class serialCommunication
{
private:
    deque<string> commandsRead;
    deque<string> commandsToWrite;

public:


public:
    bool canReadMessage();

    string readMessage();

    void writeMessage( string message );

private:
    void startCommunication();

    void addReadMessage( string message );

    string serialRead();

    void serialWrite( string message );
};
