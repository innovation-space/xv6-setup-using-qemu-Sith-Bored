#ifndef PROCINFO_H
#define PROCINFO_H

#define PROC_NAME_LEN 16
#define PROC_STATE_LEN 16

struct procinfo {
  int pid;
  int ppid;
  char state[PROC_STATE_LEN];
  char name[PROC_NAME_LEN];
};

#endif
