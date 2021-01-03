// abstract class dictionary
// abstract data type specification for dictionary data structure
// all methods are pure virtual functions
// K is key type and E is value type

#ifndef dictionary_
#define dictionary_

#include <utility>

template<typename K,typename E>
class dictionary
{
public:
    virtual ~dictionary() {}
    virtual bool empty() const = 0;
    // return true if dictionary is empty
    virtual int size() const = 0;
    // return number of pairs in dictionary
    virtual std::pair<const K, E>* find(const K&) const = 0;
    // return pointer to matching pair
    virtual void erase(const K&) = 0;
    // remove matching pair
    virtual void insert(const std::pair<const K, E>&) = 0;
    // insert a (key, value) pair into the dictionary
};
#endif