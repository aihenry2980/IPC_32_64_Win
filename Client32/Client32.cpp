#include <Windows.h>
#include <iostream>

int main() {
    std::cout << sizeof(int*) << std::endl;
    // Open the named pipe
    HANDLE hPipe = CreateFileW(
        L"\\\\.\\pipe\\MyNamedPipe", GENERIC_READ | GENERIC_WRITE, 0, nullptr,
        OPEN_EXISTING, 0, nullptr);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open named pipe. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Connected to named pipe server!" << std::endl;

    // Send data to the server
    const char* message = "Hello from 32-bit client!";
    DWORD bytesWritten;
    if (WriteFile(hPipe, message, strlen(message), &bytesWritten, nullptr) != FALSE) {
        std::cout << "Sent message to server: " << message << std::endl;
    }
    else {
        std::cerr << "Failed to write to pipe. Error code: " << GetLastError() << std::endl;
    }

    // Clean up
    CloseHandle(hPipe);

    // Wait for user input before exiting
    std::wcout << L"Press Enter to exit...";
    std::wcin.get();

    return 0;
}
