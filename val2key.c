#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int len_filename_no_ending(char * str);
char * replace_file_ending(char * fn, char * ending);

int len_filename_no_ending(char * str) { // returns the index of the '.'
  return (strlen(str) - 3);
}

char * replace_file_ending(char * fn, char * ending) {
  int l = strlen(fn) + 1;
  char * fn_new = calloc(l+1, sizeof(char));
  strcpy(fn_new,fn);
  fn_new[len_filename_no_ending(fn)] = '\0';
  strcat(fn_new, ending);
  return fn_new;
}


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
  char key[STRLEN];
  key[0] = '\0';
  while (strcmp(val, search_term) && i < capacity) {
    read_index(fvhs, search_hash, &idx);
    if (idx > -1) {
      read_val(fp, idx, val);
    }
    search_hash++;
    if (search_hash == capacity) {
      search_hash = 0;
    }
    i++;
  }
  if (strcmp(val, search_term)) {
    strcpy(key, "NOT FOUND");
  } else {
    read_key(fp, idx, key);
  }
  printf("%s\n", key);

  free(filename_vhs);
  fclose(fvhs);
  fclose(fp);
  return 0;
}
