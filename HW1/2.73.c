//
//  main.c
//  2.73
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
    int positiveOverflow = (((x>>31)==0) && ((y>>31)==0) && ((sum>>31)==-1));
    int negativeOverflow = (((x>>31)==-1) && ((y>>31)==-1) && ((sum>>31))==0);
    
    (positiveOverflow && (sum = INT_MAX)) || (negativeOverflow && (sum = INT_MIN));
    return sum;
}


int main() {
    return 0;
}
