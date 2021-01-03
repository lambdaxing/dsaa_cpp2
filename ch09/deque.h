#ifndef deque_
#define deque_

template<typename T>
class dequeBase
{
public:
    virtual ~dequeBase() {}
    virtual bool empty() const = 0;
    // return true if queue is empty
    virtual int size() const = 0;
    // return number of elements in deque
    virtual T& front() = 0;
    // return reference to the front element
    virtual T& back() = 0;
    // return reference to the back element
    virtual void pop_front() = 0;
    // remove the front element
    virtual void push_back(const T& theElement) = 0;
    // add theElement at the back of the deque
    virtual void pop_back() = 0;
    // remove the back element
    virtual void push_front(const T& theElement) = 0;
    // add theElement at the front of the deque 
};

#endif // !deque_
