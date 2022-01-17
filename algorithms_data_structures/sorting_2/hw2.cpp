#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const int MAX_NUM = 101;

vector<int> countingSort(vector<int> arr, int length)
{
    int i, j;
    int cnt[MAX_NUM] = {0};

    for (i = 0; i < length; i++)
    {
        cnt[arr[i]]++;
    }

    i = 0;
    for (j = 0; j < MAX_NUM; j++)
    {
        while(cnt[j] > 0)
        {
            arr[i++] = j;
            cnt[j]--;
        }
    }
    return arr;
}

int main()
{
    vector<int> arr;
    int numb;
    while (cin >> numb)
    {
        arr.push_back(numb);
    }

    int length = arr.size();

    vector<int> sorted = countingSort(arr, length);
    for (int i = 0; i < length; i ++)
    {
        cout << sorted[i] << " ";
    }

    return 0;
}


/*
* A - kth elem

int kthSmallest(int arr[], int l, int r, int k)
{
    int index = split(arr, l, r);

    if (index - l == k - 1)
        return arr[index];

    if (index - l > k - 1)
        return kthSmallest(arr, l, index - 1, k);

    return kthSmallest(arr, index + 1, r,
                       k - index + l - 1);
}

int split(int arr[], int l, int r)
{
    int pivot = arr[r];
    int m = l;

    for (int i = l; i < r; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(arr[m], arr[i]);
            m++;
        }
    }

    swap(arr[m], arr[r]);

    return m;
}



int findK(int arr[], int l, int r, int k)
{
    int m = split(arr, l, r);

    if (m - l == k - 1)
        return arr[m];

    if (m - l > k - 1)
        return findK(arr, l, m - 1, k);

    return findK(arr, m + 1, r, k - m + l - 1);
}


int split(int arr[], int l, int r)
{
    int pivot = arr[r];
    int m = l;

    for (int i = l; i < r; i ++)
    {
        if (arr[i] <= pivot)
        {
            swap(arr[m], arr[i]);
            m ++;
        }
    }

    swap(arr[m], arr[r]);

    return m;
}


int findK(int arr[], int k, int l, int r)
{
    if (l == r)
    {
        return arr[k];
    }

    int m = split(arr, l, r);

    if (k < m)
    {
        return findK(arr, k, l, m - 1);
    }
    else
    {
        return findK(arr, k, m, r);
    }
}


int main()
{
    int elements, requests, numb, i, l, r, k;

    cin >> elements;
    int arr[elements];
    for (i = 0; i < elements; i++)
    {
        cin >> numb;
        arr[i] = numb;
    }

    cin >> requests;
    int lArr[requests], rArr[requests], kArr[requests];
    for (i = 0; i < requests; i++)
    {
        cin >> l >> r >> k;
        lArr[i] = l - 1;
        rArr[i] = r - 1;
        kArr[i] = k - 1;
    }

    for (i = 0; i < requests; i++)
    {
        int* copyOfArr = new int[rArr[i] - lArr[i] + 1];
        copy(arr + lArr[i], arr + rArr[i] + 1, copyOfArr);
        cout << findK(copyOfArr, kArr[i], 0, rArr[i] - lArr[i]) << "\n";
    }

    return 0;
}

*/


/*
* B-COUNTING SORT
vector<int> countingSort(vector<int> arr, int length)
{
    int i, j;
    int maxNum = 101;
    int cnt[maxNum] = {0};

    for (i = 0; i < length; i++)
    {
        cnt[arr[i]]++;
    }

    i = 0;
    for (j = 0; j < maxNum; j++)
    {
        while(cnt[j] > 0)
        {
            arr[i++] = j;
            cnt[j]--;
        }
    }
    return arr;
}
*/

/*
* C - digit sorting
int charToInt(char c)
{
    return (int)(c) - 97;
}

//sort pairs based on the first element of a pair
pair<int, string>* pairCountingSort(pair<int, string> pairArr[], pair<int, string> sorted[], int lines)
{
    int i;
    int maxNum = 27;
    int cnt[maxNum] = {0}; //array for counting characters

    //count number of occuring characters
    for (i = 0; i < lines; i++)
    {
        cnt[pairArr[i].first]++;
    }

    int indices[maxNum] = {0}; //kernel array for helping to sort pairs
    for (i = 1; i < maxNum; i++)
    {
        indices[i] = indices[i - 1] + cnt[i - 1]; //populate array of beginning indices
    }

    for (i = 0; i < lines; i++)
    {
        sorted[indices[pairArr[i].first]++] = pairArr[i]; //save the new element in the right place
    }
    return sorted;
}

//Digit sorting algorithm for ONE phase only
void digitSortingPhase(string arr[], int lines, int length, int phase)
{
    pair<int, string> pairs[lines]; //array of pairs for saving character from string and string itself
    pair<int, string> tempPair;
    int tempCharInt, i;
    for (i = 0; i < lines; i++)
    {
        tempCharInt = charToInt(arr[i].at(length - phase - 1)); //get a character a given phase
        tempPair = make_pair(tempCharInt, arr[i]); //pair of character in int form and string
        pairs[i] = tempPair; //add a given pair to array of pairs
    }

    pair<int, string> sortedPairs[lines];
    pairCountingSort(pairs, sortedPairs, lines); //get reference to an array

    for (i = 0; i < lines; i++)
    {
        arr[i] = sortedPairs[i].second;
    }
}

void digitSorting(string arr[], int lines, int length, int phases)
{
    for (int i = 0; i < phases; i++)
    {
        digitSortingPhase(arr, lines, length, i);
    }
}

void display(int* arr)
{
    int i = 0;
    while (arr[i] != '\0')
    {
        cout << arr[i] << " ";
        ++ i;
    }

    cout << endl;
}
*/




