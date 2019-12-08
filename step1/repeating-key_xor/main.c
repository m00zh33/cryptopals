#include "../../cryptoutils.h"

int main()
{
  char to_encode[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  char key[4] = "ICE";

  int *encoded = repeating_key_xor(strlen(to_encode),to_encode,strlen(key),key);

  int i;
  for(i=0;i<strlen(to_encode);++i)
    printf("%02X",encoded[i]);

  printf("\n");

  return 0;
}
