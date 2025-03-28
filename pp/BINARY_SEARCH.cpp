#include<iostream>

using namespace std;

void Heapify(int arr[] , int n , int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    int max = i;

    if(l < n && arr[l] > arr[max]) max = l;
    if(r < n && arr[r] > arr[max]) max = r;

    if(max != i)
    {
        swap(arr[i] , arr[max]);
        Heapify(arr , n , max);
    }

}

void BuildHeap(int arr[] ,int n)
{
    for(int i = n / 2 - 1;i >= 0;i--)
        Heapify(arr , n , i);
}

void Heap_Sort(int arr[] ,int n)
{
    BuildHeap(arr , n);
    for(int i = n - 1;i > 0;i--)
    {
        swap(arr[0] , arr[i]);
        Heapify(arr , i , 0);
    }
}

bool Binary_Search(int arr[] ,int l ,int h ,int key)
{
    if(h >= l)
    {
        int m = (l + h) / 2;

        if(arr[m] == key)
            return true;
        else if (key  > arr[m])
            return Binary_Search(arr , m+1 , h , key);
        else if (key < arr[m])
            return Binary_Search(arr , l , m-1 , key);
    }
    return false;
}

int Binary_Search1(int arr[], int l, int h, int key) 
{
    while (l <= h) 
    {
        int m = (l + h) / 2;
        if (arr[m] == key) return m;
        else if (key > arr[m])  l = m + 1;
        else  h = m - 1;
    }
    
    return -1;
}

void print(int arr[] , int n)
{
    for(int i = 0;i < n;i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int arr[] = {18 , 22 , 80 , 60 , 31 , 70 , 1 , 6 , 10 , 55 , 15 , 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    Heap_Sort(arr , n);
    if(Binary_Search(arr , 0 , n-1 , 110))
        cout << "Found" << endl;
    else
        cout << "Not Found" << endl;
    // print(arr , n);
    return 0;
}