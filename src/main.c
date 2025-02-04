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

ssize_t sendData(const char* const line, const size_t byte, int const fd, t_Setting* sys) {
  const size_t buffSize = byte + ft_strlen(sys->format)
  char message[buffSize + 1];
  memmove(message, line, byte);
  memmove(message + byte, sys->format, buffSize - byte);
  message[buffSize] = 0; //not needed but just to be sure
  if (!fd)
    return (write(STDOUT_FILENO, message, buffSize));
  return (send(fd, message, buffSize, 0));
}

void printOpenError(const char* const fileName, int colors) {
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
    verboseB = snprintf(verboseLine, buffSize, "[%s%-4zu%s]: -> %s\n", Colors[1], index, Colors[6], str);
  else {
    verboseB = snprintf(verboseLine, buffSize, "[%s%-4zu%s]: <- %s\n", Colors[2], index, Colors[6], str);
  }
  write(STDERR_FILENO, verboseLine, verboseB);
}




void parseFile(t_Setting* sys, const char** file) {
  size_t i = 0;
  while (file[i]) {
    size_t lineLen = ft_strlen(file[i]);
    if (lineLen && !strchr("#><", file[i][0])) {
      sendData(file[i], lineLen, sys->fd, sys);
      usleep(sys->speed * sys->sleep);
      if (sys->verbose)
        printVerbose(file[i], 0, lineLen, i);
    }
    if (sys->fd && sys->verbose) {
      ssize_t error = 0;
      char*   str = getMessage(sys->fd, sys->readBuffer, &error);
      const   size_t responsLen = ft_strlen(str);
      if (responsLen)
        printVerbose(str, 1, responsLen, 0);
      free(str);
      if (error == -1 && !lineLen) {
        connectionClose(sys->verbose);
        return ;
      }
    }
    i++;
  }
}

void freeLoop(char** splitFile) {
  size_t i = 0;
  while (splitFile[i]) {
    free(splitFile[i]);
    i++;
  }
  free(splitFile);
}

void readFile(const char* fileName, t_Setting* sys) {
  const int fd = open(fileName, O_RDONLY);
  if (fd < 0) {
    printOpenError(fileName, sys->verbose);
    sys->error = 1;
    return ;
  }
  char* line = "";
  char* rawFile = NULL;
  while (line) {
    line = get_next_line(fd);
    rawFile = ft_strjoin(rawFile, line);
    free(line);
  }
  close(fd);
  char** splitFile = ft_split(rawFile, '\n');
  free(rawFile);
  if (!splitFile) {
    perror("malloc");
    exit(2);
  }
  parseFile(sys, (const char**)splitFile);
  freeLoop(splitFile);
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

int main(int ac, const char* const* av) {
  int    i = 1;
  size_t k = 1;
  //
  t_Setting sysSetting = {
    .progameName = av[0],
    .interactive = 0,
    .sleep       = 1000,
    .speed       = 1,
    .verbose     = 0,
    .readBuffer  = 100,
    .error       = 0,
    .port        = 8080,
    .args.av = av,
    .args.i  = &i,
    .args.k  = &k,
    };
  bzero(sysSetting.format, sizeof(char) * FORMAT_BUFF_SIZE);
  memmove(sysSetting.format, DEF_ENDL, strlen(DEF_ENDL));
  bzero(&sysSetting.sock, sizeof(sysSetting.sock));
  if (ac >= 2) {
    while (i < ac) {
      if (strncmp(av[i], "--", 2) == 0) {
        SetSettingVerbose(&sysSetting, av[i] + 2);
        i++;
      }
      else if (av[i] && av[i][0] == '-' && av[i][1] != 0) {
        size_t arglen = strlen(av[i]);
        for (k = 1; k < arglen; k++) {
          SetSetting(&sysSetting);
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
    fprintf(stderr, "%s {file*}\n", av[0]);
  }
  return sysSetting.error;
}