#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"
#include "assignment6.h"

int len_filename_no_ending(char * str) { // returns the index of the '.'
  return (strlen(str) - 3);
}

int main(int argc, char **argv) {
  FILE * fkhs, fp;
  if (argc != 3) {
    fprintf(stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
    exit(1);
  }
  return 0;
}
