#pragma once

#include "../../stdafx.h"

class PipeClient
{
private:
    HANDLE pipe;

    static PipeClient& GetInstance() {
        static PipeClient instance;
        return instance;
    }

    PipeClient() : pipe(INVALID_HANDLE_VALUE) {
        std::string pipePath = SP_STRING("\\\\.\\pipe\\LeagueOfLegends");
        std::wstring wPipePath(pipePath.begin(), pipePath.end());

        pipe = CreateFile(
            wPipePath.c_str(),
            GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );

        if (pipe == INVALID_HANDLE_VALUE) {
            std::cerr << SP_STRING("Failed to open named pipe.") << std::endl;
        }
    }

public:
    static void Write(const std::string& message) {
        HANDLE pipe = GetInstance().pipe;
        if (pipe == INVALID_HANDLE_VALUE)
        {
            std::cout << message << std::endl;
            return;
        };
        DWORD bytesWritten;
        BOOL result = WriteFile(pipe, message.c_str(), message.size(), &bytesWritten, NULL);
        if (!result || bytesWritten != message.size()) {
            CloseHandle(pipe);
            std::cerr << SP_STRING("Failed to write to named pipe.") << std::endl;
        }
    }

    ~PipeClient() {
        CloseHandle(pipe);
    }
};

#define LOG(str) PipeClient::Write(SP_STRING(str))