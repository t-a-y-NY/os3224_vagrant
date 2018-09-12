#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1024];

void sed(int fd, char* name)
{
  int i;
  int n;

  int the_count = 0; // Transylvanian accent: "I am the_count."

  if (fd < 0) {
    for (i = 0; i < sizeof(name); i++) {
      if (name[i] == 't' && name[i+1] == 'h' && name[i+2] == 'e') {
        name[i] = 'x';
        name[i+1] = 'y';
        name[i+2] = 'z';
        the_count++;
        printf(1, name);
        printf(1, "\n");
      }
    }
  }
  else {
    while ( (n = read(fd, buf, sizeof(buf) ) ) > 0) {
      for (i = 0; i < n; i++) {
        if (buf[i] == 't' && buf[i+1] == 'h' && buf[i+2] == 'e') {
          buf[i] = 'x';
          buf[i+1] = 'y';
          buf[i+2] = 'z';
          the_count++;
          printf(1, buf);
          printf(1, "\n");
        }
      }
    }
  }
  

  // if (n < 0) 
  // {
  //   printf(1, "sed: read error\n");
  //   exit();
  // }
  printf(1, "Found and replaced %d occurences.\n", the_count);
}

int main(int argc, char* argv[])
{
  int fd;

  if (argc <= 1) 
  {
    sed(0, "");
    exit();
  }

  int i;
  for (i = 1; i < argc; i++) 
  {
    if ((fd = open(argv[i], 0)) < 0) 
    {
      // printf(1, "sed: cannot open %s\n", argv[i]);
      // exit();
    }
    sed(fd, argv[i]);
    close(fd);
  }

  exit();
}
