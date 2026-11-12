
#include "types.h"
#include "stat.h"
#include "user.h"

char*
gettype(int type)
{
  if(type == T_DIR)
    return "Directory";
  if(type == T_FILE)
    return "Regular File";
  if(type == T_DEV)
    return "Device";

  return "Unknown";
}

int
main(int argc, char *argv[])
{
  int i;
  struct stat st;

  if(argc < 2) {
    printf(2, "Usage: stat filename\n");
    exit();
  }

  for(i = 1; i < argc; i++) {
    if(stat(argv[i], &st) < 0) {
      printf(2, "stat: cannot stat %s\n", argv[i]);
      continue;
    }

    printf(1, "\nFile: %s\n", argv[i]);
    printf(1, "Device: %d\n", st.dev);
    printf(1, "Inode: %d\n", st.ino);
    printf(1, "Type: %s\n", gettype(st.type));
    printf(1, "Links: %d\n", st.nlink);
    printf(1, "Size: %d bytes\n", st.size);
  }

  exit();
}
