#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int main (int argc, char **argv) {
  FILE * fp;
  if (argc != 2){
    fprintf(stderr, "Usage: %s filename.kv capacity\n", "buildidx");
    exit(-1);
  }
  fp = fopen(argv[0], "r+");





  fclose(fp);
  return(0);
}
