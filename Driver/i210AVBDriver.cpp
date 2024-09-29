#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>
#include <ndis.h>

#define GPTP_EVENT_PORT 319
#define GPTP_MULTICAST_ADDRESS "224.0.1.129"

typedef struct _DEVICE_CONTEXT {
    WDFDEVICE Device;
    NDIS_HANDLE NdisHandle;
    BOOLEAN Running;
    KEVENT StopEvent;
} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD EvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP EvtDriverContextCleanup;

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
{
    WDF_DRIVER_CONFIG config;
    NTSTATUS status;

    WDF_DRIVER_CONFIG_INIT(&config, EvtDeviceAdd);
    config.EvtDriverUnload = EvtDriverContextCleanup;

    status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfDriverCreate failed with status 0x%x\n", status));
    }

    return status;
}

NTSTATUS
EvtDeviceAdd(
    _In_ WDFDRIVER Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
{
    NTSTATUS status;
    WDFDEVICE device;
    PDEVICE_CONTEXT deviceContext;

    UNREFERENCED_PARAMETER(Driver);

    status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfDeviceCreate failed with status 0x%x\n", status));
        return status;
    }

    deviceContext = DeviceGetContext(device);
    deviceContext->Device = device;
    deviceContext->Running = FALSE;
    KeInitializeEvent(&deviceContext->StopEvent, NotificationEvent, FALSE);

    return status;
}

VOID
EvtDriverContextCleanup(
    _In_ WDFOBJECT DriverObject
    )
{
    UNREFERENCED_PARAMETER(DriverObject);
}

VOID
StartGPTP(
    _In_ PDEVICE_CONTEXT DeviceContext
    )
{
    DeviceContext->Running = TRUE;
    HANDLE threadHandle;
    PsCreateSystemThread(&threadHandle, THREAD_ALL_ACCESS, NULL, NULL, NULL, GPTPThread, DeviceContext);
    ZwClose(threadHandle);
}

VOID
StopGPTP(
    _In_ PDEVICE_CONTEXT DeviceContext
    )
{
    DeviceContext->Running = FALSE;
    KeSetEvent(&DeviceContext->StopEvent, 0, FALSE);
}

VOID
GPTPThread(
    _In_ PVOID Context
    )
{
    PDEVICE_CONTEXT deviceContext = (PDEVICE_CONTEXT)Context;
    SOCKET sock;
    sockaddr_in serverAddr;
    WSADATA wsaData;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        KdPrint(("Socket creation failed with error: %d\n", WSAGetLastError()));
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(GPTP_EVENT_PORT);
    inet_pton(AF_INET, GPTP_MULTICAST_ADDRESS, &serverAddr.sin_addr);

    while (deviceContext->Running) {
        SendSyncMessage(sock, &serverAddr);
        ReceiveSyncMessage(sock, &serverAddr);
        KeWaitForSingleObject(&deviceContext->StopEvent, Executive, KernelMode, FALSE, NULL);
    }

    closesocket(sock);
    WSACleanup();
}

VOID
SendSyncMessage(
    _In_ SOCKET Sock,
    _In_ sockaddr_in* ServerAddr
    )
{
    const char* syncMessage = "SYNC";
    int result = sendto(Sock, syncMessage, strlen(syncMessage), 0, (sockaddr*)ServerAddr, sizeof(*ServerAddr));
    if (result == SOCKET_ERROR) {
        KdPrint(("Send failed with error: %d\n", WSAGetLastError()));
    }
}

VOID
ReceiveSyncMessage(
    _In_ SOCKET Sock,
    _In_ sockaddr_in* ServerAddr
    )
{
    char buffer[1024];
    int serverAddrSize = sizeof(*ServerAddr);
    int result = recvfrom(Sock, buffer, sizeof(buffer), 0, (sockaddr*)ServerAddr, &serverAddrSize);
    if (result == SOCKET_ERROR) {
        KdPrint(("Receive failed with error: %d\n", WSAGetLastError()));
    } else {
        buffer[result] = '\0';
        KdPrint(("Received: %s\n", buffer));
    }
}