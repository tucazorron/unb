#include <iostream>

using namespace std;

int merge(int array[], int aux[], int left, int middle, int right)
{

    int swaps = 0;

    int l = left;
    int m = middle;
    int r = left;

    while ((l <= middle - 1) && (m <= right))
    {
        if (array[l] <= array[m])
        {
            aux[r++] = array[l++];
        }

        else
        {
            aux[r++] = array[m++];
            swaps += (middle - l);
        }
    }

    while (l <= middle - 1)
    {
        aux[r++] = array[l++];
    }

    while (m <= right)
    {
        aux[r++] = array[m++];
    }

    for (l = left; l <= right; l++)
    {
        array[l] = aux[l];
    }

    return swaps;
}

int merge_sort(int array[], int aux[], int left, int right)
{
    int swaps = 0;

    if (right > left)
    {
        int middle = (left + right) / 2;

        swaps = merge_sort(array, aux, left, middle);
        swaps += merge_sort(array, aux, middle + 1, right);

        swaps += merge(array, aux, left, middle + 1, right);
    }
    return swaps;
}

int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        int n;
        scanf("%d", &n);

        int array[n];
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &array[i]);
        }
        int aux[n];
        int swaps = merge_sort(array, aux, 0, n - 1);
        printf("%d\n", swaps);
    }
    return 0;
}