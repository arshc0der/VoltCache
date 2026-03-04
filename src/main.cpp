#include <iostream>
#include <string>
#include "VoltCache.h"

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define closesocket close
    typedef int SOCKET;
#endif

int main() {
    #ifdef _WIN32
    WSADATA wsa; WSAStartup(MAKEWORD(2, 2), &wsa);
    #endif

    VoltCache db;
    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};
    
    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 10);
    std::cout << "⚡ VoltCache Server Online [Port 8080]\n";

    while (true) {
        SOCKET client = accept(server, nullptr, nullptr);
        char buf[1024] = {0};
        int bytes = recv(client, buf, 1024, 0);
        
        if (bytes > 0) {
            auto tokens = db.tokenize(std::string(buf));
            std::string response = "ERR: Invalid Command\n";
            
            if (tokens.size() >= 2) {
                if (tokens[0] == "GET") response = db.get(tokens[1]) + "\n";
                else if (tokens[0] == "SET" && tokens.size() >= 3) {
                    db.set(tokens[1], tokens[2]);
                    response = "OK\n";
                }
            }
            send(client, response.c_str(), response.length(), 0);
        }
        closesocket(client);
    }
    return 0;
}