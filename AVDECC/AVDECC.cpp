#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class AVDECC {
public:
    AVDECC();
    ~AVDECC();
    void start();
    void stop();
    void enumerateDevices();
    void manageStreams();

private:
    bool running;
    SOCKET sock;
    sockaddr_in serverAddr;
    std::vector<std::string> devices;
    void initializeSocket();
    void closeSocket();
    void discoverDevices();
    void controlDevice(const std::string& device);
};

AVDECC::AVDECC() : running(false), sock(INVALID_SOCKET) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    initializeSocket();
}

AVDECC::~AVDECC() {
    stop();
    closeSocket();
    WSACleanup();
}

void AVDECC::initializeSocket() {
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1720); // AVDECC port
    inet_pton(AF_INET, "224.0.1.129", &serverAddr.sin_addr); // AVDECC multicast address
}

void AVDECC::closeSocket() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}

void AVDECC::start() {
    running = true;
    std::thread deviceThread(&AVDECC::enumerateDevices, this);
    deviceThread.detach();
    std::thread streamThread(&AVDECC::manageStreams, this);
    streamThread.detach();
}

void AVDECC::stop() {
    running = false;
}

void AVDECC::enumerateDevices() {
    while (running) {
        discoverDevices();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void AVDECC::manageStreams() {
    while (running) {
        for (const auto& device : devices) {
            controlDevice(device);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void AVDECC::discoverDevices() {
    const char* discoverMessage = "DISCOVER";
    int result = sendto(sock, discoverMessage, static_cast<int>(strlen(discoverMessage)), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    char buffer[1024];
    int serverAddrSize = sizeof(serverAddr);
    result = recvfrom(sock, buffer, static_cast<int>(sizeof(buffer)), 0, (sockaddr*)&serverAddr, &serverAddrSize);
    if (result == SOCKET_ERROR) {
        std::cerr << "Receive failed with error: " << WSAGetLastError() << std::endl;
    } else {
        buffer[result] = '\0';
        devices.push_back(buffer);
        std::cout << "Discovered Device: " << buffer << std::endl;
    }
}

void AVDECC::controlDevice(const std::string& device) {
    std::cout << "Managing Device: " << device << std::endl;
    // Implement device control logic here
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
void AVDECC::initializeSocket() {
    IntelI210AbstractionLayer.InitializeSocket(&sock, &serverAddr, "224.0.1.129", 1720);
}

void AVDECC::closeSocket() {
    IntelI210AbstractionLayer.CloseSocket(&sock);
}

void AVDECC::discoverDevices() {
    IntelI210AbstractionLayer.SendMessage(sock, "DISCOVER", &serverAddr);
    char buffer[1024];
    IntelI210AbstractionLayer.ReceiveMessage(sock, buffer, sizeof(buffer), &serverAddr);
    devices.push_back(buffer);
    std::cout << "Discovered Device: " << buffer << std::endl;
}
