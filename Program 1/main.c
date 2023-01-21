#include<stdio.h>
#include"bit_flags.h"

int main(int argc, char* argv[])
{
	BIT_FLAGS hBit_flags = bit_flags_init_number_of_bits(1);
	printf("check\n");
	printf("%d / %d\n", bit_flags_get_size(hBit_flags), bit_flags_get_capacity(hBit_flags));
	printf("check 2\n");
	bit_flags_set_flag(hBit_flags, 31);
	printf("%d / %d\n", bit_flags_get_size(hBit_flags), bit_flags_get_capacity(hBit_flags));
	bit_flags_set_flag(hBit_flags, 2000000000);
	printf("%d / %d\n", bit_flags_get_size(hBit_flags), bit_flags_get_capacity(hBit_flags));

	/*printf("An initial bit_flag object is made with size %d: ", bit_flags_get_size(hBit_flags));
	bit_flags_display_bit_flags(hBit_flags);
	printf("\n\n");
	for (int i = 0; i <= 200; i++)
	{
		Status status = bit_flags_set_flag(hBit_flags, (i * 2));
	}
	printf("Bit_flag object after setting alternating bits to position 400: "); 
	bit_flags_display_bit_flags(hBit_flags);
	for (int i = 0; i <= 200; i++)
	{
		Status status = bit_flags_unset_flag(hBit_flags, (i * 2));
	}
	printf("\n\n");
	printf("Bit_flag object after unsetting alternating bits to position 400: ");
	bit_flags_display_bit_flags(hBit_flags);
	printf("\n\n");
	printf("The size of the bit_flags object is %d bits\n", bit_flags_get_size(hBit_flags));
	printf("\n\n");
	printf("The capacity of the bit_flags object is %d bits\n", bit_flags_get_capacity(hBit_flags));
	printf("\n\n");
	bit_flags_destroy(&hBit_flags);
	printf("The bit_flags object has been destroyed.\n");*/
}