#include "log.hpp"

extern LogLevel logLevel;

void LogDebug(const char *pText)
{
    if (logLevel <= Debug)
    {
        std::cout << "  DEBUG: " << pText << std::endl;
    }
}
void LogInfo(const char *pText)
{
    if (logLevel <= Verbose)
    {
        std::cout << "   INFO: " << pText << std::endl;
    }
}
void LogStatus(const char *pText)
{
    if (logLevel <= Normal)
    {
        std::cout << " STATUS: " << pText << std::endl;
    }
}
void LogWarn(const char *pText) { std::cout << "WARNING: " << pText << std::endl; }
void LogError(const char *pText) { std::cout << "!!ERROR: " << pText << std::endl; }
void LogFatal(const char *pText) { std::cout << "**FATAL: " << pText << std::endl; }
void LogAlways(const char *pText) { std::cout << "..Log..: " << pText << std::endl; }
void LogTrace(const char *pText) { std::cout << "-Trace-: " << pText << std::endl; }

// The registered log receiver for DEBUG logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverDebug = nullptr;

// The registered log receiver for INFO logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverInfo = nullptr;

// The registered log receiver for STATUS logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverStatus = nullptr;

// The registered log receiver for WARN logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverWarn = nullptr;

// The registered log receiver for ERROR logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverError = nullptr;

// The registered log receiver for FATAL logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverFatal = nullptr;

// The registered log receiver for ALWAYS logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverAlways = nullptr;

// The registered log receiver for TRACE logs - a nullptr will cause the logging for that receiver to be ignored
LogReciever Log::logReceiverTrace = nullptr;

//
// Registration
//

// Register logging receiver for DEBUG logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerDebugReceiver(LogReciever receiver) { Log::logReceiverDebug = receiver; }

// Register logging receiver for INFO logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerInfoReceiver(LogReciever receiver) { Log::logReceiverInfo = receiver; }

// Register logging receiver for STATUS logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerStatusReceiver(LogReciever receiver) { Log::logReceiverStatus = receiver; }

// Register logging receiver for WARN logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerWarnReceiver(LogReciever receiver) { Log::logReceiverWarn = receiver; }

// Register logging receiver for ERROR logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerErrorReceiver(LogReciever receiver) { Log::logReceiverError = receiver; }

// Register logging receiver for FATAL logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerFatalReceiver(LogReciever receiver) { Log::logReceiverFatal = receiver; }

// Register logging receiver for ALWAYS logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerAlwaysReceiver(LogReciever receiver) { Log::logReceiverAlways = receiver; }

// Register logging receiver for TRACE logging.  To register a logging level, simply call with a delegate that performs the
// appropriate logging action. To unregister, call with `nullptr`
void Log::registerTraceReceiver(LogReciever receiver) { Log::logReceiverTrace = receiver; }

//
// Logging actions
//

// Log a DEBUG entry with a C string
void Log::debug(const char *pText)
{
    if (nullptr != Log::logReceiverDebug)
    {
        Log::logReceiverDebug(pText);
    }
}

// Log a DEBUG entry with a string
void Log::debug(const std::string &text)
{
    if (nullptr != Log::logReceiverDebug)
    {
        debug(text.c_str());
    }
}

// Log a DEBUG entry using a stream
void Log::debug(const std::ostream &text)
{
    if (nullptr != Log::logReceiverDebug)
    {
        debug(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}

// Log a INFO entry with a C string
void Log::info(const char *pText)
{
    if (nullptr != Log::logReceiverInfo)
    {
        Log::logReceiverInfo(pText);
    }
}

// Log a INFO entry with a string
void Log::info(const std::string &text)
{
    if (nullptr != Log::logReceiverInfo)
    {
        info(text.c_str());
    }
}

// Log a INFO entry using a stream
void Log::info(const std::ostream &text)
{
    if (nullptr != Log::logReceiverInfo)
    {
        info(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}

// Log a STATUS entry with a C string
void Log::status(const char *pText)
{
    if (nullptr != Log::logReceiverStatus)
    {
        Log::logReceiverStatus(pText);
    }
}

// Log a STATUS entry with a string
void Log::status(const std::string &text)
{
    if (nullptr != Log::logReceiverStatus)
    {
        status(text.c_str());
    }
}

// Log a STATUS entry using a stream
void Log::status(const std::ostream &text)
{
    if (nullptr != Log::logReceiverStatus)
    {
        status(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}

// Log a WARN entry with a C string
void Log::warn(const char *pText)
{
    if (nullptr != Log::logReceiverWarn)
    {
        Log::logReceiverWarn(pText);
    }
}

// Log a WARN entry with a string
void Log::warn(const std::string &text)
{
    if (nullptr != Log::logReceiverWarn)
    {
        warn(text.c_str());
    }
}

// Log a WARN entry using a stream
void Log::warn(const std::ostream &text)
{
    if (nullptr != Log::logReceiverWarn)
    {
        warn(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}

// Log a ERROR entry with a C string
void Log::error(const char *pText)
{
    if (nullptr != Log::logReceiverError)
    {
        Log::logReceiverError(pText);
    }
}

// Log a ERROR entry with a string
void Log::error(const std::string &text)
{
    if (nullptr != Log::logReceiverError)
    {
        error(text.c_str());
    }
}

// Log a ERROR entry using a stream
void Log::error(const std::ostream &text)
{
    if (nullptr != Log::logReceiverError)
    {
        error(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}

// Log a FATAL entry with a C string
void Log::fatal(const char *pText)
{
    if (nullptr != Log::logReceiverFatal)
    {
        Log::logReceiverFatal(pText);
    }
}

// Log a FATAL entry with a string
void Log::fatal(const std::string &text)
{
    if (nullptr != Log::logReceiverFatal)
    {
        fatal(text.c_str());
    }
}

// Log a FATAL entry using a stream
void Log::fatal(const std::ostream &text)
{
    if (nullptr != Log::logReceiverFatal)
    {
        fatal(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}

// Log a ALWAYS entry with a C string
void Log::always(const char *pText)
{
    if (nullptr != Log::logReceiverAlways)
    {
        Log::logReceiverAlways(pText);
    }
}

// Log a ALWAYS entry with a string
void Log::always(const std::string &text)
{
    if (nullptr != Log::logReceiverAlways)
    {
        always(text.c_str());
    }
}

// Log a ALWAYS entry using a stream
void Log::always(const std::ostream &text)
{
    if (nullptr != Log::logReceiverAlways)
    {
        always(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}

// Log a TRACE entry with a C string
void Log::trace(const char *pText)
{
    if (nullptr != Log::logReceiverTrace)
    {
        Log::logReceiverTrace(pText);
    }
}

// Log a TRACE entry with a string
void Log::trace(const std::string &text)
{
    if (nullptr != Log::logReceiverTrace)
    {
        trace(text.c_str());
    }
}

// Log a TRACE entry using a stream
void Log::trace(const std::ostream &text)
{
    if (nullptr != Log::logReceiverTrace)
    {
        trace(static_cast<const std::ostringstream &>(text).str().c_str());
    }
}
