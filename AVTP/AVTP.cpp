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

int main() {
    AVTP avtp;
    avtp.start();

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();

    avtp.stop();
    return 0;
}
