#include <windows.h>
#include <iostream>
#include <array>
#include <cstdlib>
#include <chrono>
#include <ctime>

class PipeServer
{
private:
    HANDLE pipe;
    std::array<char, 128> buffer;

public:
    PipeServer() : pipe(INVALID_HANDLE_VALUE) {}

    bool Init(const std::string& pipeName) {
        std::wstring wPipeName = std::wstring(pipeName.begin(), pipeName.end());
        pipe = CreateNamedPipe(
            (std::wstring(TEXT("\\\\.\\pipe\\")) + wPipeName).c_str(),
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
            1, // max instance
            1024 * 16, // out buffer size
            1024 * 16, // in buffer size
            NMPWAIT_USE_DEFAULT_WAIT,
            NULL
        );

        if (pipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to create named pipe." << std::endl;
            return false;
        }

        std::cout << "Waiting for client to connect to pipe..." << std::endl;

        BOOL result = ConnectNamedPipe(pipe, NULL);
        if (!result) {
            CloseHandle(pipe);
            std::cerr << "Failed to make connection on named pipe." << std::endl;
            return false;
        }

        std::cout << "Client connected." << std::endl;
        return true;
    }

    bool WaitConnection() {
        DisconnectNamedPipe(pipe);
        std::cout << "Waiting for client to connect to pipe..." << std::endl;
        BOOL result = ConnectNamedPipe(pipe, NULL);
        if (!result) {
            CloseHandle(pipe);
            std::cerr << "Failed to make connection on named pipe." << std::endl;
            return false;
        }

        system("cls");
        std::cout << "Client connected." << std::endl;
        return true;
    }

    std::string Update() {
        DWORD bytesRead;
        BOOL result = ReadFile(pipe, buffer.data(), buffer.size(), &bytesRead, NULL);
        if (!result) {
            std::cerr << "Failed to read from named pipe, waiting for new connection..." << std::endl;
            return "";
        }

        return std::string(buffer.data(), bytesRead);
    }

    ~PipeServer() {
        DisconnectNamedPipe(pipe);
        CloseHandle(pipe);
    }
};

inline std::tm localtime_xp(std::time_t timer)
{
    std::tm bt {};
    localtime_s(&bt, &timer);
    return bt;
}

inline std::string GetTimestamp() {
	auto in_time_t = localtime_xp(std::time(0));

    char timeBuffer[100];
    return { timeBuffer, std::strftime(timeBuffer, sizeof(timeBuffer), "[%Y-%m-%d %H:%M:%S]", &in_time_t) };
}

int main() {
    PipeServer server;

    if (server.Init("LeagueOfLegends")) {
        while (true) {
            std::string message = server.Update();
            if (message.empty()) {
                if (!server.WaitConnection())
                    break;
            }
            else {
                std::cout << GetTimestamp() << " " << message << std::endl;
            }
        }
    }

	return 0;
}