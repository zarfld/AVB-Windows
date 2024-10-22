#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <thread>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class AVTP {
public:
    AVTP();
    ~AVTP();
    void start();
    void stop();
    void handleStream();

private:
    bool running;
    SOCKET sock;
    sockaddr_in serverAddr;
    void initializeSocket();
    void closeSocket();
    void captureAVBFrames();
    void processAVBFrames();
};

AVTP::AVTP() : running(false), sock(INVALID_SOCKET) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    initializeSocket();
}

AVTP::~AVTP() {
    stop();
    closeSocket();
    WSACleanup();
}

void AVTP::initializeSocket() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1720); // AVTP port
    inet_pton(AF_INET, "224.0.1.129", &serverAddr.sin_addr); // AVTP multicast address
}

void AVTP::closeSocket() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}

void AVTP::start() {
    running = true;
    std::thread streamThread(&AVTP::handleStream, this);
    streamThread.detach();
}

void AVTP::stop() {
    running = false;
}

void AVTP::handleStream() {
    while (running) {
        captureAVBFrames();
        processAVBFrames();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void AVTP::captureAVBFrames() {
    char buffer[2048];
    int serverAddrSize = static_cast<int>(sizeof(serverAddr));
    int result = recvfrom(sock, buffer, static_cast<int>(sizeof(buffer)), 0, (sockaddr*)&serverAddr, &serverAddrSize);
    if (result == SOCKET_ERROR) {
        std::cerr << "Receive failed with error: " << WSAGetLastError() << std::endl;
    } else {
        buffer[result] = '\0';
        std::cout << "Captured AVB Frame: " << buffer << std::endl;
    }
}

void AVTP::processAVBFrames() {
    // Process the captured AVB frames
    std::cout << "Processing AVB Frames..." << std::endl;
}

// Abstraction layer for NIC-specific code
typedef struct _NIC_ABSTRACTION_LAYER {
    void (*InitializeSocket)(SOCKET* sock, sockaddr_in* serverAddr, const char* multicastAddress, int port);
    void (*CloseSocket)(SOCKET* sock);
    void (*SendMessage)(SOCKET sock, const char* message, sockaddr_in* serverAddr);
    void (*ReceiveMessage)(SOCKET sock, char* buffer, int bufferSize, sockaddr_in* serverAddr);
} NIC_ABSTRACTION_LAYER, *PNIC_ABSTRACTION_LAYER;

void InitializeSocket(SOCKET* sock, sockaddr_in* serverAddr, const char* multicastAddress, int port) {
    *sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (*sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(port);
    inet_pton(AF_INET, multicastAddress, &serverAddr->sin_addr);
}

void CloseSocket(SOCKET* sock) {
    if (*sock != INVALID_SOCKET) {
        closesocket(*sock);
        *sock = INVALID_SOCKET;
    }
}

void SendMessage(SOCKET sock, const char* message, sockaddr_in* serverAddr) {
    int result = sendto(sock, message, strlen(message), 0, (sockaddr*)serverAddr, sizeof(*serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
    }
}

void ReceiveMessage(SOCKET sock, char* buffer, int bufferSize, sockaddr_in* serverAddr) {
    int serverAddrSize = sizeof(*serverAddr);
    int result = recvfrom(sock, buffer, bufferSize, 0, (sockaddr*)serverAddr, &serverAddrSize);
    if (result == SOCKET_ERROR) {
        std::cerr << "Receive failed with error: " << WSAGetLastError() << std::endl;
    } else {
        buffer[result] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }
}

// NIC-specific modules
NIC_ABSTRACTION_LAYER IntelI210AbstractionLayer = {
    InitializeSocket,
    CloseSocket,
    SendMessage,
    ReceiveMessage
};

NIC_ABSTRACTION_LAYER AnotherNICAbstractionLayer = {
    InitializeSocket,
    CloseSocket,
    SendMessage,
    ReceiveMessage
};

// Refactor existing code to use the abstraction layer
void AVTP::initializeSocket() {
    IntelI210AbstractionLayer.InitializeSocket(&sock, &serverAddr, "224.0.1.129", 1720);
}

void AVTP::closeSocket() {
    IntelI210AbstractionLayer.CloseSocket(&sock);
}

void AVTP::captureAVBFrames() {
    char buffer[2048];
    IntelI210AbstractionLayer.ReceiveMessage(sock, buffer, sizeof(buffer), &serverAddr);
    std::cout << "Captured AVB Frame: " << buffer << std::endl;
}
