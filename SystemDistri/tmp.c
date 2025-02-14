#include <stdio.h>
#include <stdlib.h>

int _factoriel(int value, int tmp, int res) {
    if (value == tmp-1) return res;
    else _factoriel(value, tmp+1, res*tmp);
}

int factoriel(int value) {
    return _factoriel(value, 1, 1);
}



int main(int argc, char *argv[])
{
  printf("Factoriel :%d\n", factoriel(5));
  return EXIT_SUCCESS;
}
