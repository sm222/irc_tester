#include "irc_tester.h"

void SetColors(void) {
  Colors[0] = RED;
  Colors[1] = GRN;
  Colors[2] = YEL;
  Colors[3] = BLU;
  Colors[4] = MAG;
  Colors[5] = CYN;
  Colors[6] = RESET;
}

void SetSetting(t_Setting *sysSetting) {
  t_args* args = &sysSetting->args;
  const char c = args->av[*args->i][*args->k];
  switch (c) {
  case 'i':
    sysSetting->interactive = true;
    break;
  case 's':
    sysSetting->speed = 100;
    break;
  case 'S':
    sysSetting->speed = 1000;
    break;
  case 'v':
    sysSetting->verbose = sysSetting->verbose > 1 ? 2 : 0;
    break;
  case 'c':
    sysSetting->verbose = 2;
    SetColors();
    break;
  case 'n':
    int fd = openSocket(&sysSetting->sock, sysSetting->port);
    if (fd >= 0)
      sysSetting->fd = fd;
    else {
      close(fd);
      exit(2);
    }
    break;
  case 'h':
    PrintHelp();
    exit(sysSetting->error);
  default:
    fprintf(stderr, "%s: unknown %c, flag that can be use are %s\n", sysSetting->progameName, c, FLAG_LIST);
    sysSetting->error = 1;
    break;
  }
}


// need to add '='
static int same(const char* const s1, const char* const s2) {
  return (strncmp(s1, s2, strlen(s2) + 1));
}

void SetSettingVerbose(t_Setting *sysSetting, const char* const arg) {
  if (same(arg, __flags[0]) == 0) {
    sysSetting->interactive = true;
  }
  else if (same(arg, __flags[1]) == 0) {
    sysSetting->speed = 100;
  }
  else if (same(arg, __flags[2]) == 0) {
    sysSetting->speed = 1000;
  }
  else if (same(arg, __flags[3]) == 0) {
    sysSetting->verbose = sysSetting->verbose > 1 ? 2 : 0;
  }
  else if (same(arg, __flags[4]) == 0) {
    sysSetting->verbose = 2;
  }
  else if (same(arg, __flags[5]) == 0) {
    PrintHelp();
    exit(sysSetting->error);
  }
  else {
    fprintf(stderr, "%s: unknown %s, flag that can be use are \n", sysSetting->progameName, arg);
    for (size_t i = 0; __flags[i]; i++) {
      fprintf(stderr, "--%s\n", __flags[i]);
    }
    // error message here
  }
}
