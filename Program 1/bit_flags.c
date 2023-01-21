#include "bit_flags.h"
#include "status.h"
#include"stdlib.h"
#include"stdio.h"


struct bit_flags
{
	int size;
	int capacity;
	int* bit_data;
};

typedef struct bit_flags Bit_flags;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	int size_of_int = sizeof(int);
	int ints_to_allocate = (number_of_bits / (size_of_int * 8)) + 1;
	Bit_flags* pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
	if (pBit_flags != NULL)
	{
		pBit_flags->capacity = ints_to_allocate * size_of_int * 8;
		pBit_flags->size = number_of_bits;
		pBit_flags->bit_data = (int*)malloc(sizeof(int) * ints_to_allocate);
		if (pBit_flags->bit_data == NULL)
		{
			free(pBit_flags);
			return NULL;
		}
		for (int i = 0; i < ints_to_allocate; i++)
		{
			pBit_flags->bit_data[i] = 0;
		}
	}
	return (BIT_FLAGS)pBit_flags;

}


//Precondition: flag_position is a non-negative integer and hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: The flag at the flag_position index is set to 1. Function will attempt to resize the
// internal representation if the flag_position is too large instead of failing for out of bounds. Returns
// SUCCESS if the operation is successful and FAILURE if the operation fails a needed resize. This
// operation is considered to be expensive if flag_position is constantly going out of bounds by a small
// amount because the resize always attempts to minimize the amount of space required to store the bits.
// All new flags created in a resize operation (except the one being set) will be set as zero.
Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	int size_of_int = sizeof(int);
	int size_of_int_bits = size_of_int * 8;
	int bit_data_index = flag_position / size_of_int_bits;
	int ints_to_allocate = (flag_position / size_of_int_bits) + 1;

	if (flag_position >= pBit_flags->capacity)
	{
		
		int* temp_data = (int*)malloc(sizeof(int) * ints_to_allocate);
		int temp_capacity = pBit_flags->capacity;
		if (temp_data == NULL)
		{
			return FAILURE;
		}
		pBit_flags->capacity = ints_to_allocate * size_of_int_bits;
		for (int j = 0; j < pBit_flags->capacity / size_of_int_bits; j++)
		{
			temp_data[j] = 0;
		}
		for (int i = 0; i < (temp_capacity / size_of_int_bits); i++)
		{
			temp_data[i] = pBit_flags->bit_data[i];
		}
		free(pBit_flags->bit_data);
		pBit_flags->bit_data = temp_data;
		pBit_flags->size = flag_position - 1;
	}

	if (flag_position > pBit_flags->size)
	{
		pBit_flags->size = flag_position + 1;
	}

	flag_position %= size_of_int_bits;

	int bit_to_flip = 1 << flag_position;

	pBit_flags->bit_data[bit_data_index] |= bit_to_flip;
	return SUCCESS;
}


Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	int size_of_int = sizeof(int);
	int size_of_int_bits = size_of_int * 8;
	int bit_data_index = flag_position / size_of_int_bits;
	int ints_to_allocate = (flag_position / size_of_int_bits) + 1;

	if (flag_position >= pBit_flags->capacity)
	{
		int* temp_data = (int*)malloc(sizeof(int) * ints_to_allocate);
		int temp_capacity = pBit_flags->capacity;
		if (temp_data == NULL)
		{

			return FAILURE;
		}
		pBit_flags->capacity = ints_to_allocate * size_of_int_bits;
		for (int j = 0; j < pBit_flags->capacity / size_of_int_bits; j++)
		{
			temp_data[j] = 0;
		}
		for (int i = 0; i < (temp_capacity / size_of_int_bits); i++)
		{
			temp_data[i] = pBit_flags->bit_data[i];
		}
		free(pBit_flags->bit_data);
		pBit_flags->bit_data = temp_data;
		pBit_flags->size = flag_position + 1;
	}

	if (flag_position > pBit_flags->size)
	{
		pBit_flags->size = flag_position;
	}

	flag_position %= size_of_int_bits;
	int bit_to_flip = 1 << flag_position;
	pBit_flags->bit_data[bit_data_index] &= ~bit_to_flip;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	return pBit_flags->size;
}


int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	return pBit_flags->capacity;
}



void bit_flags_display_bit_flags(BIT_FLAGS hBit_flags)
{
	int int_bytes = sizeof(int);
	int int_bits = int_bytes * 8;

	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	for (int i = pBit_flags->size - 1; i >= 0; i--)
	{
		printf("%d", bit_flags_check_flag(hBit_flags, i));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	int int_bytes = sizeof(int);
	int int_bits = int_bytes * 8;
	int check_bit = 1 << (flag_position % int_bits);
	int match = pBit_flags->bit_data[(flag_position / int_bits)] & check_bit;
	
	if (match)
	{
		return 1;
	}
	else if (flag_position > pBit_flags->capacity)
	{
		return -1;
	}
	return 0;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)*phBit_flags;
	free(pBit_flags->bit_data);
	free(pBit_flags);
	*phBit_flags = NULL;

}