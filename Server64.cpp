#include <Windows.h>
#include <iostream>

int main() {
    std::cout << sizeof(int*) << std::endl;

    // Create a named pipe
    HANDLE hPipe = CreateNamedPipeW(
        L"\\\\.\\pipe\\MyNamedPipe", PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 0, 0, NMPWAIT_USE_DEFAULT_WAIT, nullptr);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Named pipe server is waiting for a connection..." << std::endl;

    // Wait for a client to connect
    if (ConnectNamedPipe(hPipe, nullptr) != FALSE) {
        std::cout << "Client connected!" << std::endl;

        // Read data from the client
        char buffer[100];
        DWORD bytesRead;
        if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr) != FALSE) {
            buffer[bytesRead] = '\0';
            std::cout << "Received message from client: " << buffer << std::endl;
        }
        else {
            std::cerr << "Failed to read from pipe. Error code: " << GetLastError() << std::endl;
        }

        // Clean up
        DisconnectNamedPipe(hPipe);
    }
    else {
        std::cerr << "Failed to establish connection. Error code: " << GetLastError() << std::endl;
    }

    CloseHandle(hPipe);

    return 0;
}
