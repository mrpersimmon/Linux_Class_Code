#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>

#define INFILE "./in.txt"
#define OUTFILE "./out.txt"
#define MODE S_IRUSR|S_IWUSER|S_IRGRP|S_IWGRP|S_IROTH

int main()
{
	int in, out;
	char buf[1024];
	memset(buf, 0, 1024);
	in = open(INFILE, O_RDONLY);
	if(in < 0){
		sprintf(stderr, "failed to open %s, reason(%s)\n", INFILE, strerror(errno));
	return 1;
	}
	out = open(OUTFILE, O_WRONLY|O_CREAT|O_TRUNC, MODE);
	if(out < 0){
		sprintf(stderr, "failed to open %s, reason(%s)\n", OUTFILE, strerror(errno));
	return 1;
	}
	fork();
	while(read(in, buf, 2) > 0){
		printf("%d: %s", getpid(), buf);
		sprintf(buf, "%d Hello World!\n", getpid());
		write(out, buf, strlen(buf));
		sleep(1);
		memset(buf, 0, 1024);
	}	
}
