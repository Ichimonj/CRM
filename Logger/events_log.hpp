#include <fstream>
#include <memory>
#include <mutex>
enum class LOG_LEVEL { INFO, WARNING, ERROR };
class EventLog {
public:
    EventLog()                           = default;
    EventLog(const EventLog&)            = delete;
    EventLog& operator=(const EventLog&) = delete;

    /// @name functions
    /// @{
    void set_file(const std::string& file_name);
    void log(
        const LOG_LEVEL    level,
        const std::string& message_file,
        const size_t&      line,
        const std::string& message
    );
    static EventLog& getInstance();
    ///@}

private:
    std::mutex                     mt;
    static EventLog*               instance;
    std::unique_ptr<std::ofstream> file;
};