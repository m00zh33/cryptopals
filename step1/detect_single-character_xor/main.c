#include "../../cryptoutils.h"

int main()
{

  FILE *fp;
  char strings[327][61],container[61];
  //int *xored;
  char decoded_string[60/2];
  int *idkey, *xored;
  char key;
  int id,i,a=0;

  fp = fopen("4.txt","r");

  for (i=0;i<652;i++)
  {
    fgets(container,61,fp);
    if(strlen(container) == 60)
    {
      strcpy(strings[a],container);
      strings[a][60] = '\x00';
      a++;
    }
  }

  idkey = detect_single_byte_xor(327,strlen(strings[0]),strings);
  id = idkey[0];
  key = idkey[1];

  hex_to_char(strlen(strings[id]),strings[id],decoded_string);
  xored = single_byte_xor(strlen(strings[id])/2,decoded_string,key);

  printf("Key = 0x%X\n",key);
  for(i=0;i<strlen(strings[id])/2;i++)
  {
    printf("%c",xored[i]);
  }
  printf("\n");

  return 0;
}
