#include <iostream>
#include <queue>
using namespace std;
#define MAXN 100000
#define INF 0x3fffffff
struct treap_node{
    int ls,rs;
    int val;
    int cnt,siz,lev;
};
treap_node pool[MAXN+5];
int treap_tail;
const int nul=0;
queue<int> treap_rubbish;
int new_treap_node(){
    int res=0;
    if(treap_rubbish.empty()){
        res=++treap_tail;
    }else{
        res=treap_rubbish.front();
        treap_rubbish.pop();
    }
    pool[res].cnt=pool[res].siz=pool[res].ls=pool[res].rs=0;
    pool[res].val=0;
    pool[res].lev=rand();
    return res;
}
void delete_treap_node(int &p){
    treap_rubbish.push(p);
    p=0;
}
struct treap{
    int root;
    treap(){
        root=nul;
    }
    void zig(int &p) {  // 左旋
        int tmp=pool[p].ls;
        pool[p].ls=pool[tmp].rs;
        pool[tmp].rs=p;
        push_up(p);push_up(tmp);
        p=tmp;
    }
    void zag(int &p) {  // 右旋
        int tmp=pool[p].rs;
        pool[p].rs=pool[tmp].ls;
        pool[tmp].ls=p;
        push_up(p);push_up(tmp);
        p=tmp;
    }
    void push_up(int p){
        pool[p].siz=pool[pool[p].ls].siz+pool[pool[p].rs].siz+pool[p].cnt;
    }
    void insert(int &p,int x){
        if(p==nul){
            p=new_treap_node();
            pool[p].val=x;
            pool[p].siz=pool[p].cnt=1;
        }else if(x==pool[p].val){
            pool[p].cnt++;
            push_up(p);
        }else if(x<pool[p].val){
            insert(pool[p].ls,x);
            push_up(p);
            if(pool[pool[p].ls].lev>pool[p].lev)zig(p);
        }else{//x>pool[p].val
            insert(pool[p].rs,x);
            push_up(p);
            if(pool[pool[p].rs].lev>pool[p].lev)zag(p);
        }
    }
    void erase(int &p,int x){
        if(p==nul){
        }else if(x==pool[p].val){
            if(pool[p].cnt>1){
                pool[p].cnt--;push_up(p);
            }else{
                pool[p].cnt=0;
                if(!(pool[p].ls||pool[p].rs)){
                    delete_treap_node(p);
                }else{
                    if(pool[p].rs==0||
                    (pool[p].ls&&pool[pool[p].ls].lev>pool[pool[p].rs].lev)){
                        zig(p);
                        erase(pool[p].rs,x);
                    }else{
                        zag(p);
                        erase(pool[p].ls,x);
                    }
                }
            }
        }else if(x<pool[p].val){
            erase(pool[p].ls,x);
            push_up(p);
            if(pool[p].ls&&pool[pool[p].ls].lev>pool[p].lev)zig(p);
        }else{//x>pool[p].val
            erase(pool[p].rs,x);
            push_up(p);
            if(pool[p].rs&&pool[pool[p].rs].lev>pool[p].lev)zag(p);
        }
    }
    int rank(int p,int x){
        if(p==nul){
            return 1;
        }else if(x==pool[p].val){
            return pool[pool[p].ls].siz+1;
        }else if(x<pool[p].val){
            return rank(pool[p].ls,x);
        }else{
            return pool[pool[p].ls].siz+pool[p].cnt+rank(pool[p].rs,x);
        }
    }
    int kth(int p,int x){
        if(p==nul){
            return INF;
        }else if(pool[pool[p].ls].siz>=x){
            return kth(pool[p].ls,x);
        }else if(pool[pool[p].ls].siz+pool[p].cnt>=x){
            return pool[p].val;
        }else{
            return kth(pool[p].rs,x-pool[pool[p].ls].siz-pool[p].cnt);
        }
    }
    int count(int p,int x){
        if(p==nul){
            return 0;
        }else if(x==pool[p].val){
            return pool[p].cnt;
        }else if(x<pool[p].val){
            return count(pool[p].ls,x);
        }else{
            return count(pool[p].rs,x);
        }
    }
};
int main(){
    srand(19260817);
    treap a;
    int n;cin>>n;
    while(n--){
        int op,x;cin>>op>>x;
        if(op==1){
            a.insert(a.root,x);
        }else if(op==2){
            a.erase(a.root,x);
        }else if(op==3){
            cout<<a.rank(a.root,x)<<endl;
        }else if(op==4){
            cout<<a.kth(a.root,x)<<endl;
        }else if(op==5){
            cout<<a.kth(a.root,a.rank(a.root,x)-1)<<endl;
        }else if(op==6){
            cout<<a.kth(a.root,a.rank(a.root,x)+a.count(a.root,x))<<endl;
        }
    }
    return 0;
}