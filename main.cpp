//
// Created by david on 03/04/2022.
//

#include <iostream>
#include <cassert>

#include "ringbuf.hpp"

typedef RingBuffer<int> IntRingBuffer;

using namespace std;

int main()
{
    //Stage 1-5
    IntRingBuffer buf(5);
    assert(buf.getSize() == 5);
    assert(buf.getCount() == 0);
    assert(buf.isEmpty());
    assert(!buf.isFull());
    buf.push(1);
    buf.push(2);
    buf.push(3);
    buf.push(4);
    cout<< buf.front()<<endl;
    cout<< buf.back()<<endl;
    buf.pop();
    cout<< buf.front()<<endl;
    buf.pop();
    buf.pop();

    buf.push(10);
    buf.push(11);
    buf.push(12);
    buf.push(13);
    cout<< buf.front()<<endl;
    cout<< buf.back()<<endl;

    //Stage 6
    //Copy of identical object buf as buf_2
    IntRingBuffer buf_2(buf);
    cout<< buf_2.front()<<endl;
    cout<< buf_2.back()<<endl;

    //Stage 7
    // Assign and copy identical object buf_2 as buf_3
    IntRingBuffer buf_3 = buf_2;
    cout<< buf_3.front()<<endl;
    cout<< buf_3.back()<<endl;

    buf_2.pop();
    buf_2.pop();
    buf_2.pop();
    buf_2.push(55);

    cout<< buf_3.front()<<endl;
    cout<< buf_3.back()<<endl;

    return 0;
}

