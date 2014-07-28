#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <groonga.h>
#include <time.h>

#define MAX_VALUE_BYTES 16

int
main(int argc, char **argv)
{
  grn_ctx ctx;

  void *got_value;
  void *value = NULL;
  int added = 0;
  if(argc == 1){
    printf("input loop count\n");
    return -1;
  }
  int loop_c = atoi(argv[1]);

  int i;
  char s1[17] = {'\0'};
  clock_t start,end;
  
  if (grn_init()) {
    fprintf(stderr, "grn_init() failed\n");
    return -1;
  }

  if (grn_ctx_init(&ctx, 0)) {
    fprintf(stderr, "grn_ctx_init() failed\n");
    return -1;
  }

  grn_hash *hash = NULL;
  const char *hash_path = "groonga.grh";

  hash = grn_hash_create(&ctx, hash_path,
                         GRN_TABLE_MAX_KEY_SIZE,
                         MAX_VALUE_BYTES,
                         GRN_OBJ_TABLE_HASH_KEY | GRN_OBJ_KEY_VAR_SIZE);
  if(hash == NULL) {
    hash = grn_hash_open(&ctx, hash_path);
  }

  start = clock();
  for (i=0;i<loop_c;i++) {
    sprintf(s1, "%016d", i);
    grn_hash_add(&ctx, hash, s1, strlen(s1), &value, &added);
    if (added) {
      memcpy(value, "hogehoge", 8);
    }
  }
  end = clock();
  printf("add time = %f[s]\n", (double)(end-start)/CLOCKS_PER_SEC);

  start = clock();
  for (i=0;i<loop_c;i++) {
    sprintf(s1, "%016d", i);
    grn_hash_get(&ctx, hash, s1, strlen(s1), &got_value);
  }
  end = clock();
  printf("get time = %f[s]\n", (double)(end-start)/CLOCKS_PER_SEC);

  grn_hash_close(&ctx, hash);
  
  if (grn_ctx_fin(&ctx)) {
    fprintf(stderr, "grn_ctx_fin() failed\n");
    return -1;
  }

  if (grn_fin()) {
    fprintf(stderr, "grn_fin() failed\n");
    return -1;
  }

  return 0;
}
