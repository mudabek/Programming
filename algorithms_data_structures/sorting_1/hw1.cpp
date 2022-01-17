#include<iostream>
#include <bits/stdc++.h>
using namespace std;

//function to get value of a Roman numeral
int DecValue(char r)
{
    if (r == 'I')
        return 1;

    else if (r == 'V')
        return 5;

    else if (r == 'X')
        return 10;

    else if (r == 'L')
        return 50;

    return -1;
}

//function to turn Roman number to Decimal number
int RomanToDecimal(string& romanNumb)
{
    int retNumber = 0;

    for (int i = 0; i < romanNumb.length(); i++)
    {
        int firstDigit = DecValue(romanNumb[i]);
        if (i + 1 < romanNumb.length())
        {
            int nextDigit = DecValue(romanNumb[i + 1]);
            if (firstDigit >= nextDigit)
            {
                retNumber = retNumber + firstDigit;
            }
            else
            {
                retNumber = retNumber + nextDigit - firstDigit;
                i++;
            }
        }
        else
        {
            retNumber = retNumber + firstDigit;
        }
    }
    return retNumber;
}

//function to modify standard sorting
bool comparator(pair<string, pair<string, int>> &a, pair<string, pair<string, int>> &b)
{


    //case when kings have the same name
    if (a.first.compare(b.first) == 0)
    {
        return a.second.second < b.second.second;
    }
    else
    {
        //case when kings have different names
        return a.first > b.first == 1 ? 0 : 1;
    }
}

int main()
{
    int length;
    cin >> length;
    pair <string, pair<string, int>> kings[length];

    for (int i = 0; i < length; i++)
    {
        cin >> kings[i].first;
        cin >> kings[i].second.first;
        kings[i].second.second = RomanToDecimal(kings[i].second.first);
    }

    sort(kings, kings+length, comparator);

    for (int j = 0; j < length; j++)
    {
        cout << kings[j].first << " "
             << kings[j].second.first << endl;
    }
}

/*
long long inv_count = 0;

bool compareLower(pair<string, pair<string, int>> &a, pair<string, pair<string, int>> &b)
{
    std::string lower_a = a.first;
    std::string lower_b = b.first;

    std::transform(lower_a.begin(), lower_a.end(), lower_a.begin(),
                   [](unsigned char c)
    {
        return std::tolower(c);
    });
    std::transform(lower_b.begin(), lower_b.end(), lower_b.begin(),
                   [](unsigned char c)
    {
        return std::tolower(c);
    });

    //case when kings have the same name
    if (lower_a.compare(lower_b) == 0)
    {
        return a.second.second < b.second.second;
    }
    else
    {
        //case when kings have different names
        return lower_a.compare(lower_b) == 1 ? 0 : 1;
    }
}

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SplitThreeWay(int arr[], int left, int right, int &lEdge, int &rEdge)
{
    //check the two element case
    if (right - left <= 1)
    {
        if (arr[right] < arr[left])
            Swap(&arr[right], &arr[left]);
        lEdge = left;
        rEdge = right;
        return;
    }

    //get the pivot and swap it with rightmost element
    int pivotIndex = left + rand() % (right-left+1);
    int pivot = arr[pivotIndex];
    Swap(&arr[right], &arr[pivotIndex]);

    //swap the elements for partition
    int mid = left;
    while (mid <= right)
    {
        if (arr[mid]<pivot)
        {
            Swap(&arr[left], &arr[mid]);
            left++;
            mid++;
        }
        else if (arr[mid]==pivot)
        {
            mid++;
        }
        else if (arr[mid]>pivot)
        {
            Swap(&arr[mid], &arr[right]);
            right--;
        }
    }

    //shift the edge trackers of middle partition
    lEdge = left--;
    rEdge = right--;
}

void QuicksortThreeWay(int arr[], int left, int right)
{
    if (left<right)
    {
        int lEdge, rEdge;
        SplitThreeWay(arr, left, right, lEdge, rEdge);
        QuicksortThreeWay(arr, left, lEdge);
        QuicksortThreeWay(arr, rEdge, right);
    }
}

void selectionSort(int arr[], int length)
{
    int cur_min_index;

    for (int index = 0; index < length-1; index++)
    {
        cur_min_index = index;
        for (int index2 = index + 1; index2 < length; index2++)
            if (arr[index2] < arr[cur_min_index])
                cur_min_index = index2;

        Swap(&arr[cur_min_index], &arr[index]);
    }
}

void merge(long long arr[], int left, int mid, int right)
{
    int i, j, k, left_len, right_len;

    //get length of right and left sub-arrays
    left_len = mid-left+1;
    right_len = right-mid;

    //declare and fill out two sub-arrays
    long long left_arr[left_len], right_arr[right_len];
    for(i = 0; i < left_len; i++)
    {
        left_arr[i] = arr[left+i];
    }
    for(j = 0; j < right_len; j++)
    {
        right_arr[j] = arr[mid+1+j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i + j < left_len + right_len)
    {
        if (j == right_len || (i < left_len && left_arr[i] < right_arr[j]))
        {
            arr[k] = arrA[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = arrB[j];
            j++;
            k++;
        }
    }


}

void mergeSort(long long arr[], int left, int right)
{
    int mid;
    if(left < right)
    {
        mid = left + (right - left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

int Split(int arr[], int left, int right)
{
    int runner = left;
    int pivot = right;

    for (int i = left; i < right; i++)
    {
        if (arr[i] < arr[pivot])
        {
            Swap(&arr[i], &arr[runner]);
            runner++;
        }
    }
    Swap(&arr[pivot], &arr[runner]);
    return runner;
}

void QuickSort(int arr[], int left, int right)
{
    int pivot, rand_index;
    if (right > left)
    {
        pivot = left + rand() % (right-left+1);
        Swap(&arr[right], &arr[pivot]);
        pivot = Split(arr, left, right);
        QuickSort(arr, left, pivot-1);
        QuickSort(arr, pivot+1, right);
    }
}

*/
