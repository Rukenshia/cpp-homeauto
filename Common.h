#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
typedef unsigned long DWORD;

// Development defines
//#define USE_WIRINGPI_LIB

// Log defines
#define Log(s) printf("%s\n", s)
#define Logf(f, s...) printf(f "\n", ## s)

// Other Defines
#define CONFIG_FILE "./config.yml"
#endif
