# include "irc_tester.h"

const char* Colors[] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  NULL
};

void printHelp(void) {
  size_t i = 0;
  fprintf(stderr, "------------------------");
  while (__flags[i] && __help[i]) {
    fprintf(stderr, "\n--%-14s -%s\n", __flags[i], __help[i]);
    i++;
  }
  fprintf(stderr, "------------------------\n");
}

ssize_t sendData(const char* const line, const size_t byte, int const fd) {
  if (!fd)
    return (write(STDOUT_FILENO, line, byte));
  return (send(fd, line, byte, 0));
}

void printError(const char* const fileName, int colors) {
  size_t errmsg = strlen(fileName) + ERRORMSG + (colors == 2 ? MAX_COLORLEN : 0);
  char fileNameError[errmsg];
  bzero(&fileNameError, errmsg);
  snprintf(fileNameError, errmsg - 1, "%sopen %s%s", Colors[0], fileName, Colors[6]);
  perror(fileNameError);
}

void printVerbose(const char* const str, const int mode, const size_t len, const size_t index) {
  const size_t buffSize = len + 20 + (MAX_COLORLEN * 2);
  char verboseLine[buffSize];
  int verboseB = 0;
  if (!mode)
    verboseB = snprintf(verboseLine, buffSize, "[%s%-3zu%s]: -> %s", Colors[1], index, Colors[6], str);
  else {
    verboseB = snprintf(verboseLine, buffSize, "[%s%-3zu%s]: <- %s", Colors[2], index, Colors[6], str);
  }
  write(STDERR_FILENO, verboseLine, verboseB);
}

void readFile(const char* fileName, t_Setting* sys) {
  const int fd = open(fileName, O_RDONLY);
  if (fd < 0) {
    printError(fileName, sys->verbose);
    sys->error = 1;
    return ;
  }
  size_t i = 0;
  char* line = "";
  while (line) {
    line = get_next_line(fd);
    i++;
    if (line && (line[0] != '#' && line[0] != '\n')) {
      const size_t len = strlen(line);
      if (sys->verbose) {
        printVerbose(line, 0, len, i);
      }
      sendData(line, len, 0);
    }
    free(line);
    usleep(sys->sleep * sys->speed);
  }
  close(fd);
}

void userInput(void) {
  char* user = "";
  fprintf(stderr, "user input mode:\n");
    while (user) {
      write(STDERR_FILENO, ">", 1);
      user =  get_next_line(STDIN_FILENO); //user input
      if (user) {
        write(STDOUT_FILENO, user, strlen(user));
        free(user);
      }
    }
}

int main(int ac, char** av) {
  t_Setting sysSetting = {
    .progameName = av[0],
    .interactive = 0,
    .sleep = 1000,
    .speed = 1,
    .verbose = 0,
    .readBuffer = 100,
    .error = 0,
  };
  bzero(&sysSetting.sock, sizeof(sysSetting.sock));
  if (ac >= 2) {
    int i = 1;
    while (i < ac) {
      if (strncmp(av[i], "--", 2) == 0) {
        SetSettingVerbose(&sysSetting, av[i] + 2);
        i++;
      }
      else if (av[i] && av[i][0] == '-' && av[i][1] != 0) {
        size_t arglen = strlen(av[i]);
        for (size_t k = 1; k < arglen; k++) {
          SetSetting(&sysSetting, av[i][k]);
        }
      }
      else {
        readFile(av[i], &sysSetting);
      }
      i++;
    }
    if (sysSetting.interactive)
      userInput();
    else
      sleep(2);
  }
  else {
    fprintf(stderr, "%s {file*}\n" , av[0]);
  }
  return sysSetting.error;
}