#include <stdio.h>
#include <ncurses.h>

void main(void) {
    initscr();
    noecho();
    printw("Hello World!\n");
    getch();
    endwin();
}