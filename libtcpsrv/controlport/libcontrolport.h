#ifndef CONTROL_PORT_H
#define CONTROL_PORT_H

#include <stdlib.h>

/* control port command callback, and its allowed return values */
typedef int (cp_cmd_f)(void *cp, int argc, char **argv, void *data);
#define CP_OK    ( 0)  // normal  
#define CP_CLOSE (-1)  // tells library to disconnect client

/******************************************************************************
 * cp_init:     lib creates a unix domain socket, gives app listener fd to poll
 * cp_add_cmd:  app registers additional command
 *              in command callback, return CP_OK or CP_CLOSE to close client
 * cp_service:  app should call whenever listener fd or a client fd is readable
 *              returns fd for app to poll (if > 0)
 *              returns fd to stop polling (if < 0)
 * cp_fini:     closes the control port, terminates any clients
 * cp_printf:   used inside a command callback
 *****************************************************************************/
void *cp_init(char *path, int *fd);
void  cp_add_cmd(void*, char *name, cp_cmd_f *cmd, char *help, void *data);
int   cp_service(void*, int fd);
void  cp_fini(void*);
void  cp_printf(void *, char *fmt, ...);

#endif 
