//
// Created by fokus on 28.07.2021.
//

#ifndef UNTITLED_LISTSEQUENCE_H
#define UNTITLED_LISTSEQUENCE_H

#endif //UNTITLED_LISTSEQUENCE_H
#include "ArraySequence.h"
#include "LinkedList.h"
#pragma once

template <class T>
class ListSequence : public Sequence<T>{

private:
    LinkedList<T>* linked_list;

public:
    // CONSTRUCTORS

    ListSequence()  {
        this->linked_list = new LinkedList<T>();
    }
    ListSequence(T* item, int size)  {
        this->linked_list = new LinkedList<T>(item, size);
    }
    ListSequence(LinkedList<T>* list) {
        this->linked_list = list;
    }
    ListSequence(const ListSequence<T>& seq) {
        this->linked_list = new LinkedList<T>(*seq.linked_list);
    }



    //DECOMPOSITION
    int GetSize() const override{
        return this->linked_list->GetLength();
    }

    T Get(int index) const override{
        if (index<0) {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return this->linked_list->Get(index);
    }

    T GetFirst() const override {
        if (this->GetSize()==0) {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return this->linked_list->GetFirst();
    }

    T GetLast() const override {
        if (this->GetSize()==0) {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return this->linked_list->GetLast();
    }

    ListSequence<T>* GetSubSequence(int start, int end) override {
        if (start<0 || start>=this->GetSize() || end<0 || end >=this->GetSize() || end<start) {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        LinkedList<T>* list = new LinkedList<T>();
        list = this->linked_list->GetSublist(start, end);
        ListSequence<T>* listSequence =new ListSequence<T>(list);
        return listSequence;
    }


    //OPERATIONS

    void Set(int index, T item) override {
        if ((index<0) || index>this->GetSize()) {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return this->linked_list->Set(index, item);
    }

    void Prepend(T item) override { //++
        this->linked_list->Prepend(item);
    }

    void Append(T item) override { //++
        this->linked_list->Append(item);
    }

    void InsertAt(T item, int index) override {
        this->linked_list->InsertAt(item, index);
    }

    void Swap(int index1, int index2) override {
        T temp;
        temp = this->Get(index1);
        this->Set(index1, this->Get(index2));
        this->Set(index2, temp);
    }

    void Print() override {
        for (int i =0; i<this->GetSize();i++) {
            cout<<this->Get(i)<<" ";
        }
        cout<<endl;
    }

    bool IsSorted() override {
        bool flag = true;
        for (int i = 0; i<this->GetSize()-2; i++) {
            if (this->Get(i)>this->Get(i+1)) {
                flag = false;
            }
        }
        return flag;
    }

    Sequence<T>* Clone() override {
        Sequence<T>* seq = (Sequence<int>*) new ListSequence<T>(*this);
        return seq;
    }

    ListSequence<T>* Concat(Sequence<T>* list) override {
        ListSequence<T>* newlinkedlist = new ListSequence<T>;
        for (int i = 0; i < this->GetSize(); i++) {
            newlinkedlist->Append(this->Get(i));
        }

        for (int i = 0; i < list->GetSize(); i++) {
            newlinkedlist->Append(list->Get(i));

        }
        return newlinkedlist;
    }

    //OPERATORS

    virtual T operator[](const int index) override {
        return this->linked_list->Get(index);
    };


//DESTRUCTOR
    ~ListSequence() = default;
};