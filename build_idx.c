#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int main (int argc, char **argv) {
  FILE * fp;
  if (argc != 3){
    fprintf(stderr, "Usage: %s filename.kv capacity\n", argv[0]);
    exit(-1);
  }
  fp = fopen(argv[1], "r+");





  fclose(fp);
  return(0);
}
