#ifndef WIPEINTERFACE_H
#define WIPEINTERFACE_H

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

//int start_wipe(char* path_name, int isdir);
//int mainA(int argc, char **argv);
int destroy_interface(const char* path,const char flag);
//void EmitSmsToUi(char* content);

#ifdef __cplusplus
}
#endif


#endif // WIPEINTERFACE_H
