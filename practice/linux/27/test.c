#include <func.h>

void handler(int signum){
  printf("before signum = %d\n",signum);
  sleep(5);
  printf("after signum = %d\n",signum);
}

int main(){
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = handler;
  act.sa_flags = SA_RESTART;
  sigaction(SIGINT,&act,NULL);
  sigaction(SIGQUIT,&act,NULL);
  char buf[1024] = {0};
  read(STDIN_FILENO,buf,sizeof(buf));
  printf("buf = %s\n",buf);
  return 0;
}

