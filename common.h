#ifndef __COMMON_H__
#define __COMMON_H__

template<class T>
void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

#endif
