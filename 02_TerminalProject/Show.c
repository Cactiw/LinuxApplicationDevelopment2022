
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC_CODE 27
#define SPACE_CODE 32


void renderFileWindow(WINDOW* win, char* fileContent, int scrollCnt) {
    werase(win);
    wmove(win, 1, 0);
    char *curLine = fileContent;
    int curLineCnt = 0;
    while (curLine && curLineCnt - scrollCnt < LINES - 1) {
        char *nextLine = strchr(curLine, '\n');
        if (nextLine) *nextLine = '\0';

        // PROCESS CURRENT LINE HERE
        if (curLineCnt >= scrollCnt) {
            wprintw(win, " %.*s\n", COLS - 3,curLine);
        }
        // --

        if (nextLine) *nextLine = '\n';
        curLine = nextLine ? (nextLine + 1) : NULL;

        curLineCnt++;
    }
    box(win, 0, 0);
    wrefresh(win);
}

int count_file_lines(char* fileContent) {
    int res = 0;
    char *curLine = fileContent;
    while (curLine ) {
        char *nextLine = strchr(curLine, '\n');
        if (nextLine) *nextLine = '\0';

        if (nextLine) *nextLine = '\n';
        curLine = nextLine ? (nextLine + 1) : NULL;

        res++;
    }
    return res;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");
    if (NULL == fp) {
        printf("File can't be opened \n");
        return 2;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* fcontent = malloc(size);
    fread(fcontent, 1, size, fp);
    fclose(fp);
//    printf("%s\n", fcontent);

    initscr();
    printw(argv[1]);

    WINDOW *win = newwin(LINES-1, COLS, 1, 0);
    refresh();

    keypad(win, TRUE);
    scrollok (win, TRUE);
    int scrollCnt = 0;
    int fileLines = count_file_lines(fcontent);
    renderFileWindow(win, fcontent, scrollCnt);
    int c = 0;
    while((c = wgetch(win)) != ESC_CODE) {
        if (c == SPACE_CODE && scrollCnt + LINES - 1 < fileLines) {
            scrollCnt++;
        }
        renderFileWindow(win, fcontent, scrollCnt);
    }

    delwin(win);
    endwin();
    free(fcontent);
}
