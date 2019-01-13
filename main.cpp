#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits.h>
using namespace std;

typedef struct liczba {
        unsigned int  x;
        char n;

}Number;
typedef struct heap {
        //unsigned int x;
        int index;
        int indexMax;
        int indexMin;
}Heap;

int parent(int v);
int leftSon(int v);
int rightSon(int v);
void heapify(Number* tab, Heap *arr, Heap* heapMin, int n, int i);
void heapfiyMin(Number* tab,Heap* arr, Heap* heapMax, int n, int i);
void bulidHeap(Number* tab,Heap *arr, Heap* heapMin, int n);
void bulidHeapMin(Number* tab,Heap *arr, Heap* heapMax, int n);
void heapfiyParentMin(Number* tab, Heap* arr, Heap* heapMax, int n, int i);
void heapfiyParent(Number* tab, Heap* arr, Heap* heapMin, int n, int i);
void removeMax(Number* tab, Heap* arr, Heap* heapMin, int& n, int i);
void removeMin(Number* tab, Heap* arr, Heap* heapMax, int& n, int i);
//void remove(Number* tab, Heap* heapMax, Heap* heapMin, int& posMax, int& posMin, int iMin, int iMax);

int main()
{
        int n = 0, q = 0, k = 0;
        char m;
        int posMin = 0, posMax = 0;
        Number *tab;

        scanf("%d", &n);
        tab = new Number[n + 1];
        for (int i = 1; i <= n; i++)
        {
                scanf_s("%u", &tab[i].x);
        }

        scanf("%d", &q);

        Heap* heapMax = new Heap[n + 1];
        int iMax = 1;
        for (int i = 1; i <= n; i++)
        {
                if (tab[i].x != 1)
                {
                        //heapMax[iMax].x = tab[i].x;
                        heapMax[iMax].index = i;
                        heapMax[iMax].indexMin = iMax;
                        heapMax[iMax].indexMax = iMax;
                        iMax++;
                        posMax++;
                }
        }
        Heap* heapMin = new Heap[n + 1];
        int iMin = 1;
        for (int i = 1; i <= n; i++)
        {
                if (tab[i].x != 1)
                {
                        //heapMin[iMin].x = tab[i].x;
                        heapMin[iMin].index = i;
                        heapMin[iMin].indexMin = iMin;
                        heapMin[iMin].indexMax = iMin;
                        iMin++;
                        posMin++;
                }
        }
        bulidHeap(tab,heapMax, heapMin, posMax);
        bulidHeapMin(tab,heapMin, heapMax, posMin);

        //#######################################################
        int d = 1;
        for (int i = 0; i < q; i++)
        {
                scanf("%d ", &k);
                m = getchar();
                
                for (int j = 0; j < k; j++)
                {
                        if (m == 's' && posMin != 0 && posMax != 0)
                        {
                                 if (tab[heapMin[d].index].x % 2 == 0 )
                                {
                                        //heapMin[d].x = heapMin[d].x / 2;
                                        tab[heapMin[d].index].x = tab[heapMin[d].index].x / 2;
                                        //heapMax[heapMin[d].indexMax].x = heapMin[d].x;// heapMax[heapMin[d].indexMax].x / 2;
                                        if (tab[heapMin[d].index].x == 1)
                                        {
                                                //remove(heapMax, heapMin, posMax, posMin, 1, heapMin[d].indexMax);
                                                removeMax(tab,heapMax, heapMin, posMax, heapMin[d].indexMax);
                                                removeMin(tab, heapMin, heapMax, posMin, 1);
                                        }
                                        else
                                                heapify(tab, heapMax, heapMin, posMax, heapMin[d].indexMax);
                                }
                                else
                                {
                                        unsigned __int64 f = tab[heapMin[d].index].x;
                                        f = f * 3 + 1;
                                        if (f > UINT_MAX)
                                        {
                                                tab[heapMin[d].index].n = 'm';
                                                //remove(heapMax, heapMin, posMax, posMin, 1, heapMin[d].indexMax);
                                                removeMax(tab, heapMax, heapMin, posMax, heapMin[d].indexMax);
                                                removeMin(tab, heapMin, heapMax, posMin, 1);
                                        }
                                        else
                                        {
                                                //heapMin[d].x = heapMin[d].x * 3 + 1;
                                                tab[heapMin[d].index].x = tab[heapMin[d].index].x * 3 + 1;
                                                //heapMax[heapMin[d].indexMax].x = heapMin[d].x;// heapMax[heapMin[d].indexMax].x * 3 + 1;
                                                heapfiyParent(tab, heapMax, heapMin, posMax, heapMin[d].indexMax);
                                                heapfiyMin(tab, heapMin, heapMax, posMin, d);
                                        }
                                }
                        }
                        else if (m == 'l' && posMin != 0 && posMax != 0)
                        {
                                if (tab[heapMax[d].index].x % 2 == 0 )
                                {
                                        //heapMax[d].x = heapMax[d].x / 2;
                                        tab[heapMax[d].index].x = tab[heapMax[d].index].x / 2;
                                        //heapMin[heapMax[d].indexMin].x = heapMax[d].x;//heapMin[heapMax[d].indexMin].x / 2;
                                        if (tab[heapMax[d].index].x == 1)
                                        {
                                                //remove(heapMax, heapMin, posMax, posMin, heapMax[d].indexMin, 1);
                                                removeMin(tab, heapMin, heapMax, posMin, heapMax[d].indexMin);
                                                removeMax(tab, heapMax, heapMin, posMax, 1);
                                        }
                                        else
                                        {
                                                heapfiyParentMin(tab, heapMin, heapMax, posMin, heapMax[d].indexMin);
                                                heapify(tab, heapMax, heapMin, posMax, d);
                                        }
                                }
                                else
                                {
                                        unsigned __int64 f = tab[heapMax[d].index].x;
                                        f = f * 3 + 1;
                                        if (f > UINT_MAX)
                                        {
                                                tab[heapMax[d].index].n = 'm';
                                                //remove(heapMax, heapMin, posMax, posMin, heapMax[d].indexMin, 1);
                                                removeMin(tab, heapMin, heapMax, posMin, heapMax[d].indexMin);
                                                removeMax(tab, heapMax,heapMin,posMax,1);
                                        }
                                        else
                                        {
                                                //heapMax[d].x = heapMax[d].x * 3 + 1;
                                                tab[heapMax[d].index].x = tab[heapMax[d].index].x * 3 + 1;
                                                //heapMin[heapMax[d].indexMin].x = heapMax[d].x;//heapMin[heapMax[d].indexMin].x * 3 + 1;
                                                heapfiyMin(tab, heapMin, heapMax, posMin, heapMax[d].indexMin);
                                        }
                                }
                        }
                }
        }

        for (int i = 1; i <= n; i++)
        {
                if (tab[i].n == 'm')
                {
                        putchar('m');
                        putchar(' ');
                }
                else
                {
                        printf("%u", tab[i].x);
                        putchar(' ');
                }
        }
        return 0;
}

int parent(int v)
{
        return v / 2;
}

int leftSon(int v)
{
        return 2 * v;
}

int rightSon(int v)
{
        return 2 * v + 1;
}

void heapify(Number* tab, Heap* arr, Heap* heapMin, int n, int i)
{
        int largest = i;
        int l = leftSon(i);
        int r = rightSon(i);

        if (l <= n &&  tab[arr[l].index].x >= tab[arr[largest].index].x)
        {
                largest = l;
                if (tab[arr[l].index].x == tab[arr[i].index].x && arr[l].index > arr[i].index)
                        largest = i;
        }
        int a = largest;
        if (r <= n &&  tab[arr[r].index].x >= tab[arr[largest].index].x)
        {
                largest = r;
                if (tab[arr[r].index].x == tab[arr[a].index].x && arr[r].index > arr[a].index)
                        largest = a;
        }
        if (largest != i)
        {
                swap(arr[i].index, arr[largest].index);
                swap(heapMin[arr[i].indexMin].indexMax, heapMin[arr[largest].indexMin].indexMax);
                swap(arr[i].indexMin, arr[largest].indexMin);
                //swap(arr[i].x, arr[largest].x);
                heapify(tab,arr, heapMin, n, largest);
        }
}

void heapfiyMin(Number* tab, Heap* arr, Heap* heapMax, int n, int i)
{
        int largest = i;
        int l = leftSon(i);
        int r = rightSon(i);

        if (l <= n && tab[arr[l].index].x <= tab[arr[largest].index].x)
        {
                largest = l;
                if (tab[arr[l].index].x == tab[arr[i].index].x && arr[l].index > arr[i].index)
                        largest = i;
        }
        int a = largest;
        if (r <= n && tab[arr[r].index].x <= tab[arr[largest].index].x)
        {
                largest = r;
                if (tab[arr[r].index].x == tab[arr[a].index].x && arr[r].index > arr[a].index)
                        largest = a;
        }
        if (largest != i)
        {
                swap(arr[i].index, arr[largest].index);
                swap(heapMax[arr[i].indexMax].indexMin, heapMax[arr[largest].indexMax].indexMin);
                swap(arr[i].indexMax, arr[largest].indexMax);
                //swap(arr[i].x, arr[largest].x);
                heapfiyMin(tab,arr, heapMax, n, largest);
        }
}

void bulidHeap(Number* tab, Heap *arr, Heap* heapMin, int n)
{
        for (int i = n / 2; i >= 1; i--)
                heapify(tab,arr, heapMin, n, i);
}

void bulidHeapMin(Number* tab,Heap *arr, Heap* heapMax, int n)
{
        for (int i = n / 2; i >= 1; i--)
                heapfiyMin(tab,arr, heapMax, n, i);
}

void heapfiyParentMin(Number* tab, Heap* arr, Heap* heapMax, int n, int i)
{
        int p = parent(i);
        int largest = p;
        if (p >= 1 &&  tab[arr[p].index].x >= tab[arr[i].index].x)
        {
                largest = i;
                if (tab[arr[p].index].x == tab[arr[i].index].x && arr[p].index < arr[i].index)
                        largest = p;
        }
        if (largest != p)
        {
                //swap(arr[p].x, arr[largest].x);
                swap(arr[p].index, arr[largest].index);
                swap(heapMax[arr[p].indexMax].indexMin, heapMax[arr[largest].indexMax].indexMin);
                swap(arr[p].indexMax, arr[largest].indexMax);
                heapfiyParentMin(tab,arr, heapMax, n, p);
        }
}

void heapfiyParent(Number* tab, Heap* arr, Heap* heapMin, int n, int i)
{
        int p = parent(i);
        int largest = p;
        if (p >= 1 && tab[arr[p].index].x <= tab[arr[i].index].x)
        {
                largest = i;
                if (tab[arr[p].index].x == tab[arr[i].index].x && arr[p].index < arr[i].index)
                        largest = p;
        }
        if (largest != p)
        {
                //swap(arr[p].x, arr[largest].x);
                swap(arr[p].index, arr[largest].index);
                swap(heapMin[arr[p].indexMin].indexMax, heapMin[arr[largest].indexMin].indexMax);
                swap(arr[p].indexMin, arr[largest].indexMin);
                heapfiyParent(tab,arr, heapMin, n, p);
        }
}

void removeMax(Number* tab, Heap* arr, Heap* heapMin, int& n, int i)
{
        if (i != n)
        {
                //arr[i].x = arr[n].x;
                arr[i].index = arr[n].index;
                arr[i].indexMin = arr[n].indexMin;
                heapMin[arr[n].indexMin].indexMax = i;
        }
        n--;
        heapify(tab, arr, heapMin, n, i);
        heapfiyParent(tab, arr, heapMin, n, i);
        /*if (i != 1 && tab[arr[parent(i)].index].x >= tab[arr[i].index].x)
        {
                heapify(tab, arr, heapMin, n, i);
                heapfiyParent(tab, arr, heapMin, n, i);
        }
        else if(i != 1)
                heapfiyParent(tab, arr, heapMin, n, i);*/
}

void removeMin(Number* tab, Heap* arr, Heap* heapMax, int& n, int i)
{
        if (i != n)
        {
                //arr[i].x = arr[n].x;
                arr[i].index = arr[n].index;
                arr[i].indexMax = arr[n].indexMax;
                heapMax[arr[n].indexMax].indexMin = i;
        }
        n--;
        heapfiyMin(tab, arr, heapMax, n, i);
        heapfiyParentMin(tab, arr, heapMax, n, i);
        /*if (i != 1 && tab[arr[parent(i)].index].x <= tab[arr[i].index].x)
        {
                heapfiyMin(tab, arr, heapMax, n, i);
                heapfiyParentMin(tab, arr, heapMax, n, i);
        }
        else if (i != 1)
                heapfiyParentMin(tab, arr, heapMax, n, i);*/
}
