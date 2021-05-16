#include "emu/log.h"

void log_alllevels(){
    LOG_error("Example for Error.");
    LOG_warn("Example for Warning.");
    LOG_info("Example for Info.");
    LOG_debug("Example for Debug.");
    LOG_trace("Example for Trace.");
}


int main(){
	LOG_setLogFile("./test_logger.log");

    // Info is default
    LOG_info("Format fields: d3=%3d, s4=%.4s, f5=%5f", 13, "hello", 3.141592 );

	LOG_setLevel(LOG_LVL_ERROR);
    log_alllevels();

	LOG_setLevel(LOG_LVL_WARN);
    log_alllevels();

	LOG_setLevel(LOG_LVL_INFO);
    log_alllevels();

	LOG_setLevel(LOG_LVL_DEBUG);
    log_alllevels();

	LOG_setLevel(LOG_LVL_TRACE);
    log_alllevels();


}