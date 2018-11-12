#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void sighandler( int signo){
  if( signo == SIGINT){
    int error = open("error_desc.txt", O_CREAT | O_WRONLY, 00777);
    if( error < 0)
      printf("opening file error: %s\n", strerror(errno));
    char error_message[256] = "program exited due to SIGINT\n";
    int bytes_written = write( error, error_message, 256);
    if( bytes_written < 0)
      printf("writing to file error: %s\n", strerror(errno));
    close( error);
    exit(0);
  }
  if( signo == SIGUSR1)
    printf( "parent pid: %d\n", getppid());  
}

int main(){
  signal( SIGINT, sighandler);
  signal( SIGUSR1, sighandler);
  int i = 1;
  while( i){
    printf( "hello, i'm: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
