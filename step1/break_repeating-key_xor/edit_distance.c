#include "../../cryptoutils.h"


int main()
{
	char string1[15] = {"this is a test"};
	char string2[15] = {"wokka wokka!!!"};

	int editdistance = get_edit_distance(strlen(string1),string1,strlen(string2),string2);
	printf("%i\n",editdistance);

	return 0;
}
