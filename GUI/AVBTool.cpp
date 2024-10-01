#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <commctrl.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Comctl32.lib")

class AVBTool {
public:
    AVBTool(HINSTANCE hInstance);
    ~AVBTool();
    void run();

private:
    HINSTANCE hInstance;
    HWND hwndMain;
    HWND hwndList;
    HWND hwndStartButton;
    HWND hwndStopButton;
    bool running;
    SOCKET sock;
    sockaddr_in serverAddr;
    std::vector<std::string> devices;
    std::thread syncThread;
    std::thread deviceThread;

    void initializeWindow();
    void initializeSocket();
    void closeSocket();
    void startSynchronization();
    void stopSynchronization();
    void synchronize();
    void discoverDevices();
    void controlDevice(const std::string& device);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

AVBTool::AVBTool(HINSTANCE hInstance) : hInstance(hInstance), hwndMain(NULL), hwndList(NULL), hwndStartButton(NULL), hwndStopButton(NULL), running(false), sock(INVALID_SOCKET) {
    initializeWindow();
    initializeSocket();
}

AVBTool::~AVBTool() {
    stopSynchronization();
    closeSocket();
}

void AVBTool::initializeWindow() {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "AVBToolClass";
    RegisterClass(&wc);

    hwndMain = CreateWindowEx(0, "AVBToolClass", "AVB Tool", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, this);
    hwndList = CreateWindowEx(0, WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | LVS_REPORT, 10, 10, 760, 400, hwndMain, NULL, hInstance, NULL);
    hwndStartButton = CreateWindowEx(0, "BUTTON", "Start", WS_CHILD | WS_VISIBLE, 10, 420, 100, 30, hwndMain, (HMENU)1, hInstance, NULL);
    hwndStopButton = CreateWindowEx(0, "BUTTON", "Stop", WS_CHILD | WS_VISIBLE, 120, 420, 100, 30, hwndMain, (HMENU)2, hInstance, NULL);

    ShowWindow(hwndMain, SW_SHOW);
}

void AVBTool::initializeSocket() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(319); // gPTP event port
    inet_pton(AF_INET, "224.0.1.129", &serverAddr.sin_addr); // gPTP multicast address
}

void AVBTool::closeSocket() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
    WSACleanup();
}

void AVBTool::startSynchronization() {
    running = true;
    syncThread = std::thread(&AVBTool::synchronize, this);
    deviceThread = std::thread(&AVBTool::discoverDevices, this);
}

void AVBTool::stopSynchronization() {
    running = false;
    if (syncThread.joinable()) {
        syncThread.join();
    }
    if (deviceThread.joinable()) {
        deviceThread.join();
    }
}

void AVBTool::synchronize() {
    while (running) {
        const char* syncMessage = "SYNC";
        int result = sendto(sock, syncMessage, strlen(syncMessage), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
        if (result == SOCKET_ERROR) {
            std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        }

        char buffer[1024];
        int serverAddrSize = sizeof(serverAddr);
        result = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&serverAddr, &serverAddrSize);
        if (result == SOCKET_ERROR) {
            std::cerr << "Receive failed with error: " << WSAGetLastError() << std::endl;
        } else {
            buffer[result] = '\0';
            std::cout << "Received: " << buffer << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void AVBTool::discoverDevices() {
    while (running) {
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

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void AVBTool::controlDevice(const std::string& device) {
    std::cout << "Managing Device: " << device << std::endl;
    // Implement device control logic here
}

void AVBTool::run() {
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK AVBTool::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    AVBTool* tool;
    if (uMsg == WM_CREATE) {
        tool = (AVBTool*)((LPCREATESTRUCT)lParam)->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)tool);
    } else {
        tool = (AVBTool*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (tool) {
        switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                tool->startSynchronization();
            } else if (LOWORD(wParam) == 2) {
                tool->stopSynchronization();
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    } else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AVBTool tool(hInstance);
    tool.run();
    return 0;
}
