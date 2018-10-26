//
// Created by mfbut on 3/10/2018.
//

#ifndef MYVECTOR_MYVECTOR_H
#define MYVECTOR_MYVECTOR_H

#include <sstream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <vector>
#include <ostream>
#include "VectorItr.h"
#include "ConstVectorItr.h"

template<typename T>
class MyVector {
    friend VectorItr<T>;
    friend ConstVectorItr<T>;
public:
    MyVector();
    explicit MyVector(const unsigned int& numElements); //create numElements empty items
    MyVector(const unsigned int& numElements, const T& value); // create numElements items all initialized to value

    //here I am templating this particular member method over another type U
    //this will allow us to convert things like a vector<vector<string>> to a
    //MyVector<MyVector<string>> which wouldn't be possible othewise
    template <typename U>
    MyVector(const std::vector<U>& values); // create a MyVector with the same values as standard vector
    MyVector(const MyVector& orig); // create a copy of a MyVector
    virtual ~MyVector(); //clean up any dynamically allocated space for a MyVector
    MyVector& operator=(const MyVector& rhs); // make this MyVector have a COPY of all the values in rhs

    unsigned int size() const; // return the
    bool isEmpty() const; //return true if the vector has no elements in it

    T& front(); //return a reference the first element in MyVector
    const T& front() const; //return a const reference the first element in MyVector
    T& back(); //return a reference to the last element in MyVector
    const T& back() const; //return a const reference to the last element in MyVector
    T& at(const unsigned int& index); //return a reference to the element at the specified position
    const T& at(const unsigned int& index) const;  //return a const reference to the element at the specified position
    T& operator[](const unsigned int& index); //return a reference to the element at the specified position
    const T& operator[](const unsigned int& index) const; //return a const reference to the element at the specified position

    //insert a value into the vector at the specified position
    //for the iterator versions the position is wherever they are pointing at in the vector
    void insert(const unsigned int& pos, const T& value);
    void insert(const VectorItr<T>& itr, const T& value);
    void insert(const ConstVectorItr<T>& itr, const T& value);

    //remove a value from the vector at the specified position
    //for the iterator versions the position is wherever they are pointing at in the vector
    void erase(const unsigned int& pos);
    void erase(const VectorItr<T>& itr);
    void erase(const ConstVectorItr<T>& itr);

    void pushBack(const T& value); // add an element to the end of the vector
    void popBack(); // remove the last element from the vector

    void clear();// remove all the elements from the vector

    ConstVectorItr<T> begin() const;//get a constant iterator to the beginning of the vector
    ConstVectorItr<T> end() const; //get a constant iterator to the end of the vector

    VectorItr<T> begin(); //get a mutating iterator to the beginning of the vector
    VectorItr<T> end();  //get a mutating iterator to the beginning of the vector

    ConstVectorItr<T> cbegin() const;//get a constant iterator to the beginning of the vector
    ConstVectorItr<T> cend() const; //get a constant iterator to the end of the vector
private:
    T** head_array;
    unsigned int capacity;
    unsigned int numContained;
};

//overloaded out for MyVector. Prints {element1 element2 element3 ...}
//you may choose to make this function a friend of MyVector if you want
template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& myVector){
    out << "{";
    for (unsigned int i = 0; i < myVector.size(); i++) {
        out << myVector.at(i) << " ";
    }
    out << "}";
    return out;
}


template<typename T>
MyVector<T>::MyVector(){
    head_array = nullptr;
    capacity = 0;
    numContained = 0;
}

template<typename T>
MyVector<T>::MyVector(const unsigned int& numElements){
    head_array = new T*[numElements];
    for (unsigned int i= 0; i < numElements; i++) {
        head_array[i] = new T;
    }
    MyVector<T>::capacity = numElements;
    numContained = 0;
} //create numElements empty items

template<typename T>
MyVector<T>::MyVector(const unsigned int& numElements, const T& value){
    head_array = new T*[numElements];
    capacity = numElements;
    numContained = numElements;
    for(unsigned int i = 0; i < numElements; i++){
        head_array[i] = new T(value);
//        *(head_array[i]) = value;
    }
}

template<typename T>
MyVector<T>::MyVector(const MyVector& orig){
    head_array = new T*[orig.size()];
    MyVector<T>::capacity = orig.size();
    numContained = capacity;
    for (unsigned int k = 0; k < orig.size(); k ++) {
        head_array[k] = new T(orig.at(k));
    }
} // create a copy of a MyVector

template<typename T>
MyVector<T>::~MyVector(){
    for (unsigned int i = 0; i < capacity; i++) {
        delete head_array[i];
    }
    delete []head_array;
    head_array = nullptr;
} //clean up any dynamically allocated space for a MyVector

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& rhs){
    head_array = new T*[rhs.size()];
    MyVector<T>::capacity = rhs.size();
    numContained = capacity;
    for (unsigned int k = 0; k < rhs.size(); k ++) {
        *head_array[k] = new T(rhs.at(k));
    }
    return *this;
} // make this MyVector have a COPY of all the values in rhs

template<typename T>
unsigned int MyVector<T>::size() const{
    return capacity;
} // return the

template<typename T>
bool MyVector<T>::isEmpty() const{
    if (numContained == 0) {
        return true;
    } else {
        return false;
    }
} //return true if the vector has no elements in it

template<typename T>
T& MyVector<T>::front(){
    return *(head_array[0]);
} //return a reference the first element in MyVector

template<typename T>
const T& MyVector<T>::front() const{
    return *(head_array[0]);
} //return a const reference the first element in MyVector

template<typename T>
T& MyVector<T>::back(){
    return *(head_array[capacity - 1]);
} //return a reference to the last element in MyVector

template<typename T>
const T& MyVector<T>::back() const{
    return *(head_array[capacity - 1]);
} //return a const reference to the last element in MyVector

template<typename T>
T& MyVector<T>::at(const unsigned int& index){
    if (index >= capacity) {
        std::stringstream errorStream;
        errorStream << "Out of bounds exception. Attempted to access the vector at " <<  index  <<   "but there are only "  << numContained <<  " elements. ";
        throw std::out_of_range(errorStream.str());
    }
    return *(head_array[index]);
} //return a reference to the element at the specified position

template<typename T>
const T& MyVector<T>::at(const unsigned int& index) const{
    if (index >= capacity) {
        std::stringstream errorStream;
        errorStream << "Out of bounds exception. Attempted to access the vector at " <<  index  <<   "but there are only "  << numContained <<  " elements. ";
        throw std::out_of_range(errorStream.str());
    }
    return *(head_array[index]);
}  //return a const reference to the element at the specified position

template<typename T>
T& MyVector<T>::operator[](const unsigned int& index){
    if (index >= capacity) {
        std::stringstream errorStream;
        errorStream << "Out of bounds exception. Attempted to access the vector at " <<  index  <<   "but there are only "  << numContained <<  " elements. ";
        throw std::out_of_range(errorStream.str());
    }
    return *(head_array[index]);
} //return a reference to the element at the specified position

template<typename T>
const T& MyVector<T>::operator[](const unsigned int& index) const{
    if (index >= capacity) {
        std::stringstream errorStream;
        errorStream << "Out of bounds exception. Attempted to access the vector at " <<  index  <<   "but there are only "  << numContained <<  " elements. ";
        throw std::out_of_range(errorStream.str());
    }
    return *(head_array[index]);
} //return a const reference to the element at the specified position

//insert a value into the vector at the specified position
//for the iterator versions the position is wherever they are pointing at in the vector
template<typename T>
void MyVector<T>::insert(const unsigned int& pos, const T& value){
    if (pos > capacity) {
         std::stringstream errorStream;
        throw std::out_of_range(errorStream.str());
    }
    T** temp = new T*[capacity + 1];
    for (unsigned int i = 0; i < pos; i++) {
        temp[i] = new T(*head_array[i]);
    }
    temp[pos] = new T(value);
    for (unsigned int i = pos + 1; i < capacity + 1; i++) {
        temp[i] = new T(*head_array[i - 1]);
    }
    capacity ++;
    numContained = capacity;
    delete[] head_array;
    head_array = new T*[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        head_array[i] = new T(*temp[i]);
        temp[i] = nullptr;
    }
    delete []temp;
}

template<typename T>
void MyVector<T>::insert(const VectorItr<T>& itr, const T& value){
    unsigned int a = itr.pos;
    insert(a, value);
}

template<typename T>
void MyVector<T>::insert(const ConstVectorItr<T>& itr, const T& value){
    insert(itr.pos, value);
}

//remove a value from the vector at the specified position
//for the iterator versions the position is wherever they are pointing at in the vector
template<typename T>
void MyVector<T>::erase(const unsigned int& pos){
    if (pos > capacity) {
        std::stringstream errorStream;
        throw std::out_of_range(errorStream.str());
    }
    T** temp = new T*[capacity - 1];
    for (unsigned int i = 0; i < pos; i++) {
        temp[i] = new T(*head_array[i]);
    }
    for (unsigned int i = pos; i < capacity - 1; i++) {
        temp[i] = new T(*head_array[i + 1]);
    }
    capacity --;
    numContained = capacity;
    delete[] head_array;
    head_array = new T*[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        head_array[i] = new T(*temp[i]);
    }
    delete []temp;
}
template<typename T>
void MyVector<T>::erase(const VectorItr<T>& itr){
    erase(itr.pos);
}
template<typename T>
void MyVector<T>::erase(const ConstVectorItr<T>& itr){
    erase(itr.pos);
}

template<typename T>
void MyVector<T>::pushBack(const T& value){
    insert(capacity, value);
} // add an element to the end of the vector

template<typename T>
void MyVector<T>::popBack(){
    erase(capacity - 1);
} // remove the last element from the vector

template<typename T>
void MyVector<T>::clear(){
    for (unsigned int i = 0; i < capacity; i++) {
        delete head_array[i];
    }
    delete []head_array;
    head_array = nullptr;
    capacity = 0;
    numContained = 0;
}
//-----------------------begin and end---------------------------------------------


template<typename T>
ConstVectorItr<T> MyVector<T>::begin() const{
    ConstVectorItr<T> temp(*this, 0);
    return temp;
}//get a constant iterator to the beginning of the vector
template<typename T>
ConstVectorItr<T> MyVector<T>::end() const{
    ConstVectorItr<T> temp(*this, capacity);
    return temp;
} //get a constant iterator to the end of the vector



template<typename T>
VectorItr<T> MyVector<T>::begin(){
    VectorItr<T> temp(*this, 0);
    return temp;
} //get a mutating iterator to the beginning of the vector
template<typename T>
VectorItr<T> MyVector<T>::end(){
    VectorItr<T> temp(*this, capacity);
    return temp;
}  //get a mutating iterator to the beginning of the vector



template<typename T>
ConstVectorItr<T> MyVector<T>::cbegin() const{
    ConstVectorItr<T> temp(*this, 0);
    return temp;
}//get a constant iterator to the beginning of the vector

template<typename T>
ConstVectorItr<T> MyVector<T>::cend() const{
    ConstVectorItr<T> temp(*this, capacity);
    return temp;
} //get a constant iterator to the end of the vector



//this is a nested template declaration.
//this is the right way of doing things if you have a template show up inside another template
//I've given you this because we didn't cover it in class
template<typename T>
template <typename U>
MyVector<T>::MyVector(const std::vector<U>& values) : capacity((unsigned int)values.size()), numContained((unsigned int)values.size()) {
    head_array = new T*[capacity];
    for (unsigned int i = 0; i < capacity; i++){
        head_array[i] = new T(static_cast<T>(values.at(i)));
    }
}

#endif //MYVECTOR_MYVECTOR_H
