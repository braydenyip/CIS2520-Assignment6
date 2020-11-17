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
  int idx = 0;
  int i = 0;
  char key[STRLEN];
  key[0] = '\0';
  char val[STRLEN] = "NOT FOUND";
  while (strcmp(key,search_term) && i < capacity) {
    read_index(fkhs, search_hash, &idx);
    read_key(fp, idx, key);
    search_hash++;
    if (search_hash == capacity) {
      search_hash = 0;
    }
    i++;
  }
  if (i < capacity) {
    read_val(fp, idx, val);
  }
  printf("%s\n", val);

  free(filename_khs);
  fclose(fkhs);
  fclose(fp);
  return 0;
}
