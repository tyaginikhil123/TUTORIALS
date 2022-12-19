#include <bits/stdc++.h>
using namespace std;

int build(vector<int> &tree, int l, int h, int index, int arr[])
{
    if (l > h)
    {
        return 0;
    }
    if (l == h)
    {
        return tree[index] = arr[l];
    }
    int mid = (l + h) / 2;
    return tree[index] = build(tree, l, mid, 2 * index + 1, arr) + build(tree, mid + 1, h, 2 * index + 2, arr);
}

int query(vector<int>& tree,vector<int>& lazyTree, int lt, int ht, int l, int h, int index)
{
    if (l > ht || h < lt)
        return 0;

    if(lazyTree[index] !=0){
        tree[index]+=lazyTree[index]*(ht-lt+1);
        //left child update
        lazyTree[2*index+1]+=lazyTree[index];
        // right child update
        lazyTree[2*index+2]+=lazyTree[index];
        lazyTree[index]=0;
    }

    if (l <= lt && h >= ht)
        return tree[index];
    int mid = (lt + ht) / 2;
    return query(tree,lazyTree,lt, mid, l, h, 2 * index + 1) + query(tree,lazyTree,mid + 1, ht, l, h, 2 * index + 2);
}

// range update
void update(vector<int>& tree,vector<int>& lazyTree, int lt, int ht, int l, int h,int index,int x){
    if (l > ht || h < lt || lt>ht){
        return;
    }
    if(lazyTree[index] !=0){
        tree[index]+=lazyTree[index]*(ht-lt+1);
        //left child update
        lazyTree[2*index+1]+=lazyTree[index];
        // right child update
        lazyTree[2*index+2]+=lazyTree[index];
        lazyTree[index]=0;
    }
    if (l <= lt && h >= ht){
        tree[index]+=x*(ht-lt+1);
        lazyTree[2*index+1]+=x;
        lazyTree[2*index+2]+=x;
    }else{
        int mid=(lt+ht)/2;
        update(tree,lazyTree,lt,mid,l,h,x,2*index+1);
        update(tree,lazyTree,mid+1,ht,l,h,x,2*index+2);
        tree[index]=tree[2*index+1]+tree[2*index+2];
    }
}


int main()
{
    int arr[] = {11, 22, 110, 13, 21, 20, 41, 5, 4, 12};
    int n = 10;
    // tree
    vector<int> tree(4 * n, 0);
    // lazy tree 
    vector<int> lazyTree(4*n,0);
    build(tree, 0, n - 1, 0, arr);

    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin>>type;
        if(type==1){
            // 1 is for finding sum only
            int l,r;
            cin >> l >> r;
            int ans = query(tree,lazyTree, 0, n - 1, l, r, 0);
            cout << "sum of range " << l << " to " << r << " is " << ans << "\n";
        }else{
            // 2 is for range  update and then sum
            int l,r,x;
            cin>>l>>r>>x;
            update(tree,lazyTree,0,n-1,l,r,x,0);
              
        }
    }
    return 0;
}