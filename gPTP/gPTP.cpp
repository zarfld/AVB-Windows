#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class gPTP {
public:
    gPTP();
    ~gPTP();
    void start();
    void stop();
    void synchronize();

private:
    bool running;
    SOCKET sock;
    sockaddr_in serverAddr;
    void initializeSocket();
    void closeSocket();
    void sendSyncMessage();
    void receiveSyncMessage();
};

gPTP::gPTP() : running(false), sock(INVALID_SOCKET) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    initializeSocket();
}

gPTP::~gPTP() {
    stop();
    closeSocket();
    WSACleanup();
}

void gPTP::initializeSocket() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(319); // gPTP event port
    inet_pton(AF_INET, "224.0.1.129", &serverAddr.sin_addr); // gPTP multicast address
}

void gPTP::closeSocket() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}

void gPTP::start() {
    running = true;
    std::thread syncThread(&gPTP::synchronize, this);
    syncThread.detach();
}

void gPTP::stop() {
    running = false;
}

void gPTP::synchronize() {
    while (running) {
        sendSyncMessage();
        receiveSyncMessage();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void gPTP::sendSyncMessage() {
    const char* syncMessage = "SYNC";
    int result = sendto(sock, syncMessage, strlen(syncMessage), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
    }
}

void gPTP::receiveSyncMessage() {
    char buffer[1024];
    int serverAddrSize = sizeof(serverAddr);
    int result = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&serverAddr, &serverAddrSize);
    if (result == SOCKET_ERROR) {
        std::cerr << "Receive failed with error: " << WSAGetLastError() << std::endl;
    } else {
        buffer[result] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }
}

int main() {
    gPTP ptp;
    ptp.start();

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();

    ptp.stop();
    return 0;
}
