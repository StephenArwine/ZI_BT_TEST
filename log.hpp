#pragma once

#include <sstream>
#include <iostream>

typedef void (*LogReciever)(const char *pMessage);


enum LogLevel
{
	Debug,
	Verbose,
	Normal,
	ErrorsOnly
};

void LogDebug(const char *pText);
void LogInfo(const char *pText);
void LogStatus(const char *pText);
void LogWarn(const char *pText);
void LogError(const char *pText);
void LogFatal(const char *pText);
void LogAlways(const char *pText);
void LogTrace(const char *pText);

#define SSTR std::ostringstream().flush()

class Log
{
public:
	//
	// Registration
	//

	// Register logging receiver for DEBUG logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerDebugReceiver(LogReciever receiver);

	// Register logging receiver for INFO logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerInfoReceiver(LogReciever receiver);

	// Register logging receiver for STATUS logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerStatusReceiver(LogReciever receiver);

	// Register logging receiver for WARN logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerWarnReceiver(LogReciever receiver);

	// Register logging receiver for ERROR logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerErrorReceiver(LogReciever receiver);

	// Register logging receiver for FATAL logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerFatalReceiver(LogReciever receiver);

	// Register logging receiver for ALWAYS logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerAlwaysReceiver(LogReciever receiver);

	// Register logging receiver for TRACE logging.  To register a logging level, simply call with a delegate that performs the
	// appropriate logging action. To unregister, call with `nullptr`
	static void registerTraceReceiver(LogReciever receiver);


	//
	// Logging actions
	//

	// Log a DEBUG entry with a C string
	static void debug(const char *pText);

	// Log a DEBUG entry with a string
	static void debug(const std::string &text);

	// Log a DEBUG entry using a stream
	static void debug(const std::ostream &text);

	// Log a INFO entry with a C string
	static void info(const char *pText);

	// Log a INFO entry with a string
	static void info(const std::string &text);

	// Log a INFO entry using a stream
	static void info(const std::ostream &text);

	// Log a STATUS entry with a C string
	static void status(const char *pText);

	// Log a STATUS entry with a string
	static void status(const std::string &text);

	// Log a STATUS entry using a stream
	static void status(const std::ostream &text);

	// Log a WARN entry with a C string
	static void warn(const char *pText);

	// Log a WARN entry with a string
	static void warn(const std::string &text);

	// Log a WARN entry using a stream
	static void warn(const std::ostream &text);

	// Log a ERROR entry with a C string
	static void error(const char *pText);

	// Log a ERROR entry with a string
	static void error(const std::string &text);

	// Log a ERROR entry using a stream
	static void error(const std::ostream &text);

	// Log a FATAL entry with a C string
	static void fatal(const char *pText);

	// Log a FATAL entry with a string
	static void fatal(const std::string &text);

	// Log a FATAL entry using a stream
	static void fatal(const std::ostream &text);

	// Log a ALWAYS entry with a C string
	static void always(const char *pText);

	// Log a ALWAYS entry with a string
	static void always(const std::string &text);

	// Log a ALWAYS entry using a stream
	static void always(const std::ostream &text);

	// Log a TRACE entry with a C string
	static void trace(const char *pText);

	// Log a TRACE entry with a string
	static void trace(const std::string &text);

	// Log a TRACE entry using a stream
	static void trace(const std::ostream &text);

private:

	// The registered log receiver for DEBUG logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverDebug;

	// The registered log receiver for INFO logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverInfo;

	// The registered log receiver for STATUS logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverStatus;

	// The registered log receiver for WARN logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverWarn;

	// The registered log receiver for ERROR logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverError;

	// The registered log receiver for FATAL logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverFatal;

	// The registered log receiver for ALWAYS logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverAlways;

	// The registered log receiver for TRACE logs - a nullptr will cause the logging for that receiver to be ignored
	static LogReciever logReceiverTrace;
};
