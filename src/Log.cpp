#include "Log.hpp"


#if MICROCONTROLLER

#include <string>
#include "Arduino.h"

STRUCT_RB logRingBuffer;
char buffer[MAX_LOG_SIZE];


HardwareSerial *serialLog = NULL;

time_t ts;
struct tm timedata;

void logInit(void * dbgUart) {
    serialLog = ((HardwareSerial *)dbgUart);
    rb_init(&logRingBuffer, buffer, MAX_LOG_SIZE);
}

void logPrint(char *data) {
    if (serialLog) {
        serialLog->print(data);
    }
}

void logWrite(uint8_t *data, uint32_t len) {
    if (serialLog) {
        serialLog->write(data, len);
    }
}

void logPrintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    uint32_t len = vsnprintf(NULL, 0, format, args) + 1;
    char* data = (char*)malloc(len + sizeof(char));
    vsprintf(data, format, args);
    serialLog->write((uint8_t*)data, strlen(data));
    va_end(args);
    free(data);
}

void logPrintfSerial(Log_LevelInfo levelInfo,const char * module,const char *format, ...) {
	memset(buffer,0,MAX_LOG_SIZE);

	//Timestamp
	ts = time(NULL);
	timedata = *gmtime(&ts);
	timedata.tm_year = (uint32_t)(timedata.tm_year-100) > 99 ? 01 : timedata.tm_year-100;

	int8_t timezone = 0;
	if(masterConfigurations && timedata.tm_year>1) {
		timezone = masterConfigurations->getTimezone();
	}

	sprintf(buffer, "[%02u/%02u/%02u %02u:%02u:%02u];",
			timedata.tm_mday,
			timedata.tm_mon+1,
			timedata.tm_year,
			(timedata.tm_hour+timezone+24)%24, //we have to sum 24h because modulo operator behaviour is compiler-dependent for negative numbers...
			timedata.tm_min,
			timedata.tm_sec);

	switch(levelInfo){
		case Error:
			strcat(buffer,"ERROR;");
			break;
		case Info:
			strcat(buffer,"INFO;");
			break;
		case Debug:
			strcat(buffer,"DEBUG;");
			break;
		case Warning:
			strcat(buffer,"WARNING;");
			break;
	}

	strcat(buffer,module);
	strcat(buffer,";");

	va_list args;
	va_start(args, format);
	vsnprintf(&buffer[strlen(buffer)],MAX_LOG_SIZE-strlen(buffer)-2, format, args);
	va_end(args);
	strcat(buffer,"\r\n");

#ifndef SEND_LOG_IN_REAL_TIME
	for (size_t i = 0; i <= strlen(buffer); i++)
	{
		vRB_PutBuff(&logRingBuffer, buffer[i]);
	}
#else
	logPrint(buffer);
#endif
}


void logPrintSerial(Log_LevelInfo levelInfo,const char * module,uint8_t *data, uint32_t len){
	char buffer[MAX_LOG_SIZE];
	memset(buffer,0,MAX_LOG_SIZE);

	switch(levelInfo){
	case Error:
		strcat(buffer,"ERROR;");
		break;
	case Info:
		strcat(buffer,"INFO;");
		break;
	case Debug:
		strcat(buffer,"DEBUG;");
		break;
	}

	strcat(buffer,module);
	strcat(buffer,";");

	int bufferLen = strlen(buffer);

	for(uint32_t i=0 ; i<len ; i++){
		if(bufferLen>=MAX_LOG_SIZE-3){
			break;
		}
		buffer[bufferLen++]=data[i];
	}

	buffer[bufferLen++] = '\r';
	buffer[bufferLen++] = '\n';
	buffer[bufferLen] = '\0';

#ifndef SEND_LOG_IN_REAL_TIME
	for (int i = 0; i < bufferLen; i++)
	{
		vRB_PutBuff(&logRingBuffer, buffer[i]);
	}
#else
	logPrint(buffer);
#endif
}


uint32_t logReceiveAvailable() {
    return serialLog ? serialLog->available() : 0;
}

uint8_t logReceive() {
    return serialLog ? serialLog->read() : 0;
}

void logReceiveSize(uint8_t *dest, uint32_t len) {
    if (serialLog) {
        serialLog->readBytes(dest, len);
    }
}

uint8_t logRBAvail() {
    if(logRingBuffer.uiNBytes > 0) { 
        return 1; 
    } else { 
        return 0; 
    }
}

uint8_t getLogRB(){
    return (ucRB_GetBuff(&logRingBuffer));
}

#else 

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void logPrintf(Log_LevelInfo levelInfo, const char *module, const char *format, ...) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    printf("[%02d/%02d/%04d %02d:%02d:%02d] ", 
          tm_info->tm_mday, 
          tm_info->tm_mon + 1, 
          tm_info->tm_year + 1900, 
          tm_info->tm_hour, 
          tm_info->tm_min, 
          tm_info->tm_sec);
    
    switch (levelInfo) {
        case Error:
            printf("ERROR: ");
            break;
        case Info:
            printf("INFO: ");
            break;
        case Debug:
            printf("DEBUG: ");
            break;
        case Warning:
            printf("WARNING: ");
            break;
    }
    printf("%s: ", module);
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void logPrintfFile(Log_LevelInfo levelInfo, const char *module, const char *format, ...) {
    FILE *file = fopen("log.txt", "a");
    if (file == NULL) {
        perror("Failed to open log file");
        return;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    fprintf(file, "[%02d/%02d/%04d %02d:%02d:%02d] ", 
            tm_info->tm_mday, 
            tm_info->tm_mon + 1, 
            tm_info->tm_year + 1900, 
            tm_info->tm_hour, 
            tm_info->tm_min, 
            tm_info->tm_sec);
    
    switch (levelInfo) {
        case Error:
            fprintf(file, "ERROR: ");
            break;
        case Info:
            fprintf(file, "INFO: ");
            break;
        case Debug:
            fprintf(file, "DEBUG: ");
            break;
        case Warning:
            fprintf(file, "WARNING: ");
            break;
    }
    fprintf(file, "%s: ", module);
    
    va_list args;
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);

    fclose(file);
}


#endif