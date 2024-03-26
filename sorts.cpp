#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

template<typename Cont> Cont filling(Cont cont) { //Заполнитель контейнеров (точно работает на последовательных контейнерах)
    srand(time(0));
    for (unsigned i = 0; i < 10000; i++) {
        cont.push_back(rand() % 10001);
    }
    return cont;
}

//template<typename Cont> int partition (int first, int last, Cont cont) {
//    int counter = 0;
//    int i = first - 1;
//    int j = last + 1;
//    for (auto it = cont.begin(); it != cont.end(); ++it, ++counter) {
//        if (first == counter) {
//            int pivot = *it;
//            auto it1 = it;
//        }
//        if (i == counter) {
//            auto it2 = it;
//        }
//        if (j == counter) {
//            auto it3 = it;
//        }
//    } 
//    while (1) {
//        do {
//            ++it2;
//            i++;
//        } while (*it2 < pivot);
//        do {
//            --it3;
//            j--;
//        } while (*it3 < pivot);
//        if (i >= j) {
//            return j;
//        }
//        std::iter_swap(it2, it3);
//    }
//}

// Разделение с использованием схемы разделения Хоара
int partition(int mas[], int low, int high)
{
    int pivot = mas[low];
    int i = low - 1;
    int j = high + 1;
    while (1)
    {
        do {
            i++;
        } while (mas[i] < pivot);
 
        do {
            j--;
        } while (mas[j] > pivot);
 
        if (i >= j) {
            return j;
        }
 
        swap(mas[i], mas[j]);
    }
}
 
// Процедура быстрой сортировки
void hoar5sort(int mas[], int low, int high)
{
    // базовое условие
    if (low >= high) {
        return;
    }
 
    // Переставляем элементы относительно опорной точки
    int pivot = partition(mas, low, high);
 
    // Повторяем подмассив, содержащий элементы, меньшие опорной точки
    hoar5sort(mas, low, pivot);
 
    // Повторяем подмассив, содержащий элементы, превышающие точку опоры
    hoar5sort(mas, pivot + 1, high);
}

void vsort(int mas[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = mas[i];
        j = i - 1;
 
        //Перетаскиваем элементы среза до j, большие key, на одну позицию вперёд
        while (j >= 0 && mas[j] > key) {
            mas[j + 1] = mas[j];
            j = j - 1;
        }
        mas[j + 1] = key;
    }
}

int main()  
{
    int nums1[10000]; //Создаём два массива
    int nums2[10000];
    srand(time(0));
    for (int i = 0; i < 10000; i++) { //Заполняем их случайными числами
        int x = rand() % 10001;
        nums1[i] = x;
        nums2[i] = x;
    }

    auto start1 = std::chrono::high_resolution_clock::now();
    hoar5sort(nums1, 0, 9999); //Проводим сортировку Хоара (сложность nlogn)
    auto end1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);

    auto start2 = std::chrono::high_resolution_clock::now();
    vsort(nums2, 10000); //Проводим сортировку простыми вставками (сложность n^2)
    auto end2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    if (time1 < time2) {
        std::cout << "First sorting won with the result: " << time1.count() << " milliseconds. " << "Second showed the result: " << \
        time2.count() << " milliseconds."; 
    }
    else if (time1 > time2) {
        std::cout << "Second sorting won with the result: " << time2.count() << " milliseconds. " << "First showed the result: " << \
        time1.count() << " milliseconds.";
    }
    else {
        std::cout << "Both have similar time: " << time2.count() << " milliseconds.";
    }
    return 0;
}