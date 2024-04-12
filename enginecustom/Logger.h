#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger
{
public:

    enum class LogLevel
    {
		Info,
		Warning,
		Error
	};

    Logger() 
    {
        char* appdata = nullptr;
        size_t len;
        _dupenv_s(&appdata, &len, "APPDATA");
        if (appdata == nullptr)
        {
            m_appdataPath = "log.log";
		}
        else 
        {
            m_appdataPath = appdata;
        }
        free(appdata);
        std::string directoryPath = m_appdataPath + "\\Khaotic Engine";
        CreateDirectoryA(directoryPath.c_str(), NULL);

        m_logFilePath = directoryPath + "\\" + m_logFileName;
    }

    void Log(const std::string& message, const std::string& fileName, int lineNumber, LogLevel level = LogLevel::Info)
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::tm buf;
        localtime_s(&buf, &in_time_t);

        // Obtenez les millisecondes à partir de maintenant
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::string levelStr;
        switch (level)
        {
            case LogLevel::Error:
				levelStr = "ERROR";
				break;
            case LogLevel::Warning:
                levelStr = "WARNING";
                break;
            case LogLevel::Info:
                levelStr = "INFO";
				break;
        }

        std::stringstream ss;
        ss << "[" << std::put_time(&buf, "%Y-%m-%d") << "] "
            << "[" << std::put_time(&buf, "%X") << "." << std::setfill('0') << std::setw(3) << ms.count() << "] "
            << "[" << levelStr << "] "
            << "[" << fileName << ":" << lineNumber << "] "
            << message;

        std::ofstream file(m_logFilePath, std::ios::app);
        if (file.is_open())
        {
            file << ss.str() << std::endl;
            file.close();
        }
    }

private:
    std::string m_filename;
    std::string m_appdataPath;
    std::string m_logFileName = "enginecustom.log";
    std::string m_logFilePath;
};
