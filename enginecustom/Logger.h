#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>

class Logger
{
public:

    static Logger& Get()
	{
		static Logger instance;
		return instance;
	}

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

    enum class LogLevel
    {
		Info,
		Warning,
		Error,
        Shutdown,
        Initialize,
        Update,
        Render,
        Input,
        Physics,
        Audio,
        Network,
        Scripting,
        AI,
        Resource,
        Memory,
        Debug
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

        ManageLogFiles(directoryPath);

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
            case LogLevel::Shutdown:
				levelStr = "SHUTDOWN";
				break;
            case LogLevel::Initialize:
				levelStr = "INITIALIZE";
				break;
            case LogLevel::Update:
                levelStr = "UPDATE";
                break;
            case LogLevel::Render:
                levelStr = "RENDER";
                break;
            case LogLevel::Input:
                levelStr = "INPUT";
				break;
            case LogLevel::Physics:
				levelStr = "PHYSICS";
				break;
			case LogLevel::Audio:
                levelStr = "AUDIO";
                break;
            case LogLevel::Network:
                levelStr = "NETWORK";
				break;
            case LogLevel::Scripting:
                levelStr = "SCRIPTING";
                break;
            case LogLevel::AI:
                levelStr = "AI";
				break;
            case LogLevel::Resource:
				levelStr = "RESOURCE";
				break;
            case LogLevel::Memory:
				levelStr = "MEMORY";
				break;
			case LogLevel::Debug:
				levelStr = "DEBUG";
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

    void ManageLogFiles(const std::string& directoryPath)
    {
        std::vector<std::filesystem::path> logFiles;

        // Parcourez tous les fichiers dans le dossier
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        {
            // Si le fichier est un fichier de log, ajoutez-le à la liste
            if (entry.path().extension() == ".log")
            {
                logFiles.push_back(entry.path());
            }
        }

        // Si nous avons plus de trois fichiers de log, supprimez le plus ancien
        while (logFiles.size() >= 3)
        {
            // Triez les fichiers par date de modification, le plus ancien en premier
            std::sort(logFiles.begin(), logFiles.end(), [](const std::filesystem::path& a, const std::filesystem::path& b)
                {
                    return std::filesystem::last_write_time(a) < std::filesystem::last_write_time(b);
                });

            // Supprimez le fichier le plus ancien
            std::filesystem::remove(logFiles[0]);

            // Supprimez-le de la liste
            logFiles.erase(logFiles.begin());
        }

        // Créez un nouveau fichier de log pour cette exécution
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm buf;
        localtime_s(&buf, &in_time_t); 

        std::stringstream ss;
        ss << "Khaotic_log_" << std::put_time(&buf, "%Y_%m_%d_%Hh%Mm%Ss") << ".log";
        m_logFileName = ss.str();

    }

private:
    std::string m_filename;
    std::string m_appdataPath;
    std::string m_logFileName;
    std::string m_logFilePath;
};
