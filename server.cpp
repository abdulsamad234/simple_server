#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv)
{
    string directory;
    string passwordFile;
    string portNumber;
    if (argc < 7)
    {
        cout << "Usage: ./ftpserver -d <directory> -p <port> -u <password file>";
        return 1;
    }
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp("-d", argv[i]) == 0)
        {
            directory = argv[i + 1];
        }
        if (strcmp("-p", argv[i]) == 0)
        {
            portNumber = argv[i + 1];
        }
        if (strcmp("-u", argv[i]) == 0)
        {
            passwordFile = argv[i + 1];
        }
    }

    int socketfd;

    struct sockaddr_in serverAddress;

    int clientSocketetId;

    struct sockaddr_in clientAddress;

    socklen_t address_size;

    pid_t childProcessId;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0)
    {
        cout << "Error";
        return 1;
    }

    memset(&serverAddress, '\0', sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(stoi(portNumber));

    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(socketfd,
             (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        cout << "Error binding";
        return 1;
    }

    if (listen(socketfd, 10) < 0)
    {
        cout << "Couldn't listen";
        return 1;
    }

    auto addressLength = sizeof(serverAddress);
    int connection = accept(socketfd, (struct sockaddr *)&serverAddress, (socklen_t *)&addressLength);
    if (connection < 0)
    {
        cout << "Failed to grab connection ";
        return 1;
    }

    char buffer[700];
    while (1)
    {
        auto bytesRead = read(connection, buffer, 700);
        cout
            << "The message was: " << buffer;
        string response = "Response!";
        send(connection, response.c_str(), response.size(), 0);
    }

    return 0;
}