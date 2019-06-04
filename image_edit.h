/* edit_function.h */
#ifndef EDIT_FUNCTION
#define EDIT_FUNCTION

// 画面のサイズ
#define MAX_WIDTH 2048
#define MAX_HEIGHT 2048

//画像の座標に対する各画素値をわかりやすく表示するためのマクロ
#define POINT_R(IMAGE, X, Y) (IMAGE->r[(X) + ((Y)*(IMAGE->w))])
#define POINT_G(IMAGE, X, Y) (IMAGE->g[(X) + ((Y)*(IMAGE->w))])
#define POINT_B(IMAGE, X, Y) (IMAGE->b[(X) + ((Y)*(IMAGE->w))])

struct ppm_image{
  int w; //幅
  int h; //高さ
  int max_value; //画素値の最大
  unsigned char r[MAX_WIDTH * MAX_HEIGHT]; //赤の画素値
  unsigned char g[MAX_WIDTH * MAX_HEIGHT]; //緑の画素値
  unsigned char b[MAX_WIDTH * MAX_HEIGHT]; //青の画素値
};

typedef struct ppm_image ppm_image_t;

void nega(ppm_image_t *in, ppm_image_t *out); //ネガ画像
void turn_right(ppm_image_t *in, ppm_image_t *out); //右回転
void upside_down(ppm_image_t *in, ppm_image_t *out); //上下反転
void turn_left(ppm_image_t *in, ppm_image_t *out); //左回転
void zoom_in(ppm_image_t *in, ppm_image_t *out); //拡大
void zoom_out(ppm_image_t *in, ppm_image_t *out); //縮小
void slide(ppm_image_t *in, ppm_image_t *out); //平行移動
void zoom_NN(ppm_image_t *in, ppm_image_t *out); //最近傍法での拡大縮小

#endif

