#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void sed(int fd, char* name)
{
  int i;
  int n;

  int the_count = 0; // Transylvanian accent: "I am the_count."

  while ((n = read(fd, buf, sizeof(buf))) > 0)
  {
    for (i = 0; i < n; i++)
    {
      if (buf[i] == 't' && buf[i+1] == 'h' && buf[i+2] == 'e')
        the_count++;
    }
  }

  if (n < 0) 
  {
    printf(1, "sed: read error\n");
    exit();
  }
  printf(1, "%d %s\n", the_count, name);
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
      printf(1, "sed: cannot open %s\n", argv[i]);
      exit();
    }
    sed(fd, argv[i]);
    close(fd);
  }

  exit();
}
