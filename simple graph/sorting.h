#ifndef TRABALHO_TEORIA_DOS_GRAFOS_DCC059_2021_3_SORTING_H
#define TRABALHO_TEORIA_DOS_GRAFOS_DCC059_2021_3_SORTING_H

#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include "NodeCluster.h"
#include "Node.h"

using namespace std;

// /* QuickSort for Quocient Implementation*/

// int medianThree(vector<NodeCluster*>* array, int a, int b, int c){
//     if((array->at(a)->getQuotient() > array->at(b)->getQuotient()) ^ (array->at(a)->getQuotient() > array->at(c)->getQuotient())){
//         return a;
//     }
//     else if((array->at(b)->getQuotient() < array->at(a)->getQuotient()) ^ (array->at(b)->getQuotient() < array->at(c)->getQuotient())){
//         return b;
//     }
//     else{
//         return c;
//     }
// }

// int partition(vector<NodeCluster*>* array, int lo, int hi){
//     int m = (lo + hi)/2;
//     int i = lo - 1;
//     int j = hi - 1;

//     double pivot = array->at(m)->getQuotient();

//     while(true){
//         do {
//             j--;
//         } while(array->at(j)->getQuotient() > pivot);

//         do{
//             i++;
//         } while(array->at(i)->getQuotient() < pivot);

//         if(i < j){
//             NodeCluster* tmp = array->at(i);
//             array->at(i) = array->at(j);
//             array->at(j) = tmp;
//         }
//         else{
//             return j;
//         }
//     }
// }

// template<typename T>
// void quicksort_range(T *array, int lo, int hi) {
//     if (lo < hi) {
//         int p = partition(array, lo, hi);
//         quicksort_range(array, lo, p);
//         quicksort_range(array, p + 1, hi);
//     }
// }

// template<typename T>
// void quicksort(T *array, int n) {
//     quicksort_range(array, 0, n-1);
// }
// /* End of QuickSort for Quocient Implementation */

// /* QuickSort for NodeWeight Implementation */

// int medianThreeWeight(vector<Node*>* listOfNodes, int a, int b, int c){
//     // cout<<"Sorting.h Linha 76"<<endl;
//     if((listOfNodes->at(a)->getWeight() > listOfNodes->at(b)->getWeight()) ^ (listOfNodes->at(a)->getWeight() > listOfNodes->at(c)->getWeight())){
//         return a;
//     }
//     else if((listOfNodes->at(b)->getWeight() > listOfNodes->at(a)->getWeight()) ^ (listOfNodes->at(b)->getWeight() > listOfNodes->at(c)->getWeight())){
//         return b;
//     }
//     else{
//         return c;
//     }
//     // cout<<"Sorting.h Linha 86"<<endl;
// }

// int partitionWeight(vector<Node*>* listOfNodes, int lo, int hi){
//     // cout<<"Sorting.h Partition Weight Beg"<<endl;
//     int m = (lo + hi)/2;
//     int i = lo - 1;
//     int j = hi - 1;

//     int pivot = listOfNodes->at(m)->getWeight();
//     // cout<<"Sorting.h Linha 96"<<endl;
//     while(true){
//         do{
//             j--;
//         } while (listOfNodes->at(j)->getWeight() > pivot);
//         // cout<<"Sorting.h Linha 101"<<endl;
//         do{
//             i++;
//         } while (listOfNodes->at(i)->getWeight() < pivot);
//         // cout<<"Sorting.h Linha 105"<<endl;
//         if (i < j){
//             Node* tmp = listOfNodes->at(i);
//             // cout<<"Sorting.h Linha 108"<<endl;
//             //copy node in j to node in i
//             listOfNodes->at(i)->setNextNode(listOfNodes->at(j)->getNextNode());
//             listOfNodes->at(i)->setPosition(listOfNodes->at(j)->getPosition());
//             listOfNodes->at(i)->setVisited(listOfNodes->at(j)->getVisited());
//             listOfNodes->at(i)->setWeight(listOfNodes->at(j)->getWeight());
//             // cout<<"Sorting.h Linha 114"<<endl;
//             //copy temp to j
//             listOfNodes->at(j)->setNextNode(tmp->getNextNode());
//             listOfNodes->at(j)->setPosition(tmp->getPosition());
//             listOfNodes->at(j)->setVisited(tmp->getVisited());
//             listOfNodes->at(j)->setWeight(tmp->getWeight()); /* cout<<"Sorting.h Linha 120"<<endl; */
//         }
//         else{
//             cout<<" ++j++ "<<endl;
//             return j;
//         }
//     }
//     cout<<"Sorting.h Partition Weight End"<<endl;
//     // cout<<"Sorting.h Linha 123"<<endl;
// }

// void quicksort_rangeWeight(vector<Node*>* listOfNodes, int lo, int hi) {
//     // cout<<"Sorting.h Linha 127"<<endl;
//     if(lo < hi){
//         int p = partitionWeight(listOfNodes, lo, hi);
//         quicksort_rangeWeight(listOfNodes, lo, p);
//         quicksort_rangeWeight(listOfNodes, p + 1, hi);
//     }
//     // cout<<"Sorting.h Linha 133"<<endl;
// }

// void quicksortWeight(vector<Node*>* listOfNodes, int n) {
//     // cout<<"Sorting.h Linha 137"<<endl;
//     quicksort_rangeWeight(listOfNodes, 0, n-1);
//     // cout<<"Sorting.h Linha 139"<<endl;
// }
// /* End of QuickSort for NodeWeight Implementation */

/* usar ordenacao a partir de um vetor de Peso e Ids */

template<typename T>
void change_places(T *x, int *y){
    int temp = *y;
    *y = *x;
    *x = temp;
}

template<typename T>
int medianThree(T *arrayToBeSorted, int* arrayIds, int a, int b, int c) {
    if ((arrayToBeSorted[a] > arrayToBeSorted[b]) ^ (arrayToBeSorted[a] > arrayToBeSorted[c])) 
        return a;
    else if ((arrayToBeSorted[b] < arrayToBeSorted[a]) ^ (arrayToBeSorted[b] < arrayToBeSorted[c])) 
        return b;
    else
        return c;
}

template<typename T>
int partition(T *arrayToBeSorted, int* arrayIds, int lo, int hi) 
{
    int m = (lo + hi) / 2;
    int i = lo-1;
    int j = hi+1;
    T pivot = arrayToBeSorted[m];
    while(true)
    {
        do
        {
            j =  j-1;
        
        } while(arrayToBeSorted[j] > pivot);
        do
        {
            i =  i+1;
        
        } while(arrayToBeSorted[i] < pivot);
        if(i < j)
        {
            T tmp = arrayToBeSorted[i];
            int tmpId = arrayIds[i];
            arrayToBeSorted[i] = arrayToBeSorted[j];
            arrayToBeSorted[j] = tmp;
            arrayIds[i] = arrayIds[j];
            arrayIds[j] = tmpId;
        } 
        else return j; 
    } 
}

template<typename T>
void quicksort_range(T *arrayToBeSorted, int* arrayIds, int lo, int hi) {
    if (lo < hi) {
        int p = partition(arrayToBeSorted, arrayIds, lo, hi);
        quicksort_range(arrayToBeSorted, arrayIds, lo, p);
        quicksort_range(arrayToBeSorted, arrayIds, p + 1, hi);
    }
}

template<typename T>
void quickssort(T *arrayToBeSorted, int* arrayIds, int n) {
    quicksort_range(arrayToBeSorted, arrayIds, 0, n-1);
}

#endif