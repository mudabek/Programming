#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 27;
const int A_CHARACTER_INT = 97;

long long charToInt(char c)
{
    return (int)(c) - A_CHARACTER_INT;
}

void createStrArr(string seq, int strLen, int* arr)
{
    for (int i = 0; i < strLen; i ++)
    {
        arr[i] = charToInt(seq.at(i));
    }
}

void countCards(int* arr, int len, long long* cnt)
{
    for (int i = 0; i < len; i++)
    {
        cnt[arr[i]] ++;
    }
}

bool addCount(long long* winCount, long long* cardsCount, int c)
{
    winCount[c]++;
    if(winCount[c] <= cardsCount[c])
    {
        return true;
    }
    return false;
}

long long countCombos(int* cards, int* word, int cardLen, int wordLen)
{
    int l, r;
    long long cnt, sum;
    l = r = 0;
    cnt = sum = 0;
    long long cardsCount[ALPHABET_SIZE] = { 0 };
    long long winCount[ALPHABET_SIZE] = { 0 };
    countCards(cards, cardLen, cardsCount);

    while (l < wordLen)
    {
        if((r < wordLen) && addCount(winCount, cardsCount, word[r]))
        {
            sum ++;
            cnt += sum;
            r ++;
        }
        else if (r <= wordLen)
        {
            sum --;
            winCount[word[l]] --;
            l ++;
            if (r != wordLen)
                winCount[word[r]] --;
        }
    }

    return cnt;
}

int main()
{
    int wordL, cardsL;
    string word, cards;

    cin >> wordL >> cardsL;
    cin >> word >> cards;

    int cardsArr[cardsL], wordArr[wordL];
    createStrArr(cards, cardsL, cardsArr);
    createStrArr(word, wordL, wordArr);

    cout << countCombos(cardsArr, wordArr, cardsL, wordL);

    return 0;
}
