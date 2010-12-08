#ifndef _SCRASHME_H
#define _SCRASHME_H 1

#include <stdio.h>

#ifndef S_SPLINT_S
#define __unused__ __attribute((unused))
#else
#define __unused__ /*@unused@*/
#endif

struct arglist {
	unsigned int num;
	unsigned int values[1024];
};

struct syscalltable {
	char name[80];
	unsigned int num_args;
	void (*sanitise)(
		unsigned long *,
		unsigned long *,
		unsigned long *,
		unsigned long *,
		unsigned long *,
		unsigned long *);
	unsigned int flags;

	unsigned int arg1type;
	unsigned int arg2type;
	unsigned int arg3type;
	unsigned int arg4type;
	unsigned int arg5type;
	unsigned int arg6type;

	char *arg1name;
	char *arg2name;
	char *arg3name;
	char *arg4name;
	char *arg5name;
	char *arg6name;

	unsigned int low1range, hi1range;
	unsigned int low2range, hi2range;
	unsigned int low3range, hi3range;
	unsigned int low4range, hi4range;
	unsigned int low5range, hi5range;
	unsigned int low6range, hi6range;

	struct arglist arg1list;
	struct arglist arg2list;
	struct arglist arg3list;
	struct arglist arg4list;
	struct arglist arg5list;
	struct arglist arg6list;
};

extern struct syscalltable *syscalls;

extern unsigned int page_size;

extern char *page_zeros;
extern char *page_0xff;
extern char *page_rand;

#define RED	"[1;31m"
#define GREEN	"[1;32m"
#define YELLOW	"[1;33m"
#define BLUE	"[1;34m"
#define MAGENTA	"[1;35m"
#define CYAN	"[1;36m"
#define WHITE	"[1;37m"

extern const char *logfilename;
extern FILE *logfile;

#define writelog(...) do {      \
	logfile = fopen(logfilename, "a"); \
	if (!logfile) { \
		perror("couldn't open logfile\n"); \
		exit(EXIT_FAILURE); \
	} \
	fprintf(logfile, ## __VA_ARGS__); \
	fflush(logfile); \
	fsync(fileno(logfile)); \
	fclose(logfile); \
} while (0)

#define writelog_nosync(...) do {      \
	logfile = fopen(logfilename, "a"); \
	if (!logfile) { \
		perror("couldn't open logfile\n"); \
		exit(EXIT_FAILURE); \
	} \
	fprintf(logfile, ## __VA_ARGS__); \
	fclose(logfile); \
} while (0)

#endif	/* _SCRASHME_H */
