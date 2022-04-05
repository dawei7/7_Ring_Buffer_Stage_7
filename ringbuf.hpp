#ifndef RINGBUF_HPP
#define RINGBUF_HPP

/*
 * Some help
ptr++;    // Pointer moves to the next int position (as if it was an array)
++ptr;    // Pointer moves to the next int position (as if it was an array)
++*ptr;   // The value pointed at by ptr is incremented
++(*ptr); // The value pointed at by ptr is incremented
++*(ptr); // The value pointed at by ptr is incremented
*ptr++;   // Pointer moves to the next int position (as if it was an array). But returns the old content
(*ptr)++; // The value pointed at by ptr is incremented
*(ptr)++; // Pointer moves to the next int position (as if it was an array). But returns the old content
*++ptr;   // Pointer moves to the next int position, and then get's accessed, with your code, segfault
*(++ptr); // Pointer moves to the next int position, and then get's accessed, with your code, segfault
*/

#include <stdexcept>


template<typename T>
class RingBuffer {

    // TODO: provide a definition of the class template here.


public:

    // Constructors
    RingBuffer(size_t sz){

        if(sz>0){
            _size = sz;
            _buf = new T[_size]; // New heap memory
            _pTail = _buf;
            _pHead = _buf;
            _tail = 0;
            _head = 0;
            _empty = true;

        }else{
            throw std::invalid_argument("The size value is zero or below zero.");
        }
    }

    //Stage 6
    //Constructor for copying an object of the previously initialized Ring-Buffer
    RingBuffer(const RingBuffer& other):
    _buf(new T[other._size]),
    _size(other._size),
    _head(other._head),
    _tail(other._tail),
    _empty(other._empty)
    {
        // Initializing Pointer adresses
        size_t ofs = other._pHead - other._buf;
        _pHead = _buf + ofs;
        ofs = other._pTail- other._buf;
        _pTail = _buf + ofs;

        //Copy all ring-buffer values
        for(size_t i = 0; i < _size; i++){
            _buf[i] = other._buf[i];
        }
    }

    //Operator overloading "=" to copy the ring-buffer object Stage 7
    RingBuffer& operator= (const RingBuffer& rhv){
        if(this == &rhv){
            return *this;
        }
        //copy and swap idiom
        RingBuffer temp(rhv); //Use the constructor of Stage 6 to copy object
        swap(temp, *this); //Swap object
        return *this; //return object
    }

    // Deconstructor
    ~RingBuffer()
    {
        delete [] _buf; // Free Heap Memory
    }

    //Static functions Stage 7
    static void swap(RingBuffer& lhv, RingBuffer rhv) noexcept
    {
        std::swap(lhv._buf, rhv._buf);
        std::swap(lhv._size, rhv._size);
        std::swap(lhv._head, rhv._head);
        std::swap(lhv._tail, rhv._tail);
        std::swap(lhv._empty, rhv._empty);
        std::swap(lhv._pTail, rhv._pTail);
        std::swap(lhv._pHead, rhv._pHead);
    }

    //public functions
    size_t getSize() const{
        return _size;
    }

    size_t getCount() const{
        if (_tail == _head && isEmpty()) {
            return 0;
        }else if (_tail > _head) {
            return _tail - _head;
        }else {
            return getSize() + _tail - _head;
        }
    }

    size_t getFree() const{
        return _size - getCount();
    }

    bool isEmpty() const{
        return _empty;
    }

    bool isFull() const{
        if(getCount()==getSize()){
            return true;
        }
        else{
            return false;
        }
    }

    void push(const T& value){
        if(isFull()){
            throw std::out_of_range("The buffer is full.");
        }else{
            //Push new value
            *_pTail = value;
            // Forward tail integer & tail pointer to the next buffer element
            ++_tail;
            ++_pTail;
            //Check if buffer reached end of array, if yes, begin again at first position (therefore ring-buffer)
            if(_tail==_size){
                _tail = 0;
                _pTail = _buf;
            }
            // If a new element is pushed, it is never empty
            _empty = false;
        }
    }

    T& front(){
        if(isEmpty()){
            throw std::out_of_range("The buffer is empty.");
        }
        return *_pHead; // Just show what is in front.
    }

    const T& front() const{
        if(isEmpty()) {
            throw std::out_of_range("The buffer is empty.");
        }
        return *_pHead; // Just show what is in front.
    }

    T& back(){
        if(isEmpty()) {
            throw std::out_of_range("The buffer is empty.");
        }
        size_t my_tail = _tail;
        if(my_tail==0){
            while(my_tail<_size-1){
                ++_pTail; //Move pointer to end -1 of array, previous element of 0 ring buffer element
                ++my_tail;
            }
            T& my_value = *_pTail;
            _pTail = _buf; //Move back to Original position
            return my_value;
        }else {
            --_pTail;
            T& my_value = *_pTail;
            ++_pTail; //Move back to Original position
            return my_value;
        }
    }

    const T& back() const{
        if(isEmpty()) {
            throw std::out_of_range("The buffer is empty.");
        }
        size_t my_tail = _tail;
        if(my_tail==0){
            while(my_tail<_size-1){
                ++_pTail; //Move pointer to end -1 of array, previous element of 0 ring buffer element
                ++my_tail;
            }
            T& my_value = *_pTail;
            _pTail = _buf; //Move back to Original position
            return my_value;
        }else {
            --_pTail;
            T& my_value = *_pTail;
            ++_pTail; //Move back to Original position
            return my_value;
        }
    }

    void pop(){
        if(isEmpty()){
            throw std::out_of_range("The buffer is empty.");
        }
        // Pop head
        ++_head;
        ++_pHead;
        // Check if buffer reached end of array, if yes, begin again at first position (therefore ring-buffer)
        if(_head==_size){
            _head = 0;
            _pHead = _buf;
        }
        // If an element is popped, check if ring buffer is empty
        if(_pHead==_pTail){
            _empty = true;
        }
    }



private:
    //private fields
    T* _buf;
    size_t _size;
    T* _pTail;
    T* _pHead;
    size_t _tail;
    size_t _head;
    bool _empty;


};


#endif //RINGBUF_HPP