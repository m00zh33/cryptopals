#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int *hex_to_int(size_t n1,char hexstring[n1])
{
	int *intfinall = malloc(sizeof(int) * n1/2);
	char hex_word[2];
	int i;

	for (i=0;i<n1;++i)
	{
		if (i%2==0)
		{
			hex_word[0] = hexstring[i];
			hex_word[1] = hexstring[i+1];

			intfinall[i/2]=strtol(hex_word,NULL,16);
		}
	}

	return intfinall;
}

void hex_to_char(size_t n1,char hexstring[n1],char *finallstring)
{
	char hex_word[2];
	char finall_word;
	int i;

	for (i=0;i<n1;++i)
	{
		if (i%2==0)
		{
			hex_word[0] = hexstring[i];
			hex_word[1] = hexstring[i+1];
			finallstring[i/2]= strtol(hex_word,NULL,16);
		}
	}
	finallstring[(n1/2)] = '\x00';
}

char *hex_to_ascii(size_t n1,char hexstring[n1],size_t n2)
{
	char *asciifinall = malloc(n2);
	char hex_word[2];
	int i,counter=0;

	for (i=0;i<n1;++i)
	{
		if (i%2==0)
		{
			hex_word[0] = hexstring[i];
			hex_word[1] = hexstring[i+1];

			asciifinall[counter]=strtol(hex_word,NULL,16);
			counter++;
		}
	}
	//asciifinall[n2] = '\x00';
	return asciifinall;
}

int *int_to_bin(int n){
	//https://stackoverflow.com/questions/2249731/how-do-i-get-bit-by-bit-data-from-an-integer-value-in-c
	int bitswanted = 8;
	int *bits = malloc(sizeof(int) * bitswanted);

	int k;
	for(k=0; k<bitswanted; k++){
		int mask =  1 << k;
		int masked_n = n & mask;
		int thebit = masked_n >> k;
		bits[k] = thebit;
  }

  return bits;
}

char *reverse_string(size_t n,char tha_sample[n])
{
	char *swaped = malloc(sizeof(char) * n);
	int i,a = 0;
	for(i=n-1;i>=0;i--)
	{
		swaped[a] = tha_sample[i];
		++a;
	}
	return swaped;
}


int bin_to_int(size_t n,char binary_num[n])
{
	int i, integer_num=0;

	for (i=0;i<n;++i)
	{
		if (binary_num[i] == '1')
		{
			integer_num += pow(2,i);
		}
	}

	return integer_num;
}

char *string_to_bin(size_t n,char asciistring[n])
{
	char *bits_container = malloc(8*n);
	int *bits;
	int i,c;
	int z = 0;

	for (i = 0;i < n;++i)
	{
		bits = int_to_bin(asciistring[i]);

		for (c=7;c>=0;--c)
		{

			if (bits[c] == 1 )
				bits_container[z] = '1';
			else if (bits[c] == 0)
				bits_container[z] = '0';
			z++;
			}
	}

	return bits_container;
}

char base64_table(int n)
{
	char table[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};
	return table[n];
}

int from_base64_table(char n)
{
	if (n == '=')
		return -1;

	char table[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};
	int i;

	for(i=0;i < 64;++i)
	{
		if (table[i] == n)
			return i;
	}

	return 0;
}

char *base64_to_ascii(size_t n, char base64string[n])
{
	//printf("len = %d\n",n);
	int original_bits[n];
	int *bits;
	char *bits_container = malloc(n*8);
	char *decoded_string = malloc(n); // Is not precise but you know
	char bits_temp[6], letter_temp[8];
	int i,a,c = 0;

	for(i=0;i < n;++i)
	{
		original_bits[i] = from_base64_table(base64string[i]);
		if (original_bits[i] == -1)
		{
			strcat(bits_container,"00");
		}else if (original_bits[i] >= 0){
			bits = int_to_bin(original_bits[i]);

			for(a=0;a < 6;++a)
			{
				if(bits[a])
				{
					bits_temp[a] = '1';
				}else
				{
					bits_temp[a] = '0';
				}

			}
			strcat(bits_container,reverse_string(strlen(bits_temp),bits_temp));
		}
	}

	a = 0;

	while (strlen(bits_container)%8 != 0) // To add the finall word too
		strcat(bits_container,"0");

	//for(i=0;i<n*6;++i)
	for(i=0;i<strlen(bits_container);++i)
	{
		if(c == 8)
		{
			decoded_string[a] = bin_to_int(8,reverse_string(8,letter_temp));
			a++;
			c=0;
		}
		letter_temp[c] = bits_container[i];
		++c;
	}

	return decoded_string;
}

void split_into_chunks(size_t n,char *string,int chunks,char *string_splited[n/chunks])
{
		int i,a,counter = 0;

		for (i=0;i<(n/chunks)+1;i++)
		{
			string_splited[i] = malloc(sizeof(char) * (chunks+1)); // We allocate space and we save the pointer in every space of the array
		}

		for(i=0;i<n/chunks;i++)
		{
			for (a=0;a<chunks;a++)
			{
				string_splited[i][a] = string[counter];
				counter++;
			}
		}

		if (n%chunks !=0) // We check if there is there is anything to add
		{
			for (a=0;a<=n%chunks;a++) // We use a because in i there is the last positiion in string_splited
			{
				string_splited[i][a] = string[counter];
				counter++;
			}
		}
}

int get_edit_distance(size_t n1, char string1[n1], size_t n2, char string2[n2])
{
	char *bits_list1 = string_to_bin(n1,string1);
	char *bits_list2 = string_to_bin(n2,string2);
	int i,diferences = 0;

	for(i=0;i<n1*8;i++)
	{
		if (bits_list1[i] != bits_list2[i])
			diferences++;
	}
	return diferences;
}

char *ascii_to_base64(size_t n,char asciistring[n])
{
	char *bits_container = string_to_bin((8*strlen(asciistring))/6,asciistring); // Before there wasn't len

	char *base64finall = malloc((8*strlen(asciistring))/6);
	char six_bits[7],character;
	char *reversed_bits;//[7];
	int i, b=0, c=0;

	for (i=0;i<8*strlen(asciistring)+1;++i)
	{
		if (b == 6)
		{
			b = 0;
			reversed_bits = reverse_string(strlen(six_bits),six_bits);

			base64finall[c] = base64_table(bin_to_int(strlen(reversed_bits),reversed_bits));
			++c;
		}
		six_bits[b] = bits_container[i];
		b++;

	}
	return base64finall;
}

int *single_byte_xor(size_t n, char to_encode[n], int key)
{
	int *xored = malloc(sizeof(int) * n);
	//int *to_encode_decoded = hex_to_int(n1,to_encode);

	int i;

	for (i=0;i<n;i++)
	{
		xored[i] = to_encode[i] ^ key;
	}
	return xored;
}

double find_max(size_t n,double values[n])
{
	double max;
	int i;

	for (i=0;i < n;i++)
	{
		if(values[i] > max)
			max = values[i];
	}
	return max;
}

int find_max_in_array(size_t n,double values[n])
{
	double max = find_max(n,values);
	int i;

	for (i=0;i < n;++i)
	{
		if (max == values[i])
		{
			return i;
		}
	}
}

double get_character_freq(char character)
{
	char characters[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
	double freqs[28] = {0.0651738,0.0124248,0.0217339,0.0349835,0.1041442,0.0197881,0.0158610,0.0492888,0.0558094,0.0009033,0.0050529,0.0331490,0.0202124,0.0564513,0.0596302,0.0137645,0.0008606,0.0497563,0.0515760,0.0729357,0.0225134,0.0082903,0.0171272,0.0013692,0.0145984,0.0007836,0.1918182	};

	int i;
	for (i=0;i<27;++i)
	{
		if(tolower(character) == characters[i])
			return freqs[i];
	}

	return 0;
}

double get_character_freqs_string(size_t n,char string[n])
{
	double freq = 0.0;
	int i;

	for(i=0;i<n;i++)
	{
		freq += get_character_freq(string[i]);
	}

	return freq;
}

char *repeating_key_xor(size_t n1, char to_encode[n1], size_t n2, char key[n2])
{
	char *xored = malloc(sizeof(char) * (n1));
	int i,a = 0;

	for (i = 0;i < n1;i++)
	{
		xored[i] = to_encode[i] ^ key[a];
		a++;
		if(a == n2)
			a = 0;
	}

	return xored;
}

int *fixed_xor(size_t n, char to_encode[n],char key[n])
{
	int *xored = malloc(sizeof(int) * n);
	int i;

	for (i = 0;i < n;i++)
	{
		xored[i] = to_encode[i] ^ key[i];
	}

	return xored;
}

/*
Hey,you need to change all of your code to one more reliable,
start by putting everything into functions and not assuming that
the data is going to be in hex
*/

char break_single_byte_xor(size_t n,char to_decode[n])
{
	double values[0xFF];
	int *xored;
	int i,a;//,a;
	int max;

	for(i=0;i<0xFF;i++)
	{
		xored = single_byte_xor(n,to_decode,i);
		values[i] = 0.0;


		for(a=0;a<n;a++)
		{
			values[i] += get_character_freq(xored[a]);
		}

		//values[i] = get_character_freqs_string(n,xored); this works unproperly with ints u know ;)
		//free(xored);
	}
	max = find_max_in_array(0xFF,values);
	return max;
}

int *detect_single_byte_xor(int numberofrows,size_t n,char xored_rows[numberofrows][n+1]) // It's assumed that the rows are in hex
{
	/*
		This funciton returns an array [index of the row,key]
	*/
	char key,maxkey;
	char decoded_string[n/2];
	int *xored,id;
	int *result = malloc(sizeof(int) * 3); // Let's give it more space than the needed
	double freq,maxfreq=0.0;
	int i,a;

	for (i=0;i<numberofrows-1;i++)
	{
		hex_to_char(n,xored_rows[i],decoded_string);
		key = break_single_byte_xor(n/2,decoded_string);

		xored = single_byte_xor(n/2,decoded_string,key);
		//freq = get_character_freqs_string(n/2,xored);
		freq = 0.0;
		for(a = 0;a<n/2;a++)
		{
			freq += get_character_freq(xored[a]);
		}
		if (freq > maxfreq)
		{
			maxfreq = freq;
			maxkey = key;
			id = i;
		}
		//free(xored);
	}
	result[0] = id;
	result[1] = maxkey;

	return result;
}

#endif
