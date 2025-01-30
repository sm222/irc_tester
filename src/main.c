# include "irc_tester.h"

void setColors(void) {
	Colors[0] = RED;
	Colors[1] = GRN;
	Colors[2] = YEL;
	Colors[3] = BLU;
	Colors[4] = MAG;
	Colors[5] = CYN;
	Colors[6] = RESET;
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

void readFile(const char* fileName, t_Setting* sys) {
	const int fd = open(fileName, O_RDONLY);
	if (fd < 0) {
		printError(fileName, sys->verbose);
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
				const int buffSize = len + 20 + (sys->verbose == 2 ? MAX_COLORLEN : 0);
				char verboseLine[buffSize];
				const int verboseB = snprintf(verboseLine, buffSize, "[%s%zu%s]: -> %s", Colors[1], i, Colors[6], line);
				write(STDERR_FILENO, verboseLine, verboseB);
			}
			sendData(line, len, 0);
		}
		free(line);
		usleep(sys->sleep * sys->speed);
	}
	close(fd);
}

void printHelp(void) {
	size_t i = 0;
	fprintf(stderr, "------------------------\n");
	while (__flags[i] && __help[i]) {
		fprintf(stderr, "\n--%-13s -%s\n", __flags[i], __help[i]);
		i++;
	}
	fprintf(stderr, "------------------------\n");
}

void SetSetting(t_Setting *sysSetting, int c) {
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
		sysSetting->verbose = 1;
		break;
	case 'c':
		sysSetting->verbose = 2;
		setColors();
		break;
	case 'h':
		printHelp();
		exit(0);
	default:
		fprintf(stderr, "%s: unknown %c, flag that can be use are %s\n", sysSetting->progameName, c, FLAG_LIST);
		break;
	}
}

/*
void SetSettingVerbose(t_Setting *sysSetting, const char* const arg) {

}
*/

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
		.error = 0
	};
	if (ac >= 2) {
		int i = 1;
		while (i < ac) {
			if (strncmp(av[i], "--", 2) == 0) {
				fprintf(stderr, "here %s\n", av[i + 1]);
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
	return 0;
}