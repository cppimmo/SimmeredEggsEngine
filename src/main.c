#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "log.h"
#include "config.h"

int exit_code = 0;

static void cmdargs(int argc, char **argv);
static void usage();
static void signal_interrupt(int sig);

int main(int argc, char *argv[])
{
	cmdargs(argc, argv);
	/* signal(SIGABRT, signal_);
	signal(SIGFPE, signal_);
	signal(SIGILL, signal_);
	signal(SIGINT, signal_);
	signal(SIGSEGV, signal_);
	signal(SIGTERM, signal_); */
	puts("Hello World!");
	return exit_code;
}

void cmdargs(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i) {
	    printf("Testing argument[%d]: %s\n", i, argv[i]);
	}
}

void usage()
{
	printf("Usage: starshipfleet: \n");
	exit(1); // okay to exit no initialization done
}

void signal_handler(int signum)
{

}
