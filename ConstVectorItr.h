//
// Created by mfbut on 3/11/2018.
//

#ifndef MYVECTOR_CONSTVECTORITR_H
#define MYVECTOR_CONSTVECTORITR_H

#include <sstream>

template<typename T>
class MyVector;

template <typename T>
class ConstVectorItr {
    friend MyVector<T>;
public:
    ConstVectorItr(const MyVector<T>& myvector, unsigned int pos);

    ConstVectorItr& operator++(); //pre
    ConstVectorItr operator++(int); //post

    ConstVectorItr& operator--(); // pre
    ConstVectorItr operator--(int); //post

    ConstVectorItr& operator+=(const unsigned int& rhs); //advance rhs elements
    ConstVectorItr operator+(const unsigned int& rhs); //create a new iterator that is rhs elements beyond the current one

    ConstVectorItr& operator-=(const unsigned int& rhs); //go back rhs elements
    ConstVectorItr operator-(const unsigned int& rhs); // create a new iterator that is rhs elements before the current one

    operator bool() const; // true if pointing to an element within the vector
    bool operator!() const; // true if pointing outside the bounds of the vector
    bool operator==(const ConstVectorItr<T>& rhs) const; // true if referring to the same vector and (at the same position or out of bounds)
    bool operator!=(const ConstVectorItr<T>& rhs) const; // opposite of ==

    //  T& operator*(); //get the element at the current position
    const T& operator*() const; //get the element at the current position

    unsigned int getpos(){
        return pos;
    }
private:
    const MyVector<T>& myvector;
    unsigned int pos;
};

#include "MyVector.h"
#include <ostream>
template<typename T>
ConstVectorItr<T>::ConstVectorItr(const MyVector<T>& myvector, unsigned int pos) : myvector(myvector), pos(pos){
}

template<typename T>
ConstVectorItr<T>& ConstVectorItr<T>::operator++() {
    pos++;
    return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator++(int) {
    return ++(*this);
}

template<typename T>
ConstVectorItr<T>& ConstVectorItr<T>::operator--() {
    pos--;
    return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator--(int) {
    return --(*this);
}

template<typename T>
ConstVectorItr<T>& ConstVectorItr<T>::operator+=(const unsigned int& rhs) {
    pos += rhs;
    return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator+(const unsigned int& rhs) {
    ConstVectorItr copy(*this);
    return copy += rhs;
}

template<typename T>
ConstVectorItr<T>& ConstVectorItr<T>::operator-=(const unsigned int& rhs) {
    pos -= rhs;
    return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator-(const unsigned int& rhs) {
    ConstVectorItr copy(*this);
    return copy -= rhs;
}

template<typename T>
ConstVectorItr<T>::operator bool() const{
    return pos >= 0 && pos < myvector.size();
} // true if pointing to an element within the vector

template<typename T>
bool ConstVectorItr<T>::operator!() const{
    return !static_cast<bool>(*this);
} // true if pointing outside the bounds of the vector

template<typename T>
bool ConstVectorItr<T>::operator==(const ConstVectorItr<T>& rhs) const{
    if (&myvector != &rhs.myvector) {
        return false;
    } else if (!*this && !rhs) {
        return true;
    } else {
        return pos == rhs.pos;
    }
} // true if referring to the same vector and (at the same position or out of bounds)

template<typename T>
bool ConstVectorItr<T>::operator!=(const ConstVectorItr<T>& rhs) const{
    return !(*this == rhs);
} // opposite of ==


template<typename T>
const T& ConstVectorItr<T>::operator*() const{
    if (*this) {
        return myvector.at(pos);
    }else{
        std::stringstream errorStream;
        errorStream << "Out of bounds exception. Attempted to access the vector at " <<  pos  <<   "but there are only "  <<  myvector.numContained <<  " elements. ";
        throw std::out_of_range(errorStream.str());
    }
} //get the element at the current position

#endif //MYVECTOR_CONSTVECTORITR_H



