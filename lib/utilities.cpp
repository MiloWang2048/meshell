#include <termios.h>

#include "meshell.h"

string getNotNULLString(int num, ...) {
  va_list valist;
  int i;
  va_start(valist, num);
  char* val = NULL;
  for (i = 0; i < num; i++) {
    val = va_arg(valist, char*);
    if (val)
      break;
  }
  va_end(valist);
  return val ? string(val) : "NULL";
}

char getch(void) {
  char buf = 0;
  struct termios old = {0};
  fflush(stdout);
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  //printf("%c\n", buf);
  return buf;
}

void splashPrint() {
  cout << endl
       << "\e[34mWelcome to meshell v0.1.0."
       << endl
       << "Type 'help' to get some help.\e[0m"
       << endl
       << endl;
}

char** stringVectorToCharMatrix(Args args) {
  char** p = (char**)malloc((args.size() + 1) * sizeof(char*));
  for (int i = 0; i < args.size(); i++) {
    p[i] = (char*)malloc(args[i].size() + 1);
    strcpy(p[i], args[i].c_str());
  }
  p[args.size()] = NULL;
  return p;
}

void freeCharMatrix(char** m) {
  char** p = m;
  while (*p) {
    free(*p);
    p++;
  };
  free(m);
}