#include<stdio.h>
#include<stdlib.h>

#define MAX_FIELD_SIZE 2000000000

int main(int argc, char* argv[])
{
	int x, field_size;
	x = field_size = 1;
	int i_bits = sizeof(int) * 8;
	int* bit_data = (int*)calloc(MAX_FIELD_SIZE / i_bits, sizeof(int));
	if (bit_data == NULL)
	{
		exit(1);
	}
	for (int i = 0; i < MAX_FIELD_SIZE && x != -1; i++)
	{
		scanf("%d", &x);
		bit_data[x / i_bits] |= 1 << (x % i_bits);
		field_size = field_size > x ? field_size : x;
	}
	for (int i = 0; i <= field_size; i++)
	{
		if (bit_data[i / i_bits] & (1 << (i % i_bits)))
		{
			printf("%d\n", i);
		}
	}
	free(bit_data);
}

