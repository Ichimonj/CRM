#include "events_log.hpp"

#include "DateTime/date.hpp"

void EventLog::set_file(const std::string& file_name)
{
    std::lock_guard<std::mutex> lock(mt);
    this->file = std::make_unique<std::ofstream>(file_name, std::ios::app);
}

void EventLog::log(
    const LOG_LEVEL    level,
    const std::string& message_file,
    const size_t&      line,
    const std::string& message
)
{
    if (file->is_open()) {
        Date        date;
        std::string result;
        switch (level) {
            case LOG_LEVEL::INFO:
                result = "[INFO]:    ";
                break;
            case LOG_LEVEL::WARNING:
                result = "[WARNING]: ";
                break;
            case LOG_LEVEL::ERROR:
                result = "[ERROR]:   ";
                break;
            default:
                result = "[DEFAULT]: ";
        }
        result += date.getDateStr() + " - ";

        size_t start_file_name = message_file.find("Crm");
        result += message_file.substr(start_file_name) + ":" + std::to_string(line) + " - ";
        result += message + '\n';
        std::lock_guard<std::mutex> lock(mt);
        file->write(result.c_str(), result.size());
    }
}

EventLog& EventLog::getInstance()
{
    static EventLog instance;
    return instance;
}
