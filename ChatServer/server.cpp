#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <algorithm>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 54000
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

using namespace std;

vector<pair<SOCKET, string>> clients; // Vector to store clients with their names
mutex clients_mutex;

// Broadcast a message to all connected clients
void broadcast(const string &message, SOCKET sender)
{
    lock_guard<mutex> lock(clients_mutex);
    for (auto &client : clients)
    {
        if (client.first != sender)
        {
            send(client.first, message.c_str(), message.size(), 0);
        }
    }
}

// Handle a single client connection
void handle_client(SOCKET client_socket)
{
    char buffer[BUFFER_SIZE];
    string client_name;

    // Get client name
    // send(client_socket, "Enter your name: ", 17, 0);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0)
    {
        client_name = string(buffer, bytes_received);
        lock_guard<mutex> lock(clients_mutex);
        clients.push_back({client_socket, client_name});

        cout << "New client changed their name to " << client_name << "\n";
    }
    while (true)
    {
        ZeroMemory(buffer, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            cout << client_name << " disconnected.\n";
            break;
        }

        string message = client_name + ": " + string(buffer, bytes_received);
        cout << "Received: " << message << "\n";

        broadcast(message, client_socket);
    }

    // Remove client from list
    {
        lock_guard<mutex> lock(clients_mutex);
        clients.erase(remove_if(clients.begin(), clients.end(),
                                [client_socket](const pair<SOCKET, string> &client)
                                {
                                    return client.first == client_socket;
                                }),
                      clients.end());
    }

    closesocket(client_socket);
}

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, MAX_CLIENTS);

    cout << "Chat server started on port " << PORT << "\n";

    while (true)
    {
        sockaddr_in client_addr{};
        int client_size = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (sockaddr *)&client_addr, &client_size);

        thread(handle_client, client_socket).detach();
        cout << "New client connected\n";
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
