void zoom_out_NN(ppm_image_t *in, ppm_image_t *out){
  int x, y, i, j, m, n, zmo = 4, sum, ave;
  
  out->w = in->w / zmo;
  out->h = in->h / zmo;
  out->max_value = in->max_value;

  n = 0;
  for(y = 0; y < in->h / zmo; y++){
    m = 0;
    for(x = 0; x < in->w / zmo; x++){
      sum = 0;
      for(j = 0; j < zmo; j++){
        for(i = 0; i < zmo; i++){
          sum += m + i + (n + j) * in->w;
        }
      }
      if(sum % 2 == 1){
        ave = sum / (zmo * zmo);
      }
      else if(sum % 2 == 0){
        ave = sum / (zmo * zmo) - in->w / 2;
      }

      POINT_R(out,x,y) = in->r[ave];
      POINT_G(out,x,y) = in->g[ave];
      POINT_B(out,x,y) = in->b[ave];

      m += zmo;
    }
    n += zmo;
  }

}