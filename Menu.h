//
// Created by fokus on 07.08.2021.
//
#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H
#endif //UNTITLED_MENU_H
#include "ISorter.h"
#include <chrono>
#include <cstdlib>

void sep() {
    std::cout << "-----------------------------------------------------------\n";
}

int compare(int a, int b) {
    return a>b ? 1 : 0;
}

template <typename T>
void Print(Sequence<T>* data) {
    cout<<"Do you want to look at sorted sequence? 1 - yes, 0 - no"<<endl;
    char choice;
    cin>>choice;
    if (choice == '1') {
        sep();
        data->Print();
        sep();
    }
}

template <typename T>
void CheckIfSorted(Sequence<T>* data) {
    cout<<"Do you want to check if the sequence is sorted right? 1 - yes, 0 - no"<<endl;
    char cho;
    cin>>cho;
    if (cho == '1') {
        if (data->IsSorted()==true) {
            cout<<"Result of the test: sequence is SORTED"<<endl;
        }
        else {
            cout<<"Result of the test: sequence is NOT SORTED"<<endl;
        }
    }
}

double ShowTime(int time, string name) {
    cout<<"Press any key to show the time";
    getchar();
    getchar();
    cout<<"Time of "<<name<<" sorting "<<time<<" microseconds"<<"\t"<< time/1000000. <<" seconds"<<endl; ;
    sep();
    cout<<"Press any key to continue"<<endl;
    getchar();
    return time/1000000.;
}

template <typename T>
void SortingMenu(Sequence<T>* data) {
    double bubble_time = 0;
    double shaker_time = 0;
    double selection_time =0;
    double quick_time = 0;
    ISorter<T>* sorter;
    while(true) {
        sep();
        cout << "What type of sorting do you want to apply?" << endl;
        cout << "	0 - Go back\n";
        cout << "	1 - Bubble Sort\n";
        cout << "	2 - Shaker Sort\n";
        cout << "	3 - Selection Sort\n";
        cout << "	4 - Quick Sort\n";
        cout << "	5 - Compare time\n";
        sep();

        char command;
        cin >> command;
        if (command != '5') {
            string  name;

            if (command == '0') {
                return;
            }
            if (command == '1') {
                sorter = new BubbleSorter<T>;
                name = "bubble";
            }
            if (command == '2') {
                sorter = new ShakerSorter<T>;
                name = "shaker";
            }
            if (command == '3') {
                sorter = new SelectionSorter<T>;
                name = "selection";
            }
            if (command == '4') {
                sorter = new QuickSorter<T>;
                name = "quick";
            }

            cout << name <<" sorting:..." << endl;
            auto begin = std::chrono::steady_clock::now();
            Sequence<T> *new_data = sorter->Sort(data, compare);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

            Print(new_data);
            CheckIfSorted(new_data);

            if (name == "bubble") {
                bubble_time = ShowTime(elapsed_ms.count(), name);
            }
            if (name == "shaker") {
                shaker_time = ShowTime(elapsed_ms.count(), name);
            }
            if (name == "selection") {
                selection_time = ShowTime(elapsed_ms.count(), name);
            }
            if (name == "quick") {
                quick_time = ShowTime(elapsed_ms.count(), name);
            }

        }

        if (command == '5') {
            cout<<"Comparing time..."<<endl;
            sep();
            cout<<"Bubble sorting time: "<<bubble_time<< " seconds"<<endl;
            cout<<"Shaker sorting time: "<<shaker_time<< " seconds"<<endl;
            cout<<"Selection sorting time: "<<selection_time<< " seconds"<<endl;
            cout<<"Quick sorting time: "<<quick_time<< " seconds"<<endl;
            sep();

            cout<<"Press any key to continue"<<endl;
            getchar();
        }
    }
}

template<typename T>
void UI() {
    Sequence<T> *data;
    while (true) {
        {
            sep();
            cout << "Commands:\n";
            cout << "	s - Show data\n";
            cout << "	1 - Create a new sequence\n";
            cout << "	2 - Sorting\n";
            cout << "	0 - Exit\n";
            sep();
        }
        char command;
        std::cin >> command;
        if (command == '0') {
            break;
        }
        if (command == 's' || command == 'S') {
            data->Print();
        }
        if (command == '1') {

            cout << "What kind of sequence do you want to use?" << endl;
            cout << " 1 - ArraySequence, 0 - ListSequence:" << endl;

            char ch;
            cin >> ch;

            cout << "What size do you want sequence to be?:" << endl;
            int len;
            cin >> len;
            cout << "Manual or automatic filling? 0-manual | 1 - auto" << endl;
            char choice;
            cin >> choice;

            if (ch == '1') {
                data = (Sequence<int> *) new ArraySequence<int>(len);
                if (choice == '1') {
                    cout << "Filling the sequence..." << endl;
                    for (int i = 0; i < len; i++) {
                        T item = rand()%5000-2500;
                        data->Set(i,item);
                    }
                }
                else if (choice == '0') {
                    for (int i = 0; i < len; i++) {
                        cout << i + 1 << " element: ";
                        T item;
                        cin >> item;
                        data->Set(i,item);
                    }
                }
                else {
                    cout<<"Try again"<<endl;
                }

            } else if (ch == '0') {
                data = (Sequence<int> *) new ListSequence<int>();
                if (choice == '1') {
                    for (int i = 0; i < len; i++) {
                        T item = rand()%5000-2500;
                        data->Append(item);
                    }
                }
                else if (choice == '0') {
                    for (int i = 0; i < len; i++) {
                        cout << i + 1 << " element: ";
                        T item;
                        cin >> item;
                        data->Append(item);
                    }
                }
                else {
                    cout<<"Try again"<<endl;
                }
            }
            else {
                cout<<"Try again"<<endl;
            }
        }
        if (command == '2') {
            SortingMenu<T>(data);
        }
        if (command == '3') {

        }
    }
}