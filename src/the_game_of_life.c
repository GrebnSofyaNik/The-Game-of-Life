#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define M 25
#define N 80
#define LIFE '*'
#define CLEAR ' '
#define ISALIVE 1
#define ISDEAD -1
#define DELAY 200000
#define MAXDELAY 500000000
#define MINDELAY 50000
#define DELAYSTEP 10000

void clearTable(int table[M][N]);
void showTable(int table[M][N], int time);
void evalute(int table[M][N], int tableNext[M][N]);
void sumField(int table[M][N], int m, int n, int *l);
void copyarray(int table[M][N], int tableNext[M][N]);
void input(int a[M][N]);
void handleInput(int *exit, int *delayMsec);

int main() {
  int table[M][N];
  int tableNext[M][N];
  int exitStatus = 0;
  int time = DELAY;

  clearTable(table);
  clearTable(tableNext);
  input(table);
  if (freopen("/dev/tty", "r", stdin) == NULL) {
    printf("n/a");
  } else {
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    while (exitStatus != 1) {
      clear();
      usleep(time);

      showTable(table, time);
      evalute(table, tableNext);
      copyarray(tableNext, table);
      clearTable(tableNext);
      handleInput(&exitStatus, &time);
      refresh();
    }
  }
  initscr();
  noecho();
  nodelay(stdscr, TRUE);
  while (exitStatus != 1) {
    clear();
    usleep(time);

    showTable(table, time);
    evalute(table, tableNext);
    copyarray(tableNext, table);
    clearTable(tableNext);
    handleInput(&exitStatus, &time);
    refresh();
  }
  endwin();
  return 0;
}

void clearTable(int table[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      table[i][j] = ISDEAD;
    }
  }
}
void showTable(int table[M][N], int time) {
  clear();
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      char temp;
      if (table[i][j] == ISALIVE) {
        temp = LIFE;
      } else {
        temp = CLEAR;
      }
      if (j == N - 1) {
        printw("%c\n", temp);
      } else {
        printw("%c", temp);
      }
    }
  }
  printw(
      "\n-- To change delay use +/- keys (q) - EXIT ------ Now delay is: %3d "
      "msec ----\n",
      time / 1000);
}

void evalute(int table[M][N], int tableNext[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int l = 0;
      sumField(table, i, j, &l);
      if (table[i][j] == ISALIVE) {
        if (l < 2 || l > 3) {
          tableNext[i][j] = ISDEAD;
        } else {
          tableNext[i][j] = ISALIVE;
        }
      }
      if (table[i][j] == ISDEAD) {
        if (l == 3) {
          tableNext[i][j] = ISALIVE;
        } else {
          tableNext[i][j] = ISDEAD;
        }
      }
    }
  }
}

void sumField(int table[M][N], int m, int n, int *l) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int mt, nt;
      mt = (i + m + M) % M;
      nt = (j + n + N) % N;
      if (!(i == 0 && j == 0))
        if (table[mt][nt] == ISALIVE) (*l)++;
    }
  }
}

void copyarray(int a[M][N], int b[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      b[i][j] = a[i][j];
    }
  }
}

void input(int a[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int t;
      scanf("%d", &t);
      if (t == 1) a[i][j] = ISALIVE;
    }
  }
}

void handleInput(int *exit, int *time) {
  switch (getch()) {
    case 'q':
      *exit = 1;
      break;

    case '+':
      if (*time < MAXDELAY) *time += DELAYSTEP;
      break;

    case '-':
      if (*time > MINDELAY) *time -= DELAYSTEP;
      break;

    default:
      break;
  }
}
