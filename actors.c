#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "%s\n", "Usage: %s 'movie name'", argv[0]);
    exit(1);
  }

  char[STRLEN] filename = "title.principals.kv";
  return 0;
}
