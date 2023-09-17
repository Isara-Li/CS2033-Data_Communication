#include <stdio.h>

void convertToBinaryArray(int inputArray[], int size, int outputArray[], int bits)
{
    for (int i = 0; i < size; i++)
    {
        int num = inputArray[i];
        for (int j = bits - 1; j >= 0; j--)
        {
            outputArray[i * bits + (bits - j - 1)] = (num >> j) & 1;
        }
    }
}

int main()
{
    int inputArray[] = {2, 3, 1};
    int size = sizeof(inputArray) / sizeof(inputArray[0]);
    int bits = 2; // Assuming 32-bit integers

    int outputArray[size * bits];

    convertToBinaryArray(inputArray, size, outputArray, bits);

    // Printing the binary array
    printf("Binary representation: ");
    for (int i = 0; i < size * bits; i++)
    {
        printf("%d", outputArray[i]);
    }
    printf("\n");

    return 0;
}
