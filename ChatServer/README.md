Chat Server Project
===================

📌 Project Overview
-------------------

This project implements a **multithreaded chat server** in **C++** using **sockets**, **multithreading (`std::thread`)**, and synchronization mechanisms like **`std::mutex`** and **`std::semaphore`**. The server allows multiple clients to connect and exchange messages in real-time.

Each client has a unique connection to the server, and the server ensures that messages are broadcast to all connected clients in a synchronized manner. The goal of this project is to demonstrate the handling of multiple client connections, message synchronization, and efficient use of threads.

* * * * *

🚀 Running Instructions
-----------------------

### **1️⃣ Compilation via Terminal**

To compile the program, run:

```
g++ -std=c++11 server.cpp -o chat_server -lpthread
g++ -std=c++11 client.cpp -o chat_client -lpthread

```

### **2️⃣ Running the Server**

To run the server, execute:

```
./chat_server

```

The server will start and wait for incoming client connections.

### **3️⃣ Running the Client**

To run the client, execute:

```
./chat_client

```

Clients can connect to the server and start chatting. Multiple clients can be run in separate terminal windows.

### **4️⃣ Alternative Method: Makefile**

If you have a **Makefile**, you can simply run:

```
make
make run

```

* * * * *

🎯 Problem Description
----------------------

This project implements a **chat server** that can handle multiple client connections using multithreading and socket programming. The server broadcasts messages to all connected clients, ensuring that messages are synchronized across different threads.

The server uses **`std::mutex`** for thread synchronization when updating the list of clients and broadcasting messages, ensuring that no race conditions occur when multiple clients send messages concurrently.

### **Challenges Addressed:**

1.  **Thread Synchronization** --- Ensuring that messages from clients are handled correctly without race conditions.

2.  **Multiple Client Connections** --- The server can handle multiple clients at the same time by creating a new thread for each client.

3.  **Message Broadcasting** --- The server broadcasts messages to all connected clients, ensuring they can see each other's messages in real time.

4.  **Handling Client Disconnects** --- When a client disconnects, the server handles it gracefully, ensuring the chat continues for the other users.

* * * * *

🧵 Threads and Their Roles
--------------------------

The project utilizes **two main types of threads**:

| **Thread** | **Role** |
| --- | --- |
| **Main (`main`)** | Starts the server and waits for client connections. For each client, a new thread is created to handle communication. |
| **Client Handler (`handle_client`)** | Each client runs in its own thread. The thread receives messages from the client and broadcasts them to all other clients. |

* * * * *

🔒 Critical Sections and Their Resolution
-----------------------------------------

The **critical section** occurs when updating the list of clients and broadcasting messages. The server ensures that only one thread can access and modify the list of clients at a time.

### **✔ Solution to Synchronization**

We use **`std::mutex`** to synchronize access to the list of clients and ensure that race conditions do not occur when clients are added or removed.

-   **`clients_mutex`** --- a mutex that protects the shared list of clients. It ensures that only one thread can modify the list of clients at a time.

-   **`std::lock_guard<mutex>`** --- used to ensure that the `mutex` is locked when modifying the client list, preventing other threads from accessing it simultaneously.

Additionally, the server uses **`send()`** and **`recv()`** socket functions to communicate with clients, ensuring each message is sent and received in an ordered manner.

* * * * *

📌 Code Structure
-----------------

The project consists of two main files:

1.  **`server.cpp`** --- The main server code that listens for incoming client connections and handles message broadcasting.

2.  **`client.cpp`** --- The client code that connects to the server, sends messages, and displays messages from other clients.

* * * * *

📌 Implementation
-----------------

Sample key code snippets:

✔ **Creating a new thread for each client**:

```
while (true) {
    SOCKET client_socket = accept(server_socket, (sockaddr *)&client_addr, &client_size);
    thread(handle_client, client_socket).detach();
    cout << "New client connected\n";
}

```

✔ **Synchronizing access to the list of clients**:

```
{
    lock_guard<mutex> lock(clients_mutex);
    clients.push_back({client_socket, client_name});
}

```

✔ **Broadcasting messages to all clients**:

```
void broadcast(const string &message, SOCKET sender) {
    lock_guard<mutex> lock(clients_mutex);
    for (auto &client : clients) {
        if (client.first != sender) {
            send(client.first, message.c_str(), message.size(), 0);
        }
    }
}

```

* * * * *

📌 Sample Program Output
------------------------

### **Server Output**:

```
Chat server started on port 54000
New client connected
New client connected
Client 1: Hello, everyone!
Client 2: Hi, there!

```

### **Client Output**:

```
Connected to chat server.
Enter your name: Client 1
[Message] Client 1: Hello, everyone!
[Message] Client 2: Hi, there!

```

The clients can exchange messages with each other in real-time.

* * * * *

📝 Author
---------

👨‍💻 *Yustyna Sukhorab*\
🔗 **Repository:** [GitHub Link](https://github.com/defnotjustine/SO2Projekt/tree/main/ChatServer) 🚀
