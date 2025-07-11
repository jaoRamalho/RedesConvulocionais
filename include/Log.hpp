#ifndef LOG_HPP
#define LOG_HPP


#include "stdint.h"
#include "ModulesNames.h"
#include "Macros.hpp"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    Error = 0,
    Warning,
    Info,
    Debug
} Log_LevelInfo;

#if MICROCONTROLLER

#include "rb.h"

#define MAX_LOG_SIZE 400
#define SEND_LOG_IN_REAL_TIME 
#define VERBOSE 1

void logInit(void * dbgUart);
void logPrint(char *data);
void logWrite(uint8_t *data, uint32_t len);
void logPrintf(const char *format, ...);
void logPrintfSerial(Log_LevelInfo levelInfo,const char * module,const char *format, ...);
void logPrintSerial(Log_LevelInfo levelInfo,const char * module,uint8_t *data, uint32_t len);
uint32_t logReceiveAvailable();
uint8_t logReceive();
void logReceiveSize(uint8_t *dest, uint32_t len);
uint8_t logRBAvail();
uint8_t getLogRB();

#else

void logPrintf(Log_LevelInfo levelInfo, const char *module, const char *format, ...);
void logPrintfFile(Log_LevelInfo levelInfo, const char *module, const char *format, ...);

#endif


#ifdef __cplusplus
}
#endif

#endif // LOG_HPP