#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MESSAGE_MAX_LENGTH		4096

char caesar(int key, char c);
int v_key(char c);

int main(int argc, char *argv[])
{
	if (argc != 2) //Only accept one argument, else print help message
	{
		printf("Usage: %s [KEY]\n\tKEY is an alphabetical phrase.\n\tEncrypts stdin using a vigenere cipher.\n", argv[0]);
		return 1;
	}
	char *key_in = argv[1];
	char intext[MESSAGE_MAX_LENGTH];
	fgets(intext, MESSAGE_MAX_LENGTH, stdin); 
	for (int i = 0, n = 0; i < strlen(intext); i++, n++)
	{
		if (n == strlen(argv[1]))
			n = 0;
		if (isalnum(intext[i]) == 0)
			--n;
		printf("%c", caesar(v_key(argv[1][n]), intext[i]));
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
int v_key(char c)
{
	if (isupper(c))
		c = tolower(c);
	if (islower(c))
		return c - 97;
	else
		return 0;;
}
