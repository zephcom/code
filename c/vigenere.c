#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MESSAGE_MAX_LENGTH		4096

char caesar(int key, char c);
int v_key(char c, int decrypt);

int main(int argc, char *argv[])
{
	if (argc > 3 || argc < 2) //Only accept one or two arguments, '-d' for decrypt should not come last
	{
		printf("Usage: %s [-d decrypt] KEY\n\tKEY is an alphabetical phrase.\n\tEncrypts stdin using a vigenere cipher.\n", argv[0]);
		return 1;
	}
	char *key_in = argv[argc - 1]; //Take the last command line argument as key
	char intext[MESSAGE_MAX_LENGTH];
	fgets(intext, MESSAGE_MAX_LENGTH, stdin);
	for (int i = 0, n = 0; i < strlen(intext); i++, n++)
	{
		if (n == strlen(argv[argc - 1]))
			n = 0;
		if (isalnum(intext[i]) == 0)
			--n;
		if (!strcmp(argv[1], "-d"))
			printf("%c", caesar(v_key(argv[argc - 1][n], 1), intext[i]));
		else
			printf("%c", caesar(v_key(argv[argc - 1][n], 0), intext[i]));
	}
}

/* Shift characters forward a specified amount */
char caesar(int key, char c)
{
	int case_mod, z = 0;
	if (islower(c))
		case_mod = -96;
	else if (isupper(c))
		case_mod = -64;
	else
		return c;
	if (c + case_mod + key == 26)
		z = 26;
	return (c + key + case_mod) % 26 - case_mod + z;
}

/* Turn alphabetical characters to numbers 0 - 25 for use as key */
int v_key(char c, int decrypt)
{
	if (isupper(c))
		c = tolower(c);
	if (decrypt == 1)
	{
		return 26 - (c - 97);
	}
	else
		//printf("%d ", c - 97);
		return c - 97;
}
