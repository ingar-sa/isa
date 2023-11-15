#ifndef ISA_SORT_HPP

#include <stdint.h>

template <typename T>
T
isaMedian3Sort(T *Arr, uint64_t L, uint64_t R)
{
    uint64_t Mid = (L + R) / 2;

    if(Arr[L] > Arr[Mid])
    {
        Swap(Arr[L], Arr[Mid]);
    }

    if(Arr[Mid] > Arr[R])
    {
        Swap(Arr[Mid], Arr[R]);

        if(Arr[L] > Arr[Mid])
        {
            Swap(Arr[L], Arr[Mid]);
        }
    }

    return Mid;
}

template <typename T>
T
isaSplit(T *Arr, uint64_t L, uint64_t R)
{
    uint64_t Mid = Median3Sort(Arr, L, R);
    T SplitVal = Arr[Mid];

    Swap(Arr[Mid], Arr[R - 1]);

    uint64_t iL, iR;
    for(iL = L, iR = R - 1;;)
    {
        while(Arr[++iL] < SplitVal);
        while(Arr[--iR] > SplitVal);

        if(iL >= iR) break;

        Swap(Arr[iL], Arr[iR]);
    }

    Swap(Arr[iL], Arr[R - 1]);

    return iL;
}

template <typename T>
void
isaFindMinAndMaxPos(T *Arr, uint64_t Len,
                    uint64_t *MinPos, uint64_t *MaxPos)
{
    T Min = Arr[0];
    T Max = Arr[0];
    uint64_t MinIdx = 0;
    uint64_t MaxIdx = 0;

    for(uint64_t i = 0; i < Len; ++i)
    {
        T Num = Arr[i];

        if(Num < Min)
        {
            Min = Num;
            MinIdx = i;
        }

        if(Num > Max)
        {
            Max = Num;
            MaxIdx = i;
        }
    }

    *MinPos = MinIdx;
    *MaxPos = MaxIdx;
}

template <typename T>
void
isaQuicksortRecursiveStep(T *Arr, uint64_t ArrayLen, uint64_t L, uint64_t R)
{
    if(Arr[L - 1] == Arr[R + 1]) return;

    if(R - L <= 2)
    {
        Median3Sort(Arr, L, R);
        return;
    }

    uint64_t SplitPos = Split(Arr, L, R);
    QuicksortRecursiveStep(Arr, ArrayLen, L, SplitPos - 1);
    QuicksortRecursiveStep(Arr, ArrayLen, SplitPos + 1, R);

}

template <typename T>
void
isaQuicksort(T *Arr, uint64_t ArrayLen)
{
    uint64_t MinPos, MaxPos;
    FindMinAndMaxPos(Arr, ArrayLen, &MinPos, &MaxPos);

    Swap(Arr[0], Arr[MinPos]);
    Swap(Arr[ArrayLen - 1], Arr[MaxPos]);

    QuicksortRecursiveStep(Arr, ArrayLen, 1, ArrayLen - 2);
}

#define ISA_SORT_HPP
#endif