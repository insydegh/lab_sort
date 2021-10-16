//
// Created by fokus on 14.09.2021.
//
#include "ISorter.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int comp(int a, int b) {
    return a>b ? 1 : 0;
}

int a[] = {1, 2, 3, 4, 5, 6};
int *ptr = a;

TEST_CASE( "DYNAMIC ARRAY TESTS", "[DynamicArray]" ) {

    SECTION("Empty") {
        //Creating an empty Dynamic Array with 0 size
        DynamicArray<int> array = DynamicArray<int>();
        REQUIRE(array.GetSize() == 0);
    }
    SECTION("D.A. Creation by size", "[DynamicArray]") {
        //Creating an empty array with 5 size
        DynamicArray<int> array = DynamicArray<int>(5);
        REQUIRE(array.GetSize() == 5);
        REQUIRE_THROWS(DynamicArray<int>(-1), NEGATIVE_SIZE);
    }

    SECTION("D.A. Creation from array", "[DynamicArray]") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        //Creting an Dynamic Array from int array : it will look like
        // elements { 1 2 3 4 5 }
        // index      0 1 2 3 4
        REQUIRE(array.GetSize() == 5);
        REQUIRE(array.Get(0) == 1);
        REQUIRE(array.Get(4) == 5);
        REQUIRE_THROWS(DynamicArray<int>(ptr, -1), NEGATIVE_SIZE);
    }

    SECTION("D.A Creating from D.A") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        DynamicArray<int> array1 = DynamicArray<int>(array);
        REQUIRE(array == array1);
        //Checking copying
    }

    SECTION("Get size") {
        DynamicArray<int> array = DynamicArray<int>(5);
        REQUIRE(array.GetSize()==5);
        // elements { 1 2 3 4 5 }
        // index      0 1 2 3 4
        //Check if size == 5
    }
    SECTION("Get") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        REQUIRE(array.Get(0) == 1);
        REQUIRE(array.Get(4) == 5);
        REQUIRE_THROWS(array.Get(-1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(array.Get(5), INDEX_OUT_OF_RANGE);
    }

    SECTION("Set element") {
        DynamicArray<int> array = DynamicArray<int>(5);
        array.Set(1,333);
        REQUIRE(array.Get(1) == 333);
        REQUIRE_THROWS(array.Set(-1, 333), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(array.Set(5, 333), INDEX_OUT_OF_RANGE);
        //Resulting must look like
        // elements { 1 333 3 4 5 }
        // index      0  1  2 3 4
    }

    SECTION("Resize") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        array.Resize(3);
        REQUIRE_THROWS(array.Resize(-1), NEGATIVE_SIZE);
        REQUIRE_THROWS(array.Get(3), INDEX_OUT_OF_RANGE);
        REQUIRE(array.Get(2)==3);
        REQUIRE(array.Get(0)==1);
        // Resulting must look like
        // elements { 1 2 3  }
        // index      0 1 2
    }


    SECTION("Operator []") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        REQUIRE_THROWS(array[-1], INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(array[5], INDEX_OUT_OF_RANGE);
        REQUIRE(array[2] ==3);
    }
}

TEST_CASE("LINKED LIST TESTS", "[LinkedList]") {
    SECTION("Empty") {
        LinkedList<int> list = LinkedList<int>();
        REQUIRE(list.GetLength()==0);
        //Creating an empty list with size = 0
    }
    SECTION("L.L. Creation from array") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE_THROWS(LinkedList<int>(ptr, -1), NEGATIVE_SIZE);
        REQUIRE(list.Get(0) ==1);
        REQUIRE(list.Get(4) == 5);
        REQUIRE(list.GetLength()==5);
        // elements { 1 2 3 4 5 }
        // index      0 1 2 3 4
    }

    SECTION("L.L. Creation from L.L.") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        LinkedList<int> list1 = LinkedList<int>(list);
        REQUIRE(list.GetLength() == list1.GetLength());
        REQUIRE(list.Get(0)==list1.Get(0));
        REQUIRE(list.Get(4) == list1.Get(4));
        //Copying
        // elements { 1 2 3 4 5 }
        // index      0 1 2 3 4
    }

    SECTION("Get Length") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE(list.GetLength()==5);
    }

    SECTION("Get") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE(list.Get(0) ==1);
        REQUIRE(list.Get(4) == 5);
        REQUIRE_THROWS(list.Get(-1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list.Get(5), INDEX_OUT_OF_RANGE);

    }
    SECTION("GetLast/GetFirst") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE(list.GetFirst()==1);
        REQUIRE(list.GetLast()==5);
        LinkedList<int> list2 = LinkedList<int>();
        REQUIRE_THROWS(list2.GetLast(), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list2.GetFirst(), INDEX_OUT_OF_RANGE);

    }
    SECTION("Get sublist") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        LinkedList<int>* list1 = new LinkedList<int>();
        list1 = list.GetSublist(1,3);
        REQUIRE(list1->GetLength() == 3);
        REQUIRE(list1->GetFirst()==2);
        REQUIRE((list1->GetLast())==4);
        REQUIRE_THROWS(list.GetSublist(-1,3), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list.GetSublist(1,5), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list.GetSublist(3,1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list.GetSublist(3,-1), INDEX_OUT_OF_RANGE);
        //Choosing elements with index with 1 to 3
        // elements { - 2 3 4 - }
        // index      - 1 2 3 -
        //Resulting list
        // elements {  2 3 4  }
        // index       0 1 2
    }

    SECTION("Append") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        list.Append(333);
        REQUIRE(list.Get(5)==333);
        // elements { 1 2 3 4 5 333 }
        // index      0 1 2 3 4 5
    }
    SECTION("Prepend") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        list.Prepend(222);
        REQUIRE(list.Get(0) == 222);
        // elements { 222 1 2 3 4 5 }
        // index        0 1 2 3 4 5
    }

    SECTION("Insert At") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE_THROWS(list.InsertAt(12, -2), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list.InsertAt(1,5), INDEX_OUT_OF_RANGE);
        list.InsertAt(12,2);
        REQUIRE(list.Get(2) == 12);
        REQUIRE(list.Get(3) == 3);
        // elements { 1 2 12 3 4 5 }
        // index      0 1 2  3 4 5
    }

    SECTION("Concat") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        LinkedList<int>* list1 = new LinkedList<int>();
        list1 = list.Concat(&list);
        REQUIRE(list1->GetLength() == 10);
        REQUIRE(list1->Get(5) == 1);
        REQUIRE((list1->Get(9))== 5);
        //Concating list with itself
        // elements { 1 2 3 4 5 1 2 3 4 5}
        // index      0 1 2 3 4 5 6 7 8 9
    }

    SECTION("operator[]") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE(list[1] == list.Get(1));
    }
    SECTION("Delete First") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        list.DeleteFirst();
        REQUIRE(list.GetLength() == 4);
        REQUIRE(list.Get(0) == 2);
        //Resulting
        // elements { 2 3 4 5 }
        // index      0 1 2 3
    }

    SECTION("Remove at") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE_THROWS(list.RemoveAt(-1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list.RemoveAt(5), INDEX_OUT_OF_RANGE);
        list.RemoveAt(2);
        REQUIRE(list.Get(2) ==4 );
        REQUIRE(list.Get(3) ==5);
        //Remove item with index
        //Result look like
        // elements { 1 2 4 5 }
        // index      0 1 2 3
    }

    SECTION("Set") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE_THROWS(list.Set(-1,12), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(list.Set(5,12), INDEX_OUT_OF_RANGE);
        list.Set(1,122);
        REQUIRE(list.Get(1) == 122);
        //Changing value
        // elements { 1 122 3 4 5 }
        // index      0  1  2 3 4
    }

    SECTION("Clear") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        REQUIRE(list.GetLength()==5);
        list.Clear();
        REQUIRE(list.GetLength()==0);
        //Result is 0 size list
    }
}

TEST_CASE("ARRAY SEQUENCE TESTS", "[ArraySequence]") {
    SECTION("Get") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        REQUIRE(seq.Get(0) == 1);
        REQUIRE(seq.Get(4) == 5);
        REQUIRE_THROWS(seq.Get(-1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.Get(5), INDEX_OUT_OF_RANGE);
        // elements { 1 2 3 4 5 }
        // index      0 1 2 3 4
    }

    SECTION("Get First/Get Last") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        REQUIRE(seq.GetFirst() == 1);
        REQUIRE(seq.GetLast() == 5);
        ArraySequence<int> seq2 = ArraySequence<int>();
        REQUIRE_THROWS(seq2.GetFirst(), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq2.GetLast(), INDEX_OUT_OF_RANGE);
    }

    SECTION("Get Sub Sequence") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        REQUIRE_THROWS(seq.GetSubSequence(-1, 3), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.GetSubSequence(1, -1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.GetSubSequence(1, 0), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.GetSubSequence(1, 6), INDEX_OUT_OF_RANGE);
        ArraySequence<int> *seq1 = new ArraySequence<int>();
        seq1 = seq.GetSubSequence(1, 2);
        REQUIRE(seq1->GetFirst() == 2);
        REQUIRE(seq1->GetLast() == 3);
        //SubSeq result is
        // elements { 2 3 }
        // index      0 1
    }

    SECTION("GetSize") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        REQUIRE(seq.GetSize() == 5);
        // elements { 1 2 3 4 5 } size 5
    }
    SECTION("Set") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        seq.Set(1, 122);
        REQUIRE(seq.Get(1) == 122);
        REQUIRE_THROWS(seq.Set(-1, 122), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.Set(5, 122), INDEX_OUT_OF_RANGE);
        // elements { 1 122 3 4 5 }
        // index      0  1  2 3 4
    }

    SECTION("Append") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        seq.Append(122);
        REQUIRE(seq.Get(5) == 122);
        // elements { 1 2 3 4 5 122}
        // index      0 1 2 3 4  5
    }

    SECTION("Prepend") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        seq.Prepend(111);
        REQUIRE(seq.Get(0) == 111);
        REQUIRE(seq.GetSize() == 6);
        REQUIRE(seq.Get(5) == 5);
        // elements {111 1 2 3 4 5 }
        // index      0  1 2 3 4 5
    }

    SECTION("InsertAt") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        REQUIRE_THROWS(seq.InsertAt(-1, 11), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.InsertAt(5, 12), INDEX_OUT_OF_RANGE);
        seq.InsertAt(222, 2);
        REQUIRE(seq.GetSize() == 6);
        REQUIRE(seq.Get(2) == 222);
        REQUIRE(seq.Get(3) == 3);
        // elements { 1 2 222 3 4 5 }
        // index      0 1  2  3 4 5
    }

    SECTION("Concat") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        ArraySequence<int> *newseq = new ArraySequence<int>();
        newseq = seq.Concat(&seq);
        REQUIRE(newseq->GetSize() == 10);
        REQUIRE(newseq->Get(4) == 5);
        REQUIRE(newseq->Get(5) == 1);
        REQUIRE((newseq->Get(9) == 5));
        //Concating sequence with itself
        // elements { 1 2 3 4 5 1 2 3 4 5}
        // index      0 1 2 3 4 5 6 7 8 9
    }

    SECTION("operator []") {
        DynamicArray<int> array = DynamicArray<int>(ptr, 5);
        ArraySequence<int> seq = ArraySequence<int>(&array);
        REQUIRE(seq[1] == 2);
        REQUIRE(seq[0] == 1);
        REQUIRE(seq[4] == 5);
        REQUIRE_THROWS(seq[-1], INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq[5], INDEX_OUT_OF_RANGE);
    }
}



TEST_CASE("LIST SEQUENCE TESTS", "[ListSequence]") {

    SECTION("Get") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        REQUIRE(seq.Get(0) == 1);
        REQUIRE(seq.Get(4) == 5);
        REQUIRE_THROWS(seq.Get(-1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.Get(5), INDEX_OUT_OF_RANGE);
        // elements { 1 2 3 4 5 }
        // index      0 1 2 3 4
    }

    SECTION("Get First/Get Last") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        REQUIRE(seq.GetFirst() == 1);
        REQUIRE(seq.GetLast() == 5);
        ArraySequence<int> seq2 = ArraySequence<int>();
        REQUIRE_THROWS(seq2.GetFirst(), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq2.GetLast(), INDEX_OUT_OF_RANGE);
    }

    SECTION("Get Sub Sequence") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        REQUIRE_THROWS(seq.GetSubSequence(-1, 3), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.GetSubSequence(1, -1), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.GetSubSequence(1, 0), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.GetSubSequence(1, 6), INDEX_OUT_OF_RANGE);
        ListSequence<int> *seq1 = new ListSequence<int>();
        seq1 = seq.GetSubSequence(1, 2);
        REQUIRE(seq1->GetFirst() == 2);
        REQUIRE(seq1->GetLast() == 3);
        //SubSeq result is
        // elements { 2 3 }
        // index      0 1
    }

    SECTION("GetSize") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        REQUIRE(seq.GetSize() == 5);
        // elements { 1 2 3 4 5 } size 5
    }
    SECTION("Set") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        seq.Set(1, 122);
        REQUIRE(seq.Get(1) == 122);
        REQUIRE_THROWS(seq.Set(-1, 122), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.Set(5, 122), INDEX_OUT_OF_RANGE);
        // elements { 1 122 3 4 5 }
        // index      0  1  2 3 4
    }

    SECTION("Append") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        seq.Append(122);
        REQUIRE(seq.Get(5) == 122);
        // elements { 1 2 3 4 5 122}
        // index      0 1 2 3 4  5
    }

    SECTION("Prepend") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        seq.Prepend(111);
        REQUIRE(seq.Get(0) == 111);
        REQUIRE(seq.GetSize() == 6);
        REQUIRE(seq.Get(5) == 5);
        // elements {111 1 2 3 4 5 }
        // index      0  1 2 3 4 5
    }

    SECTION("InsertAt") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        REQUIRE_THROWS(seq.InsertAt(-1, 11), INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq.InsertAt(5, 12), INDEX_OUT_OF_RANGE);
        seq.InsertAt(222, 2);
        REQUIRE(seq.GetSize() == 6);
        REQUIRE(seq.Get(2) == 222);
        REQUIRE(seq.Get(3) == 3);
        // elements { 1 2 222 3 4 5 }
        // index      0 1  2  3 4 5
    }

    SECTION("Concat") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        ListSequence<int> *newseq = new ListSequence<int>();
        newseq = seq.Concat(&seq);
        REQUIRE(newseq->GetSize() == 10);
        REQUIRE(newseq->Get(4) == 5);
        REQUIRE(newseq->Get(5) == 1);
        REQUIRE((newseq->Get(9) == 5));
        //Concating sequence with itself
        // elements { 1 2 3 4 5 1 2 3 4 5}
        // index      0 1 2 3 4 5 6 7 8 9
    }

    SECTION("operator []") {
        LinkedList<int> list = LinkedList<int>(ptr, 5);
        ListSequence<int> seq = ListSequence<int>(&list);
        REQUIRE(seq[1] == 2);
        REQUIRE(seq[0] == 1);
        REQUIRE(seq[4] == 5);
        REQUIRE_THROWS(seq[-1], INDEX_OUT_OF_RANGE);
        REQUIRE_THROWS(seq[5], INDEX_OUT_OF_RANGE);
    }
}

int array1[] = {9, 8, 7 , 6, 5 ,4, 3 ,2, 1, 0};
int *arr1 = array1;
int array2[] = {9, 8, 7 , 6, 5 ,4, 3 ,2, 1, 0, -1 , -2 , -3 , -4, -5, -6, -7 , -8, -9};
int *arr2 = array2;
int array3[] = {-9, 9, -8, 8, -7, -7, 6, -6, 3, -4};
int *arr3 = array3;
Sequence<int>* seq1_arr = (Sequence<int> *) new ArraySequence<int>(arr1, 10);
Sequence<int>* seq2_arr = (Sequence<int> *) new ArraySequence<int>(arr2, 19);
Sequence<int>* seq3_arr = (Sequence<int> *) new ArraySequence<int>(arr3, 10);

Sequence<int>* seq1_lst = (Sequence<int> *) new ListSequence<int>(arr1, 10);
Sequence<int>* seq2_lst = (Sequence<int> *) new ListSequence<int>(arr2, 19);
Sequence<int>* seq3_lst = (Sequence<int> *) new ListSequence<int>(arr3, 10);

TEST_CASE("SORTING") {
    ISorter<int>* sorter;
    SECTION("BUBBLE") {
        sorter = new BubbleSorter<int>;
        REQUIRE((sorter->Sort(seq1_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq1_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_lst, comp))->IsSorted() == 1);

    }
    SECTION("SHAKER") {
        sorter = new ShakerSorter<int>;
        REQUIRE((sorter->Sort(seq1_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq1_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_lst, comp))->IsSorted() == 1);
    }
    SECTION("SELECTION") {
        sorter = new SelectionSorter<int>;
        REQUIRE((sorter->Sort(seq1_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq1_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_lst, comp))->IsSorted() == 1);
    }
    SECTION("QUICK") {
        sorter = new QuickSorter<int>;
        REQUIRE((sorter->Sort(seq1_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_arr, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq1_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq2_lst, comp))->IsSorted() == 1);
        REQUIRE((sorter->Sort(seq3_lst, comp))->IsSorted() == 1);
    }

}



