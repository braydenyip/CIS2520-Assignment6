#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"
#include "assignment6.h"

int main(int argc, char **argv) {
  FILE * fvhs, * fp;
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

  char * filename_vhs = replace_file_ending(argv[1], ".vhs");

  fvhs = fopen(filename_vhs, "rb");
  if (fvhs == NULL) {
    fprintf(stderr, "Failed to open the file: %s\n", filename_vhs);
    free(filename_vhs);
    fclose(fp);
    exit(-1);
  }
  int capacity = get_capacity(fvhs);
  int search_hash = hashfn(search_term, capacity);
  int idx = 0;
  int i = 0;
  char val[STRLEN];
  val[0] = '\0';
  char key[STRLEN] = "NOT FOUND";
  while (strcmp(val,search_term) && i < capacity) {
    read_index(fvhs, search_hash, &idx);
    read_val(fp, idx, val);
    search_hash++;
    if (search_hash == capacity) {
      search_hash = 0;
    }
    i++;
  }
  if (i < capacity) {
    read_key(fp, idx, key);
  }
  printf("%s\n", key);

  free(filename_vhs);
  fclose(fvhs);
  fclose(fp);
  return 0;
}
