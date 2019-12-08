#include "../../cryptoutils.h"


int main()
{
  char to_encode[36] = "1c0111001f010100061a024b53535009181c";
  char key[36] = "686974207468652062756c6c277320657965";

  char to_encode_decoded[36/2];
  char key_decoded[36/2];
  hex_to_char(strlen(to_encode),to_encode,to_encode_decoded);
  hex_to_char(strlen(key),key,key_decoded);

/*  for(i=0;i<strlen(key)/2;i++)
    printf("%d,",to_encode_decoded[i]);

  char hehe[] = "686f6c61207175652074616c";
  char sample[strlen(hehe)/2];
  hex_to_char(strlen(hehe),hehe,sample);
  printf("%s\n",sample);
*/
  int *xored;
  xored = fixed_xor(strlen(key),to_encode_decoded,key_decoded);

  int i;
  for (i = 0;i < strlen(to_encode)/2; ++i)
  {
    printf("%X",xored[i]);
  }
  printf("\n");

  return 0;
}
