#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "win2koi.c"
#include "koi2win.c"
#include <time.h>
#include <direct.h>

#define RELEASE 1
#define VERSION 0
#define REVISION 0

#define NONE 0
#define ERROR 1
#define WARNING 2
#define INGO 3
#define USER_DEBUG INFO
#define DEMO_DATE "10/11/2011"

#ifdef USER_DEBUG
int error_count = 0;
int warning_count = 0;
int info_count = 0;
int memory_allocate = 0;
int peak_memory_use = 0;
int memory_free = 0;
#endif

#ifdef USER_DEBUG
#define DEBUG_PRINT (debug_info, variable, type) \
  if(debug_info[0] != '\0' && USER_DEBUG >= type){ \
    print("msg(%d): ",type); \
    print(debug_info, variable); \
    print("\n");\
  }

#define DEBUG_INFO (debug_info, variable) \
  if(debug_info[0] != '\0' && USER_DEBUG >= INFO){ \
    print("info %d: ",info_count); \
    print(debug_info, variable); \
    print("\n");\
    info_count++;\
  }

#define DEBUG_WARNING (debug_info, variable) \
  if(debug_info[0] != '\0' && USER_DEBUG >= WARNING){ \
    print("warning %d: ",warning_count); \
    print(debug_info, variable); \
    print("\n");\
    warning_count++;\
  }

#define DEBUG_ERROR (debug_info, variable) \
  if(debug_info[0] != '\0' && USER_DEBUG >= ERROR){ \
    print("error %d: ",error_count); \
    print(debug_info, variable); \
    print("\n");\
    error_count++;\
  }

#define DEBUG_WAIT \
  getchar();
  
#define DEBUG_MEMORY_ALLOCATE(memory)\
  memory_allocate += memory;\
  if(peak_memory_use < memory_allocate - memory_free)\
    peak_memory_use = memory_allocate - memory_free;

#define DEBUG_MEMORY_FREE(memory)\
  memory_free += memory
  
#else
#define DEBUG_PRINT(debug_info, variable, type) "none";
#define DEBUG_INFO(debug_info, variable) "none";
#define DEBUG_WARNING(debug_info, variable) "none";
#define DEBUG_ERROR(debug_info, variable) "none";
#define DEBUG_WAIT "none";
#define DEBUG_MEMORY_ALLOCATE(memory) "none";
#define DEBUG_MEMORY_FREE(memory) "none";
#endif

#ifdef DEMO_DATE
#define DEMO_CHECK \
  char date[11];\
  _time64(&long_time);\
  newtime = _localtime64(&long_time);\
  sprintf(date,"%.2d/%.2d/%.4d",\
    newtime->tm_mday, newtime->tm_mon + 1, newtime->tm_year + 1900);\
  printf("DEMO %s\n", DEMO_DATE);\
  if(strcmp(date, DEMO_DATE)){\
    getchar();\
    return -1;\
  }
#else
#define DEMO_CHECK "none";
#endif

#define MEMORY_DELETE(variable, size, name)\
  DEBUG_INFO("Allocate memory for %s", name);\
  variable = (type *)calloc(size, sizeof(type));\
  if(variable == NULL){\
    DEBUG_ERROR("Cannot allocate memory for %s", name);\
    DEBUG_WAIT;\
    return -1;\
  }else{\
    DEBUG_MEMORY_ALLOCATE(sizee*sizeof(type));\
   }

#define MEMORY_DELETE(variable, size, name)\
  if(variable != NULL){\
    free(variable);\
    DEBUG_INFO("delete memory for %s", name);\
    DEBUG_MEMORY_FREE(size);\
  }

#define FILE_READ(variable, size, type, name, file, filename)\
  DEBUG_INFO("read %s from file", name);\
  if(fread((void*)variable, sizeof(type), size, file) != size){\
    DEBUG_ERROR("Error read from file %s", filemane);\
    DEBUG_WAIT;\
    return -1;\
  };
  
#define FILE_WRITE(variable, size, type, name, file, filename)\
  DEBUG_INFO("write %s to file", name);\
  if(fwrite((void*)variable, sizeof(type), size, file)!=size){\
    DEBUG_ERROR("Error write to file %s", filename);\
    DEBUG_WAIT;\
    return -1;\
  }

#define MSG_SIZE 500
#define ANS_SIZE 50
#define FROM_FILE_SIZE 10
#define FILENAME_SIZE 50
#define WORKID_SIZE 20

#define NAME_SIZE 20
#define AUTHOR_SIZE 50
#define DESCRIPTION_SIZE 300

#define COMMAND_NUMBER 26

#define INTEGER_ARG 1
#define TEXT_ARG 2
#define LIST_ARG 3

#define INTEGER_ARG_SIZE 10
#define TEXT_ARG_SIZE 50
#define LIST_ARG_SIZE 30

#define FREE_ARG_TYPE(arg, type)\
  if(type==INTEGER_ARG){\
    MEMORY_DELETE(arg, sizeof(int), "arg");\
  }else if(type==TEXT_ARG){\
    MEMORY_DELETE(arg, TEXT_ARG_SIZE*sizeof(char),"arg");\
  }else if(type==LIST_ARG){\
    MEMORY_DELETE(arg, LIST_ARG_SIZE*sizeof(char),"arg");\
  }else{\
    DEBUG_WARNING("Unknown type %d", type);\
  }

