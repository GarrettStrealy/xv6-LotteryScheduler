#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

void spin()
{
  int i;
  for(i = 0; i <= 100000; i++){ }
}

void print(struct pstat *ps)
{
  int i;
  int j = 0;
  for(i = 0; i < NPROC; i++){
    if(ps->inuse[i]){
      j++;
    }
    if(ps->inuse[i] && j > 3){
      printf(1, "%d ", ps->ticks[i]);
    }
  }
  printf(1,"\n");
}

int
main(int argc, char *argv[])
{
  int tickets[3];
  tickets[0] = 100;
  tickets[1] = 200;
  tickets[2] = 300;
  
  int i;
  for (i = 0; i < 3; i++){
    if(fork() == 0){  
      settickets(tickets[i]);
      
      int k = 0;
      while (k < 10000){
        struct pstat ps;
	spin();
	getpinfo(&ps);
        print(&ps);
      }
    }
  }
  while(wait() > 0);
  exit();
}
