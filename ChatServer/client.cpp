#include <iostream>
#include <thread>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 54000
#define BUFFER_SIZE 1024

using namespace std;

void receive_messages(SOCKET sock)
{
    char buffer[BUFFER_SIZE];
    while (true)
    {
        ZeroMemory(buffer, BUFFER_SIZE);
        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            cout << "Disconnected from server.\n";
            break;
        }
        cout << "[Message] " << string(buffer, bytes_received) << "\n";
    }
}

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr *)&server_addr, sizeof(server_addr));
    cout << "Connected to chat server.\n";

    // Get the user's name
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    send(sock, name.c_str(), name.size(), 0);

    thread(receive_messages, sock).detach();

    string input;
    while (true)
    {
        getline(cin, input);
        if (input == "/exit")
            break;
        send(sock, input.c_str(), input.size(), 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
