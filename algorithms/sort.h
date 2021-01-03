// some algorithms about sort

#ifndef ALGORITHMS_SORT_
#define ALGORITHMS_SORT_

#include <iostream>
#include <algorithm>


// rank sort without additional array

template<class T>
void rankOfSort(T a[], int n, int r[])
{// Rank the n elements a[0:n-1].
 // Element ranks returned in r[0:n-1]
    for (int i = 0; i < n; i++)
        r[i] = 0;  // initialize

     // compare all element pairs
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] <= a[i]) r[i]++;
            else r[j]++;
}

template<class T>
void rearrange(T a[], int n, int r[])
{// In-place rearrangement into sorted order. 
    using std::swap();
    for (int i = 0; i < n; i++)
        // get proper element to a[i]
        while (r[i] != i)
        {
            int t = r[i];
            swap(a[i], a[t]);
            swap(r[i], r[t]);
        }
}
template<class T>
void rearrange2(T a[], int n, int r[])
{// Rearrange the elements of a into sorted order
 // using an additional array u.
    T* u = new T[n]; // create additional array

    // move to correct place in u
    for (int i = 0; i < n; i++)
        u[r[i]] = a[i];

    // move back to a
    for (i = 0; i < n; i++)
        a[i] = u[i];

    delete[] u;
}


// early terminating selection sort

template<class T>
void selectionSort(T a[], int n)
{// Early-terminating version of selection sort.
    using std::swap();
    bool sorted = false;
    for (int size = n; !sorted && (size > 1); size--)
    {
        int indexOfMax = 0;
        sorted = true;
        // find largest
        for (int i = 1; i < size; i++)
            if (a[indexOfMax] <= a[i]) indexOfMax = i;
            else sorted = false; // out of order
        swap(a[indexOfMax], a[size - 1]);
    }
}


// early terminating bubble sort

template<class T>
bool bubble(T a[], int n)
{// Bubble largest element in a[0:n-1] to right.
    using std::swap();
    bool swapped = false; // no swaps so far
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1])
        {
            swap(a[i], a[i + 1]);
            swapped = true; // swap was done
        }
    return swapped;
}

template<class T>
void bubbleSort(T a[], int n)
{// Early-terminating version of bubble sort.
    for (int i = n; i > 1 && bubble(a, i); i--);
}


// insertion sort

template<class T>
void insert(T a[], int n, const T& x)
{// Insert x into the sorted array a[0:n-1].
    int i;
    for (i = n - 1; i >= 0 && x < a[i]; i--)
        a[i + 1] = a[i];
    a[i + 1] = x;
}
template<class T>
void insertionSort2(T a[], int n)
{// Sort a[0:n-1] using the insertion sort method.
    for (int i = 1; i < n; i++)
    {
        T t = a[i];
        insert(a, i, t);
    }
}

template<class T>
void insertionSort(T a[], int n)
{// Sort a[0:n-1] using the insertion sort method.
    for (int i = 1; i < n; i++)
    {// insert a[i] into a[0:i-1]
        T t = a[i];
        int j;
        for (j = i - 1; j >= 0 && t < a[j]; j--)
            a[j + 1] = a[j];
        a[j + 1] = t;           // The reason why there's "j+1" is that there is "j--" in the last loop of for 
    }
}

/**
 *  bin sort and radix sort
 *  https://github.com/xiaoxing30/dsaa_cpp2/blob/master/DataStructures/linearList/chain.h
**/

/**
 * merge sort
 * see mergeSort.h
 */

// quick sort
template<typename T>
void quickSort(T a[],int n)
{// Sort a[0:n-1] using the quick sorted method.
    if (n <= 1) return;
    // move largest element to right end
    int max = indexOfMax(a, n);
    std::swap(a[n - 1], a[max]);
    quickSort(a, 0, n - 2);
}

template<typename T>
void quickSort(T a[], int leftEnd, int rightEnd)
{// Sort a[leftEnd : rightEnd], a[rightEnd+1] >= a[leftEnd : rightEnd].
    if (leftEnd >= rightEnd) return;

    int leftCursor = leftEnd,           // left-to-right cursor
        rightCursor = rightEnd + 1;     // right-to-left cursor
    T pivot = a[leftEnd];

    // swap elements >= pivot on left side
    // with elements <= pivot on right side
    while (true)
    {
        do {// find >= element on left side
            leftCursor++;
        } while (a[leftCursor] < pivot);

        do{// find <= element on right side
            rightCursor--;
        } while (a[rightCursor] > pivot);

        if (leftCursor >= rightCursor) break;   // swap pair not found
        std::swap(a[leftCursor], a[rightCursor]);
    }

    // place pivot 
    a[leftEnd] = a[rightCursor];
    a[rightCursor] = pivot;

    quickSort(a, leftEnd, rightCursor - 1);     // sort left segment
    quickSort(a, rightCursor + 1, rightEnd);    // sort right segment
}


#endif // !ALGORITHMS_SORT_
