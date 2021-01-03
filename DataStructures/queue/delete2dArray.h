// delete a two-dimensional array

#ifndef delete2dArray_
#define delete2dArray_

template <class T>
void delete2dArray(T**& theArray, int numberOfRows)
{// Delete the two-dimensional array theArray.

   // delete the memory for each row
    for (int i = 0; i < numberOfRows; i++)
        delete[] theArray[i];

    // delete the row pointers
    delete[] theArray;
    theArray = nullptr;
}
#endif
