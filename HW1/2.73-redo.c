//
//  main.c
//  6.73-redo
//
//  Created by Anh Mac on 1/16/20.
//  Copyright © 2020 Anh Mac. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include <assert.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y) {
    // saturating addition returns TMAX when there is positive overflow
    // x > 0, y > 0, sum < 0
    // saturating addition returns TMIN when there is negative overflow
    // x < 0, y < 0, sum > 0
    int sum = x + y;
    int overflowed = __builtin_add_overflow_p (x, y, (int) 0);
    
    ( (overflowed) && ((x>>31)==0) && (sum=INT_MAX)) || ( (overflowed) && ((x>>31)==-1) && (sum=INT_MIN));
    
    return sum;
}

int main() {
    return 0;
}
