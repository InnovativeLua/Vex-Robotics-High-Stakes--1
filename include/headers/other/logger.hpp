/*
#pragma once

// For the unique pointers.
#include <memory>
// Filestream.
#include <fstream>
// String class for names and parameters passed around.
#include <string>

namespace logger{
    //INFO - Informational messages that do not indicate any fault or error.
    //WARN - Indicates that there is a potential problem, but with no user experience impact.
    //ERROR - Indicates a serious problem, with some user experience impact.
    //FATAL - Indicates fatal errors, user experience is majorly impacted.
    //DEBUG - Used for debugging. The messaging targets specifically the app’s developers.
    enum logLevel {E_NONE, E_INFO, E_WARN, E_ERROR, E_FATAL, E_DEBUG};

    // Initialize the log.
    void startLog(const std::string& filepath);

    // Log a message.
    void log(logLevel s, const std::string& msg);

    // Logging class.
    class Log {
    public:
        Log(const std::string& filepath);
        void addLog(logLevel s, const std::string& msg);
        ~Log();
    private:
        // File for logging.
        std::ofstream m_logfile;

        std::string levels[5] = {"Fatal", "Error", "Warning", "Info", "Debug"};
    };
}
*/