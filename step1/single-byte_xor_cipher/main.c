#include "../../cryptoutils.h"

int main()
{
  char key;
  int a;
  int *xored;

  char to_decode[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  char to_decode_decoded[strlen(to_decode)/2];

  hex_to_char(strlen(to_decode),to_decode,to_decode_decoded);

  key = break_single_byte_xor(strlen(to_decode)/2,to_decode_decoded);

  xored = single_byte_xor(strlen(to_decode)/2,to_decode_decoded,key);
  for(a = 0;a < strlen(to_decode)/2;a++)
  {
    printf("%c",xored[a]);
  }
  printf("\nkey = 0x%X\n",key);

  return 0;
}

/*
  int i,a,max;
  int *xored;
  double values[0xFF];

  for (i = 0; i < 0xFF;i++)
  {
    xored = single_byte_xor(strlen(to_decode),to_decode,i);

    for(a = 0;a < strlen(to_decode)/2;a++)
    {
      values[i] += get_character_freq(xored[a]);
    }

    //values[i] = getfreqsinstring(strlen(xored),xored);
  }

  max = find_max_in_array(0xFF,values);
*/
