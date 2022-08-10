//
// Created by Sevent on 2022/8/9.
//

#ifndef ALGORITHM_SEGMENTTREE_H
#define ALGORITHM_SEGMENTTREE_H
#include <iostream>
struct Node
{
    int sum = 0;
    int lazy = 0, change = 0;
    bool update = false;
};

class SegmentTree
{
private:
    int m_size = 0;
    int* array = nullptr;
    Node* node = nullptr;

    void PushUp(const int& index)
    {
        node[index].sum = node[index<<1].sum + node[index<<1|1].sum;
    }

    void PushDown(int ln, int rn, int index)
    {
        if (node[index].update)
        {
            node[index<<1].update = true;
            node[index<<1].sum = node[index].change * ln;
            node[index<<1].change = node[index].change;
            node[index<<1].lazy = 0;


            node[index<<1|1].update = true;
            node[index<<1|1].sum = node[index].change * rn;
            node[index<<1|1].change = node[index].change;
            node[index<<1|1].lazy = 0;

            node[index].update = false;
        }
        if(node[index].lazy!=0)
        {
            node[index<<1].lazy += node[index].lazy;
            node[index<<1].sum += node[index].lazy * ln;

            node[index<<1|1].lazy += node[index].lazy;
            node[index<<1|1].sum += node[index].lazy * rn;

            node[index].lazy = 0;

        }
    }

    void Build(int l, int r, int index)
    {
        if (l == r)
        {
            node[index].sum = array[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(l, mid, index<<1);
        Build(mid + 1, r, index<<1|1);
        PushUp(index);
    }

    void Add(int L, int R, int increment, int l, int r, int index)
    {
        if (L <= l && R >= r)
        {
            node[index].sum += increment * (r - l + 1);
            node[index].lazy += increment;
            return;
        }

        int mid = (l + r) >> 1;
        PushDown(mid-l+1, r - mid, index );

        if (L <= mid )
            Add(L,R,increment,l, mid, index<<1);
        if (R>mid)
            Add(L,R,increment,mid+1, r, index<<1|1);

        PushUp(index);
    }

    void Update(int L, int R, int C ,int l, int r, int index)
    {
        if(L<=l && R>=r)
        {
            node[index].update = true;
            node[index].sum = C *(r - l + 1);
            node[index].change = C;
            node[index].lazy = 0;
            return;
        }

        int mid = (l+r) >>1;
        PushDown(mid - l +1 , r - mid, index);

        if (L <=mid )
            Update(L, R, C, l, mid, index<<1);

        if (R >= mid + 1)
            Update(L, R, C, mid+1, r, index<<1|1);

        PushUp(index);

    }

    long GetSum(int L, int R, int l, int r, int index)
    {
        if (L<=l && R>=r)
            return node[index].sum;

        int mid = (l + r) >>1;
        PushDown(mid-l+1, r - mid, index);

        long ans = 0;
        if (L <= mid)
            ans += GetSum(L, R, l, mid, index<<1);
        if (R > mid)
            ans += GetSum(L, R, mid+1, r, index<<1|1);

        return ans;

    }

public:
    SegmentTree(const int* arr, int size):m_size(size +1)
    {
        node = new Node[m_size<<1];
        array = new int[m_size];
        for (int i = 1; i < m_size; ++i) {
            array[i] = arr[i - 1];
        }
    }

    void build()
    {
        Build(1, m_size, 1 );
    }

    void add(int l, int r, int increment)
    {
        Add(l, r, increment, 1, m_size, 1 );
    }

    void update(int l, int r, int C)
    {
        Update(l, r, C, 1, m_size, 1);
    }

    long getSum(int l, int r)
    {
        return GetSum(l,r,1,m_size,1);
    }



};
#endif //ALGORITHM_SEGMENTTREE_H
