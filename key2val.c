#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"
#include "assignment6.h"

int main(int argc, char **argv) {
  FILE * fkhs, * fp;
  if (argc != 3) {
    fprintf(stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
    exit(1);
  }

  char * search_term = argv[2];

  fp = fopen(argv[1], "rb"); // Open filename.kv for reading
  if (fp == NULL) {
    fprintf(stderr, "Failed to open the file: %s\n", argv[1]);
    exit(-1);
  }

  char * filename_khs = replace_file_ending(argv[1], ".khs");

  fkhs = fopen(filename_khs, "rb");
  if (fkhs == NULL) {
    fprintf(stderr, "Failed to open the file: %s\n", filename_khs);
    free(filename_khs);
    fclose(fp);
    exit(-1);
  }
  int capacity = get_capacity(fkhs);
  int search_hash = hashfn(search_term, capacity);
  printf("%d\n", search_hash);

  free(filename_khs);
  fclose(fkhs);
  fclose(fp);
  return 0;
}
