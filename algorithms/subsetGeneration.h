// some algorithms about subset generation

#ifndef ALGORITHMS_SUBSET_GENERATION_
#define ALGORITHMS_SUBSET_GENERATION_

#include <iostream>
#include <algorithm>
#include <iterator>

// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c1/e29.htm

/** generate all subsets of n elements */

template<typename T>
void rSubsets(T x[], T subX[], size_t i, size_t n);

template <typename T, size_t N>
void allSubsets(T(&x)[N])
{
    T* subX = new T[N];
    std::copy(x, x + N, subX);
    rSubsets(x, subX, 0, N);
    delete[] subX;
}

template<typename T>
void rSubsets(T x[], T subX[], size_t i, size_t n)
{
    if (i == n - 1)
    {// x[n-1] can be 0 or 1
        // output subset without last element
        subX[n - 1] = T{};
        std::copy(subX, subX + n, std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl;

        // output subset with last element
        subX[n - 1] = x[n - 1];
        std::copy(subX, subX + n, std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl;
        return;
    }

    // leave element i out
    subX[i] = T{};
    // generate all subsets with i excluded
    rSubsets(x, subX, i + 1, n);

    // put element i into subset
    subX[i] = x[i];
    // generate all subsets with i included
    rSubsets(x, subX, i + 1, n);
}


#endif // !ALGORITHMS_SUBSET_GENERATION_
