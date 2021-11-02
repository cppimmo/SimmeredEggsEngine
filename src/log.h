#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdbool.h>

#define LOG_FILE "log/log.txt"
static FILE *pLogFile = NULL;

bool LogOpen(const char *filename);
void LogWrite(const char *str);
bool LogClose();

#endif // LOG_H
