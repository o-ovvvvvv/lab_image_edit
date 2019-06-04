#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "image_edit.h"

void read_ppm(FILE *fp, ppm_image_t *p); //ファイル読み込み
void write_ppm(FILE *fp, ppm_image_t *p); //ファイル書き込み

int main(){
  ppm_image_t image_in,image_out; //入力と出力の画像構造体を宣言
  FILE *fpr, *fpw; //ファイルポインタ

  //ファイル操作
  fpr=fopen("yotsuba_shiogama.ppm", "r");
  if(fpr==NULL){
    fprintf(stderr, "%s can not open.\n", "yotsuba_shiogama.ppm");
    exit(1);
  }
  fpw=fopen("output.ppm", "w");
  if(fpw==NULL){
    fprintf(stderr, "%s can not open.\n", "output.ppm");
    exit(2);
  }
  
  //ファイル読み込み
  read_ppm(fpr, &image_in);

  //画像処理
  //nega(&image_in, &image_out);
  //turn_right(&image_in, &image_out);
  //upside_down(&image_in, &image_out);
  //turn_left(&image_in, &image_out);
  //zoom_in(&image_in, &image_out);
  //zoom_out(&image_in, &image_out);
  //slide(&image_in, &image_out);
  zoom_NN(&image_in, &image_out);
  
  //ファイル書き込み
  write_ppm(fpw, &image_out);

  //ファイル操作終了
  fclose(fpr);
  fclose(fpw);

  return 0;
}

void read_ppm(FILE *fp, ppm_image_t *p){
  char line[128];
  char id[128];
  int i;

  fgets(line, 128, fp);

  while(line[0]=='#'){ fgets(line, 128, fp);} //コメントスキップ

  sscanf(line, "%s", id);

  // 画像形式チェック
  if(strncmp("P6",id,128)!=0){ 
    fprintf(stderr, "Sorry. I can read only P6 image.\n");
    exit(3);
  }

  fgets(line, 128, fp);

  while(line[0]=='#'){ fgets(line, 128, fp);} //コメントスキップ

  sscanf(line, " %d %d ", &(*p).w, &(*p).h); //幅と高さを読み込む
 
  fgets(line, 128, fp);

  while(line[0]=='#'){ fgets(line, 128, fp);} //コメントスキップ

  //画素値の最大を読み込む
  (*p).max_value=atoi(line);

  //RGB画素値を読み込む
  for(i=0; i<(*p).w * (*p).h; i++){
    fread( &(*p).r[i], 1, 1, fp);
    fread( &(*p).g[i], 1, 1, fp);
    fread( &(*p).b[i], 1, 1, fp);
  }
}

void write_ppm(FILE *fp, ppm_image_t *p){
  int i;
  
  //ステータス書き込む
  fprintf(fp, "%s\n", "P6");
  fprintf(fp, " %d %d \n", (*p).w, (*p).h);
  fprintf(fp, " %d ", (*p).max_value);

  //画素値書き込む
  for(i=0; i<(*p).w * (*p).h; i++){
    fwrite( &(*p).r[i], 1, 1, fp);
    fwrite( &(*p).g[i], 1, 1, fp);
    fwrite( &(*p).b[i], 1, 1, fp);
  }
}
