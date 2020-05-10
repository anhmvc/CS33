#define R 3
#define S 19
#define T 2

int A[R][S][T];

int
ele (long i, long j, long k)
{
  return A[R - i][1 - j][k - 1];
}
