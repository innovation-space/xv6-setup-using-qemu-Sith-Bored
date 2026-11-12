#include "types.h"
#include "stat.h"
#include "user.h"
#include "procinfo.h"
#include "param.h"

int
main(void)
{
  struct procinfo procs[NPROC];
  int result;

  result = getprocs(procs, NPROC + 1);

  if(result == -1)
    printf(1, "PASS: Invalid max rejected\n");
  else
    printf(1, "FAIL: Invalid max accepted\n");

  exit();
}
