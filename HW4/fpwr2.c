#include <stdio.h>
#include <assert.h>
#include <math.h>

static float u2f(unsigned u) {
  // converting unsigned to float
  union { // union stores both values at the same starting address, so it would have the same bit representation
    float fl;
    unsigned uns;
  } x;
  x.fl=0;
  x.uns=u;
  return x.fl; // returning the float variable of the union will return the same bits as the unsigned variable, but it will be interpreted as float by the program.
}

float fpwr2(int x){

  /* Result exponent and fraction */
  unsigned exp, frac;
  unsigned u;

  if (x < -149) { // 2-pow(2,7)-23
    // 0 0000 0000 0000 0000 0000 0000 0000 001
    // exp = 0 -> Denormalized -> E = 1 - Bias = 1 - (2^7-1) = -126
    // Smallest value = 2^-23 * 2*(-126) = 2^-149
    /* Too small. Return 0.0 */
    exp = 0;
    frac = 0;
  } else if (x < -126) {
    /* Denormalized result */
    // Smallest value before changing to denomarlized form
    // 0 0000 0001 0000 0000 0000 0000 0000 000
    // E = e - BIAS = 1 - (2^7-1) = 2 - 2^7 = -126
    exp = 0;
    /*
      E = 1 - BIAS = 1 - (2^7 - 1) = 2 - 2^7 = -126
      2^x = M * 2^E
      frac = M = 2^x / (2^-23 * 2^E) = 2^(x) / (2^-23 + 2^(-126))
      = x+23+126 = x + 149
     */
    frac = 1 << (x+149);
  } else if (x < 128) { 
    /* Normalized result */
    /*
      Largest normalized value: 0 1111 1111 .....
      E = e - BIAS = (2^8 - 1) - (2^7-1) = 2^8 - 2^7 = 128
      e = E + BIAS = x + (2^7-1) = x + 127
     */
    exp = x+127;
    frac = 0;
  } else {
    /* Too big. Return +oo */
    exp = 255; // exp = 11111111
    frac = 0; // frac = 000..000
  }

  /*Pack exp and frac into 32 bits */
  u = exp << 23 | frac;
  /* Return as float */
  return u2f(u);
}

int main() {
  assert(fpwr2(0) == powf(2,0));
  assert(fpwr2(1) == powf(2,1));
  assert(fpwr2(100) == powf(2,100));
  assert(fpwr2(-100) == powf(2,-100));
  assert(fpwr2(10000) == powf(2,10000));
  return 0;
}
