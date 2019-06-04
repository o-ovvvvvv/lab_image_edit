#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "image_edit.h"

void nega(ppm_image_t *in, ppm_image_t *out){
  int x, y;

  //outのステータス設定
  out->w = in->w;
  out->h = in->h;
  out->max_value = in->max_value;

  //ネガ反転
  for (y = 0; y < in->h; y++)
  {
    for (x = 0; x < in->w; x++)
    {
      POINT_R(out, x, y) = in->max_value - POINT_R(in, x, y);
      POINT_G(out, x, y) = in->max_value - POINT_G(in, x, y);
      POINT_B(out, x, y) = in->max_value - POINT_B(in, x, y);
    }
  }
}

void turn_right(ppm_image_t *in, ppm_image_t *out){
  int x, y;

  //outのステータス設定
  out->h = in->w;
  out->w = in->h;
  out->max_value = in->max_value;

  //右回転
  for (y = 0; y < in->h; y++)
  {
    for (x = 0; x < in->w; x++)
    {
      POINT_R(out, out->w - y, x) = POINT_R(in, x, y);
      POINT_G(out, out->w - y, x) = POINT_G(in, x, y);
      POINT_B(out, out->w - y, x) = POINT_B(in, x, y);
    }
  }
}

void upside_down(ppm_image_t *in, ppm_image_t *out){
  int x, y;

  //outのステータス設定
  out->w = in->w;
  out->h = in->h;
  out->max_value = in->max_value;

  //上下反転
  for (y = 0; y < in->h; y++)
  {
    for (x = 0; x < in->w; x++)
    {
      POINT_R(out, out->w - x, out->h - y) = POINT_R(in, x, y);
      POINT_G(out, out->w - x, out->h - y) = POINT_G(in, x, y);
      POINT_B(out, out->w - x, out->h - y) = POINT_B(in, x, y);
    }
  }
}

void turn_left(ppm_image_t *in, ppm_image_t *out){
  int x, y;

  //outのステータス設定
  out->h = in->w;
  out->w = in->h;
  out->max_value = in->max_value;
  
  //左回転
  for (y = 0; y < in->h; y++)
  {
    for (x = 0; x < in->w; x++)
    {
      POINT_R(out, y, out->h - x) = POINT_R(in, x, y);
      POINT_G(out, y, out->h - x) = POINT_G(in, x, y);
      POINT_B(out, y, out->h - x) = POINT_B(in, x, y);
    }
  }
}

void zoom_in(ppm_image_t *in, ppm_image_t *out){
  //zmiで拡大率指定
  int x, y, zmi = 10;

  //outのステータス設定
  out->w = in->w / zmi;
  out->h = in->h / zmi;
  out->max_value = in->max_value;

  //拡大
  for (y = 0; y < in->h / zmi; y++)
  {
    for (x = 0; x < in->w / zmi; x++)
    {
      POINT_R(out, x, y) = POINT_R(in, x + in->w / 2 - in->w / (2 * zmi), y + in->h / 2 - in->h / (2 * zmi));
      POINT_G(out, x, y) = POINT_G(in, x + in->w / 2 - in->w / (2 * zmi), y + in->h / 2 - in->h / (2 * zmi));
      POINT_B(out, x, y) = POINT_B(in, x + in->w / 2 - in->w / (2 * zmi), y + in->h / 2 - in->h / (2 * zmi));
    }
  }
}

void zoom_out(ppm_image_t *in, ppm_image_t *out){
  //zmoで縮小率指定
  int x, y, i, j, zmo = 10;

  //outのステータス設定
  out->w = in->w / zmo;
  out->h = in->h / zmo;
  out->max_value = in->max_value;

  //縮小
  j = 0;
  for (y = 0; y < in->h / zmo; y++)
  {
    i = 0;
    for (x = 0; x < in->w / zmo; x++)
    {
      POINT_R(out, x, y) = POINT_R(in, i, j);
      POINT_G(out, x, y) = POINT_G(in, i, j);
      POINT_B(out, x, y) = POINT_B(in, i, j);
      i += zmo;
    }
    j += zmo;
  }
}

void slide(ppm_image_t *in, ppm_image_t *out){
  //dirで方向(0が上で時計回りに1,2,3),ratioで移動率設定
  int x, y, dir = 1, ratio = 2;

  out->w = in->w;
  out->h = in->h;
  out->max_value = in->max_value;
  switch (dir){
    case 0:
      for(y = 0; y < in->h / ratio; y++){
        for(x = 0; x < in->w; x++){
          POINT_R(out, x, y) = POINT_R(in, x, y + in->h / ratio);
          POINT_G(out, x, y) = POINT_G(in, x, y + in->h / ratio);
          POINT_B(out, x, y) = POINT_B(in, x, y + in->h / ratio);
        }
      }
      break;

    case 1:
      for(y = 0; y < in->h; y++){
        for(x = 0; x < in->w / ratio; x++){
          POINT_R(out, x, y) = POINT_R(in, x + in->w / ratio, y);
          POINT_G(out, x, y) = POINT_G(in, x + in->w / ratio, y);
          POINT_B(out, x, y) = POINT_B(in, x + in->w / ratio, y);
        }
      }
      break;
    case 2:
      for(y = 0; y < in->h / ratio; y++){
        for(x = 0; x < in->w; x++){
          POINT_R(out, x, y) = POINT_R(in, x, y - in->h / ratio);
          POINT_G(out, x, y) = POINT_G(in, x, y - in->h / ratio);
          POINT_B(out, x, y) = POINT_B(in, x, y - in->h / ratio);
        }
      }
      break;
    case 3:
      for(y = 0; y < in->h; y++){
        for(x = 0; x < in->w / ratio; x++){
          POINT_R(out, x, y) = POINT_R(in, x - in->w / ratio, y);
          POINT_G(out, x, y) = POINT_G(in, x - in->w / ratio, y);
          POINT_B(out, x, y) = POINT_B(in, x - in->w / ratio, y);
        }
      }
      break;
    default:
      exit(4);
  }
}

void zoom_NN(ppm_image_t *in, ppm_image_t *out){
  //scaleで拡大縮小率設定
  int x, y, ori_x, ori_y;
  double scale = 1.2;
   
  //outのステータス設定
  out->w = (int)(in->w * scale);
  out->h = (int)(in->h * scale);
  out->max_value = in->max_value;

  //拡大縮小
    for(y = 0; y < in->h * scale; y++){
      for(x = 0; x < in->w * scale; x++){
        
        ori_x = (int)round(x/scale);
        ori_y = (int)round(y/scale);
        
        if(ori_x < in->w && ori_y < in->h){
          POINT_R(out, x, y) = POINT_R(in, ori_x, ori_y);
          POINT_G(out, x, y) = POINT_G(in, ori_x, ori_y);
          POINT_B(out, x, y) = POINT_B(in, ori_x, ori_y);
        }
     }
   }
}
