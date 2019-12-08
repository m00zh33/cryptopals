#include "../../cryptoutils.h"




int main(int argc, char *argv[])
{
	char to_encode[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

	int size = strlen(to_encode)/2;
	char *asciifinall;

	asciifinall = hex_to_ascii(strlen(to_encode),to_encode, size);

	char *base64finall;
	base64finall = ascii_to_base64(size,asciifinall);
	printf("%s\n",base64finall);
	return 0;
}
