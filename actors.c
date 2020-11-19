#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

char * key2val(FILE * fkhs, FILE * fp, char * search_term);
char * val2key(FILE * fvhs, FILE * fp, char * search_term);
//char ** key2values(FILE * fkhs, FILE * fp, char * search_term);

char * key2val(FILE * fkhs, FILE * fp, char * search_term) {
  int capacity = get_capacity(fkhs);
  int search_hash = hashfn(search_term, capacity);
  int idx = 0;
  int i = 0;
  char key[STRLEN];
  key[0] = '\0';
  char * val = malloc(sizeof(char) * STRLEN);
  val[0] = '\0';
  while (strcmp(key, search_term) && i < capacity) {
    read_index(fkhs, search_hash, &idx);
    if (idx > -1) {
      read_key(fp, idx, key);
    }
    search_hash++;
    if (search_hash == capacity) {
      search_hash = 0;
    }
    i++;
  }
  if (strcmp(key, search_term)) {
    strcpy(val, "NOT FOUND");
  } else {
    read_val(fp, idx, val);
  }
  return val;
}


char * val2key(FILE * fvhs, FILE * fp, char * search_term) {
  int capacity = get_capacity(fvhs);
  int search_hash = hashfn(search_term, capacity);
  int idx = 0;
  int i = 0;
  char val[STRLEN];
  val[0] = '\0';
  char * key = malloc(sizeof(char) * STRLEN);
  key[0] = '\0';
  while (strcmp(val, search_term) && i < capacity) { // until one loop or search found
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
  return key;
}


int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./actors 'movie name'\n");
    exit(1);
  }
  char * movie_title = argv[1];
  char * title_code;
  char * actor_code;
  char * actor_name;

  FILE * title_kv = fopen("title.basics.kv", "rb");
  FILE * title_vhs = fopen("title.basics.vhs", "rb");
  if (title_kv == NULL || title_vhs == NULL) {
    fprintf(stderr, "%s\n", "Error opening a title basics file");
    exit(-1);
  }

  title_code = val2key(title_vhs, title_kv, movie_title);
  fclose(title_kv);
  fclose(title_vhs);
  // Special version of key2val for multiple entries
  FILE * principals_kv = fopen("title.principals.kv", "rb");
  FILE * principals_khs = fopen("title.principals.khs", "rb");
  if (principals_kv == NULL || principals_khs == NULL) {
    fprintf(stderr, "%s\n", "Error opening a title principals file");
    exit(-1);
  }
  actor_code = key2val(principals_khs, principals_kv, title_code);
  fclose(principals_kv);
  fclose(principals_khs);

  FILE * names_kv = fopen("name.basics.kv", "rb");
  FILE * names_khs = fopen("name.basics.khs", "rb");
  if (names_kv == NULL || names_khs == NULL) {
    fprintf(stderr, "%s\n", "Error opening a name basics file");
    exit(-1);
  }

  actor_name = key2val(names_khs, names_kv, actor_code);
  printf("%s\n", actor_name);
  fclose(names_kv);
  fclose(names_khs);
  free(title_code);
  free(actor_code);
  free(actor_name);
  return(0);
}
