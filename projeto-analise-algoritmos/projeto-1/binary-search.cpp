#include <iostream>
using namespace std;

int binary_search(int array[], int left, int right, int num)
{
    if (left <= right)
    {
        int middle = (left + right) / 2;

        if (array[middle] == num && array[middle - 1] != num)
        {
            return middle;
        }

        else if (array[middle] >= num)
        {
            return binary_search(array, left, middle - 1, num);
        }

        else if (array[middle] < num)
        {
            return binary_search(array, middle + 1, right, num);
        }
    }
    return -1;
}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);

    int array[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < q; i++)
    {
        int num;
        scanf("%d", &num);
        int index = binary_search(array, 0, n - 1, num);
        printf("%d\n", index);
    }
}