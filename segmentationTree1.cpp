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

int query(vector<int> &tree, int lt, int ht, int l, int h, int index)
{
    if (l > ht || h < lt)
        return 0;
    if (l <= lt && h >= ht)
        return tree[index];
    int mid = (lt + ht) / 2;
    return query(tree, lt, mid, l, h, 2 * index + 1) + query(tree, mid + 1, ht, l, h, 2 * index + 2);
}

// point update
void update(vector<int>& tree,int l,int h,int i,int x,int index){
    // out of range
    if(l>h) return;
    if(l==h){
        tree[index]=x;
        return;
    }
    int mid=(l+h)/2;
    if(i<=mid){
        update(tree,l,mid,i,x,2*index+1);
    }else{
        update(tree,mid+1,h,i,x,2*index+2);
    }
    // update on return 
    tree[index]=tree[2*index+1]+tree[2*index+2];
}


int main()
{
    int arr[] = {11, 22, 110, 13, 21, 20, 41, 5, 4, 12};
    int n = 10;

    vector<int> tree(4 * n, 0);
    build(tree, 0, n - 1, 0, arr);

    // for (int i = 0; i < 4*n; i++){
    //     cout<<i<<":"<<tree[i]<<"  ,  ";
    // }
    // cout<<"\n";

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
            int ans = query(tree, 0, n - 1, l, r, 0);
            cout << "sum of range " << l << " to " << r << " is " << ans << "\n";
        }else{
            // 2 is for update and then sum
            int index,x;
            cin>> index>>x;
            update(tree,0,n-1,index,x,0);
              
        }
    }
    return 0;
}
