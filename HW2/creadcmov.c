long cread(long *xp) {
  long a = -1;
  if (!xp) { // if xp is NULL
    xp = &a; // set xp to address a
  }
  else {
    xp = &xp[a];
  }
  return *xp;
}
