#include "types.h"
#include "stat.h"
#include "user.h"
#include "procinfo.h"
#include "param.h"

int
main(void)
{
  struct procinfo procs[NPROC];
  int n, i;

  n = getprocs(procs, NPROC);

  if(n < 0){
    printf(2, "ps: getprocs failed\n");
    exit();
  }

  printf(1, "PID\tPPID\tSTATE\t\tNAME\n");

  for(i = 0; i < n; i++){
    printf(1, "%d\t%d\t%s\t\t%s\n",
           procs[i].pid,
           procs[i].ppid,
           procs[i].state,
           procs[i].name);
  }

  exit();
}
