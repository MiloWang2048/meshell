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