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
    int result = sendto(sock, discoverMessage, strlen(discoverMessage), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    char buffer[1024];
    int serverAddrSize = sizeof(serverAddr);
    result = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&serverAddr, &serverAddrSize);
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

int main() {
    AVDECC avdecc;
    avdecc.start();

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();

    avdecc.stop();
    return 0;
}
