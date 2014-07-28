#include <tcutil.h>
#include <tchdb.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char **argv){
  TCHDB *hdb;
  int ecode;
  int i;
  char s1[17] = {'\0'};
  clock_t start,end;
  if(argc == 1){
    printf("input loop count\n");
    return -1;
  }
  int loop_c = atoi(argv[1]);

  hdb = tchdbnew();

  if(!tchdbopen(hdb, "tokyocabinet.tch", HDBOWRITER | HDBOCREAT)){
    ecode = tchdbecode(hdb);
    fprintf(stderr, "open error: %s\n", tchdberrmsg(ecode));
  }

  start = clock();
  for (i=0;i<loop_c;i++) {
    sprintf(s1, "%016d", i);
    tchdbput2(hdb, s1, "hogehoge");
  }
  end = clock();
  printf("add time = %f[s]\n", (double)(end-start)/CLOCKS_PER_SEC);

  start = clock();
  for (i=0;i<loop_c;i++) {
    sprintf(s1, "%016d", i);
    tchdbget2(hdb, s1);
  }
  end = clock();
  printf("get time = %f[s]\n", (double)(end-start)/CLOCKS_PER_SEC);

  if(!tchdbclose(hdb)){
    ecode = tchdbecode(hdb);
    fprintf(stderr, "close error: %s\n", tchdberrmsg(ecode));
  }

  tchdbdel(hdb);

  return 0;
}
