#include "SHA.h"

void rotr(vector<int>& input, int n)
{
    int dim = input.size();
    for (int i = 0; i < dim; i++)
    {
        if (i + n < dim) swap(input[i], input[i + n]);
        else swap(input[i], input[i + n - dim]);
    }

}