#include <iostream>
#include <cstdlib>
#include <time.h>
//Хаззан Омотола

using namespace std;

class node{
    int key;
    node* left;
    node* right;
    
    public:
    
    node(int k = 0, node*l = 0, node*r = 0){
        key = k, 
        left = l, 
        right = r;
    }
    
    ~node(){
        key = 0;
        left = 0;
        right = 0;
    }
    
    friend class tree;
};

struct elem{
    node* p;
    elem* nx;
};

class tree{
    node* root;
    
    public:
    tree(){
        root = 0;
    }
    tree(int n);
    tree(const tree&);
    node* tree_cpy(node* n);
    node* deln(int k);
    void printt(node*, int);
    void add(int i);
    void del_tree(node* n);
    void inmass(node* p, int* a, int& k);
    void LRN(node* n);
    ~tree();
    tree& operator = (tree&);
    node* search(int);
    node* searchr(node* r, int k);
    bool searchr(int k);
    elem* opu();
    int min();
    int max();
    void LRN(){
        LRN(root);
    }
    node* Root(){
        return root;
    }
};
	
tree::tree(int n){
    node*q = new node(rand()%100 + 1);
    root = q; 
    n--;
    while (n > 0){
        add(rand() %100);
        n--;
    }
}

tree::tree(const tree& a){
    if(a.root == 0) root == 0;
    else{
        root = new node(a.root-> key);
        root-> left = tree_cpy(a.root->left);
        root-> right = tree_cpy(a.root-> right);
    }
}

node* tree::tree_cpy(node* n){
    if(n == 0) return 0;
    node* p = new node(n-> key);
    p-> left = tree_cpy(n-> left);
    p-> right = tree_cpy(n-> right);
    return p;
}

void tree::printt(node* q, int k){
    if(q != 0){
        printt(q-> right, k + 5);
        for(int i = 0; i < k; i++){ cout << " ";}
        cout << q-> key << endl;
        printt(q-> left, k + 5);
    }
}

void tree::add(int i){
    node* j = new node;
    node* r = root;
    while (r != 0){
        j = r;
        if(i < r-> key) r = r-> left;
        else r = r-> right;
    }
    node* m = new node(i);
    if(i < j-> key) j-> left = m;
    else j-> right = m;
}

void tree::del_tree(node* n){
    if(n-> left) del_tree(n->left);
    if(n-> right) del_tree(n->right);
    delete n;
}

elem* tree::opu() {
    elem* curr;
    elem* h;
    elem* t;
    h->p = root;
    h->nx = 0;
    t = h;

    curr = h;
    while (h != 0) {
        
        if (h->p->left != 0) {
            elem* lchild = new elem;
            lchild->p = h->p->left;
            lchild->nx = 0;
            curr->nx = lchild;
            curr = curr->nx;
        }
        if (h->p->right != 0) {
            elem* rchild = new elem;
            rchild->p = h->p->right;
            rchild->nx = 0;
            curr->nx = rchild;
            curr = curr->nx;
        }
        cout<< h->p->key << " ";
        h = h->nx;
        
    }
    cout << endl;
    return t;
}

node* tree::deln(int k){
    node* h = root;
    node* p = NULL;
    node* s;
    node* r;
    node* d;
    
    while (h && h->key != k){
       p = h;
       if(h->key > k){
            h = h->left;
        }
        else{
            h = h->right;
        }
    }

    if(!h){
        cout << "Key Not Found!" << endl;
    }
    ////////
    else if (h->left == 0){
        if (p && p->left == h){
            p->left = h->right;
            delete h;
            return p->left;
        }
        else if (p && p->right == h){
            p->right = h->right;
            delete h;
            return p->right;
        }
        else{
            s = h->right;
            root = s;
            return root;
        }
    }
    else if (h->right == 0){
        if (p && p->left == h){
            p->left = h->left;
            delete h;
            return p->left;
        }
        else if (p && p->right == h){
            p->right = h->left;
            delete h;
            return p->right;
        }
        else{
            s = h->left;
            root = s;
            return root;
        }
        
    }
    s = h->right;
    if (s->left == 0){
        h->key = s->key;
        h->right = s->right;
        delete s;
        return h;
    }
    
    while (s->left != 0){
        r = s;
        s = s->left;
    }
    
    h->key = s->key;
    r->left = s->right;
    delete s;
    return h;
}

/*void tree::inmass(node* p, int* a, int& k){
    if(p==0) return;
    inmass(p->left, a, k);
    a[k++] = p -> key;
    inmass(p-> right, a, k);
}*/

void tree::LRN(node* r){
    if(r->left) LRN(r->left);
    if(r->right) LRN(r->right);
    cout << r->key<< " ";
}

tree::~tree(){
    del_tree(root);
}

node* tree::search(int s){
    node* r = root;
    while(r&&s != r-> key){
        if(s < r-> key) r = r-> left;
        else r = r-> right;
    }
    return r;
}

node* tree::searchr(node* r, int k){
    if(r==0 || r-> key == k) return r;
    node* q;
    if((q=searchr(r->left, k)) != 0) return q;
    return(searchr(r->right, k));
}

bool tree::searchr(int k){
    node* p = searchr(root, k);
    if(p != 0) return true; else return false;
}

int tree::min(){
    node* r = root;
    while(r-> left != 0) r = r-> left;
    return r-> key;
}

int tree::max(){
    node* r = root;
    while(r-> right != 0) r = r-> right;
    return r-> key;
}

tree& tree::operator = (tree& n){
    if (n.root == root) return *this;
    //if (*this == n) return *this;
    if (n.root == 0) root = 0;
    else{
        del_tree(root);
        root = new node(n.root-> key);
        root-> left = tree_cpy(n.root-> left);
        root-> right = tree_cpy(n.root-> right);
    }
    return *this;
}


int main(void){
    srand(time(0));
    int min, max, sizea, sizeb, i, j, k, d;
    
    cout << "Enter Size Of Tree A: " << endl;
    cin >> sizea;
    
    tree a(sizea);
    cout << "Tree A: " << endl;
    a.printt(a.Root(), 0);
    min = a.min();
    max = a.max();
    cout << "Minimum Element in tree A: " << min << endl;
    cout << "Maximum Element in tree A: " << max << endl;
    cout << " ------------------------------------------------------- " <<endl;
    /*cout << "Enter Size Of Tree B: " << endl;
    cin >> sizeb;
    tree b(sizeb);
    cout << "Tree B: " << endl;
    b.printt(b.Root(), 0);*/
    cout << "Enter Element To Be Added To The Tree: " << endl;
    cin >> j;
    a.add(j);
    cout << "Tree A After Adding Element: " << j << endl;
    a.printt(a.Root(), 0);
    
    cout << "Enter Element To Be Searched For: " << endl;
    cin >> i;
    if (a.search(i) != 0){
        cout << "Element " << i << " Found!" << endl;
    }
    else cout << "Element " << i << " Not Found!"<< endl;
    cout << " " << endl;
    cout << " ------------------------------------------------------- " <<endl;
    tree c(a);
    a = c;
    c.printt(c.Root(), 0);
    cout << " " << endl;
    
    /*min = b.min();
    max = b.max();
    cout << "Min Element in tree B: " << min << endl;
    cout << "Max Element in tree B: " << max << endl;*/
    
    cout << " " << endl;
    cout << "LRN Tree A: " << endl;
    a.LRN();
    cout << " " << endl;
    cout << " ------------------------------------------------------- " <<endl;
    cout << " ------------------------------------------------------- " <<endl;
    
    cout << "Enter Element To Delete: " << endl;
    cin >> d;
    cout << "Tree Before Deleting " << d << endl;
    c.printt(c.Root(), 0);
    c.deln(d);
    cout << "Tree After Deleting " << d << endl;
    c.printt(c.Root(), 0);
    
    cout << " ------------------------------------------------------- " <<endl;
    /*tree x(10);
    x.printt(x.Root(), 0);
    cout << "Enter Search Key" << endl;
    cin >> k;
    if(x.searchr(k)) cout << k << " Exists In The Tree.";
    else cout << k << " Does Not Exist In The Tree." << endl;*/
    
    elem* y;
    y = c.opu();
    
    return 0;
}


