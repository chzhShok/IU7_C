#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define ERR_OK  0
#define ERR_IO  1

void print_two_base_uint32(uint32_t num)
{
    for (int i = CHAR_BIT * 4 - 1; i >= 0; i--) 
    {
        printf("%u", (num >> i) & 1);
    }
    printf("\n");
}

uint32_t encrypt_number(uint32_t num) 
{
    uint32_t encrypted_num = 0;

    for (int i = 0; i < CHAR_BIT * 4; i += 2) 
    {
        uint32_t even_bit = (num >> i) & 1;
        uint32_t odd_bit = (num >> (i + 1)) & 1;

        encrypted_num |= (even_bit << (i + 1)) | (odd_bit << i);
    }

    return encrypted_num;
}

int main(void) 
{
    uint32_t num;

    printf("Enter a four-byte unsigned integer: ");
    if (scanf("%u", &num) != 1) 
    {
        printf("Error: IO error\n");
        return ERR_IO;
    } 

    uint32_t encrypted_num = encrypt_number(num);

    printf("Result: \n");
    print_two_base_uint32(encrypted_num);

    return ERR_OK;
}

