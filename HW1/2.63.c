//
//  main.c
//  2.63
//
//  Created by Anh Mac on 1/15/20.
//  Copyright © 2020 Anh Mac. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

unsigned long srl(unsigned long x, int k) {
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    int w = sizeof(long) << 3;
    int mask = -1 << (w-k); // create a mask with 1s on the highest bits that forms the difference between the right shift and the size of int type
    return xsra & ~mask;
}

int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int) << 3;
    int MSB = x >> (w-1); // extract the most significant bit
    int mask = MSB << (w-k);
    return (~xsrl)^(~mask);
}


int main() {
    return 0;
}
