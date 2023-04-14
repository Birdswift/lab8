#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const char* SERVER_IP = "127.0.0.1";
const int PORT = 54000;
const int BUFFER_SIZE = 1024;

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        cerr << "Failed to create socket!" << endl;
        return EXIT_FAILURE;
    }
    cout << "Client socket created!" << endl;

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddress.sin_port = htons(PORT);

    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "Failed to connect to server!" << endl;
        close(clientSocket);
        return EXIT_FAILURE;
    }
    cout << "Connected to server!" << endl;

    char buffer[BUFFER_SIZE] = {0};
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    cout << "Server: " << buffer << endl;

    string name;
    getline(cin, name);
    const char* nameToSend = name.c_str();
    send(clientSocket, nameToSend, strlen(nameToSend), 0);
    memset(buffer, 0, BUFFER_SIZE);
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    cout << "Server: " << buffer << endl;

    close(clientSocket);

    return EXIT_SUCCESS;
}
