#include <stdio.h>
#include <unistd.h>
#include <curses.h>

#define MAXBUFSIZE 4096

int main(int argc, char *argv[]) {
    char buf[MAXBUFSIZE];
    int buf_size = read(STDIN_FILENO, buf, MAXBUFSIZE);
    printf("%s", buf);
}