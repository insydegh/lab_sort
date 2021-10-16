//
// Created by fokus on 28.07.2021.
//
#include "random"

//Settings for genarating random numbers
//std::random_device random_device; // Источник энтропии.
//std::mt19937 generator(random_device()); // Генератор случайных чисел.
// (Здесь берется одно инициализирующее значение, можно брать больше)

//std::uniform_int_distribution<> distribution(-1000, 1000); // Равномерное распределение [10, 20]


#ifndef UNTITLED_SEQUENCE_H
#define UNTITLED_SEQUENCE_H

#endif //UNTITLED_SEQUENCE_H
template <typename T> class Sequence {
public:
    //decompose
    virtual int GetSize() const = 0;
    virtual T Get(int index) const = 0;
    virtual T GetLast() const = 0;
    virtual T GetFirst() const = 0;
    virtual Sequence<T>* GetSubSequence(int start, int end) = 0;

    //operations
    virtual void Set(int index, T item) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;

    //Sorting
    virtual void Swap(int index1, int index2) = 0;
    virtual void Print() =0;
    virtual bool IsSorted() = 0;
    virtual Sequence<T>* Clone() = 0;

    // operators
    virtual T operator[](const int index) = 0;

};
