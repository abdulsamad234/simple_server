#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    char *directory;
    char *passwordFile;
    char *portNumber;
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

    cout << "Directory: " << directory;
    cout << "Port: " << portNumber;
    cout << "Password file: " << passwordFile;

    return 0;
}