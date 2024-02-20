#include <iostream>
#include <vector>

using namespace std;

void mergeSort(vector<int> &left, vector<int> &right, vector<int> &bars)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR)
    {
        if (left[j] < right[k])
        {
            bars[i] = left[j];
            j++;
        }
        else
        {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL)
    {
        bars[i] = left[j];
        j++;
        i++;
    }
    while (k < nR)
    {
        bars[i] = right[k];
        k++;
        i++;
    }
}
void sort(vector<int> &bar)
{
    if (bar.size() <= 1)
        return;

    int mid = bar.size() / 2;
    vector<int> left;
    vector<int> right;

    for (size_t j = 0; j < mid; j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    sort(left);
    sort(right);
    mergeSort(left, right, bar);
}

int main()
{
    int input;
    vector<int> nums;
    while (cin >> input)
    {
        nums.push_back(input);
    }

    sort(nums);

    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums.at(i) << " ";
    }
    cout << endl;
    return 0;
}