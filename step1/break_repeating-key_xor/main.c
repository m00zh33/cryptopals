#include "../../cryptoutils.h"

int main()
{
  FILE *fp;
  char to_decrypt[3837],container[61],the_key[41];
  char *b64decoded;
  char *decrypted_text;
  int i,a=0,o,base64stringlen,currentdistance,keysize;
  int minkeysize[5] = {100,100,100,100};
  int mindistance[5] = {100,100,100,100};
  double freq = 0.0,lastfreq = 0.0;

  fp = fopen("6.txt","r");

  for (i = 0;i < 127;i++)
  {
    fgets(container,61,fp);
    if (strlen(container) >= 56)
    {
      strcat(to_decrypt,container);
    }
  }
  to_decrypt[3836] = '\00';
  b64decoded = base64_to_ascii(strlen(to_decrypt),to_decrypt);

  // Now we have everything OK, let's start with the magic

  base64stringlen = (3*(strlen(to_decrypt)/4))-1;

  for (i = 2;i<41;i++)
  {
    char *string_chunked[(base64stringlen/i)+2]; // + 2 because we need space :)
    split_into_chunks(base64stringlen,b64decoded,i,string_chunked);

    currentdistance = 0;
    for (o=0;o<6*2;o++)
    {
      o++;
      currentdistance = currentdistance + get_edit_distance(i,string_chunked[o-1],i,string_chunked[o]);
      //printf("%d,%d\n",o-1,o);
    }

    currentdistance = currentdistance/6;

    currentdistance = currentdistance/i;

    for (o=0;o<4;o++)
    {
      if (currentdistance < mindistance[o])
      {
        mindistance[o] = currentdistance;
        minkeysize[o] = i;
        break;
      }
    }
  }
  for (o=0;o<4;o++)
  {
    //keysize = 29;
    keysize = minkeysize[o];

    char *string_chunked[(base64stringlen/keysize)+2];
    split_into_chunks(base64stringlen,b64decoded,keysize,string_chunked);

    char posiblekeys[keysize][(base64stringlen/keysize)+2]; // Contains the first byte of every block, the second byte of every block and so on
    char key[keysize];

    for (i=0;i< keysize;i++)
    {
      for(a=0;a<(base64stringlen/keysize)+1;a++)
      {
        posiblekeys[i][a] = string_chunked[a][i];
      }
      key[i] = break_single_byte_xor((base64stringlen/keysize)+1,posiblekeys[i]);

    }
    key[keysize] = '\x00';

    decrypted_text = repeating_key_xor(base64stringlen,b64decoded,keysize,key);
    freq = 0;
    for (i=0;i<base64stringlen;i++)
    {
      freq += get_character_freq(decrypted_text[i]);
    }

    if (lastfreq == 0.0)
    {
        lastfreq = freq;
    }
    else if (freq > lastfreq)
    {
      lastfreq = freq;
      strcpy(the_key,key);
    }
  }
  decrypted_text = repeating_key_xor(base64stringlen,b64decoded,strlen(the_key),the_key);
  printf("%s\n----------------------",decrypted_text);
  printf("\nKey = %s\n",the_key);

  return 0;
}
