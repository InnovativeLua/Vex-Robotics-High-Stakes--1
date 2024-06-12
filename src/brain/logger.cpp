#include "custom/general/logger.hpp"

/*
namespace Logger {
    // Global Logging Object.
    std::unique_ptr<logger::Log> g_log;

    // Initalize our logging object.
    void startLog(const std::string& filepath) {
        g_log = std::make_unique<logger::Log>(filepath);
        Logger::log(logger::E_INFO, "Started logging system.");
    }

    // Method which logs.
    void log(logger::logLevel s, const std::string& msg) {
        g_log->addLog(s, msg);
    }

    // Create our global logging object.
    Log::Log(const std::string& filepath) : m_logfile{} {
        m_logfile.open(filepath);
    }

    // Add a message to our log.
    void logger::Log::addLog(logger::logLevel s, const std::string& msg) {
        if (m_logfile.is_open()) {
            m_logfile << levels[static_cast<int>(s)] << ": " << msg << std::endl;
        }
    }

    logger::Log::~Log() {
        addLog(logger::logLevel::E_INFO, "Stopped logging system.");
        m_logfile.close();
    }
}

*/