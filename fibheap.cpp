#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int x;
    int d;
    Node* p;
    Node* c;
    Node* l;
    Node* r;
    char m;
    char v;
};

Node* createNode(int value)
{
    Node* x = new Node;
    x->x = value;
    return x;
}

int display(Node* H)
{

    Node* p = H;
    if (p == NULL)
    {
        cout<<"empty"<<endl;
        return 0;
    }

    cout<<"root list: "<<endl;
    do
    {
        cout<<p->x;
        p = p->r;
        if (p != H)
        {
            cout<<"-->";
        }
    }while (p != H && p->r != NULL);

    cout<<endl;
}

Node* insert(Node* H, Node* x, int* nH)
{
    x->d = 0;
    x->p = NULL;
    x->c = NULL;
    x->l = x;
    x->r = x;
    x->m = 'F';
    x->v = 'N';

    if (H != NULL)
    {
        (H->l)->r = x;
        x->r = H;
        x->l = H->l;
        H->l = x;
        if (x->x < H->x)
            H = x;
    }
    else
    {
        H = x;
    }

    *nH = *nH + 1;
    return H;
}


int fibonacciLink(Node* H, Node* y, Node* x)
{
    (y->l)->r = y->r;
    (y->r)->l = y->l;

    if (x->r == x)
        H = x;

    y->l = y;
    y->r = y;
    y->p = x;

    if (x->c == NULL)
        x->c = y;

    y->r = x->c;
    y->l = (x->c)->l;
    ((x->c)->l)->r = y;
    (x->c)->l = y;

    x->d++;

}

Node* find(Node* H, int k)
{
    Node* x = H;
    x->v = 'Y';
    Node* p = NULL;
    if (x->x == k)
    {
        p = x;
        x->v = 'N';
        return p;
    }

    if (p == NULL)
    {
        if (x->c != NULL )
            p = find(x->c, k);
        if ((x->r)->v != 'Y' )
            p = find(x->r, k);
    }

    x->v = 'N';
    return p;

}

int cut(Node* H, Node* x, Node* y)
{
    if (x == x->r)
        y->c = NULL;

    (x->l)->r = x->r;
    (x->r)->l = x->l;

    if (x == y->c) 
        y->c = x->r;

    y->d = y->d - 1;
    x->r = x;
    x->l = x;

    (H->l)->r = x;
    x->r = H;
    x->l = H->l;
    H->l = x;


    x->p = NULL;
    x->m = 'F';

}

int cascadingCut(Node* H, Node* y)
{
    Node* z = y->p;
    if (z != NULL)
    {
        if (y->m == 'F')
        {
            y->m = 'T';
        }
        else
        {
            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}

void consolidate(Node* H,int* nH)
{
    int d, i;
    float f = (log(*nH)) / (log(2));
    int D = f;
    cout<<"in consolidate nh="<<*nH<<endl<<endl;
    cout<<"in consolidate D="<<D<<endl<<endl;

    display(H);
    Node* A[D+1];
    for (i = 0; i <= D; i++)
        A[i] = NULL;

    Node* x = H;
    Node* y;
    Node* temp;

    do
    {
        d = x->d;
        while(A[d] != NULL)
        {
            y = A[d];
            if (x->x > y->x)
            {
                temp = x;
                x = y;
                y = temp;
            }
            if (y == H)
                H = x;

            fibonacciLink(H, y, x);

            if (x->r == x)
                H = x;

            A[d] = NULL;
            d = d + 1;
        }
        A[d] = x;
        x = x->r;
    }while (x != H);

    H = NULL;
    for (int j = 0; j <= D; j++)
    {
        if (A[j] != NULL)
        {
            A[j]->l = A[j];
            A[j]->r =A[j];
            if (H == NULL)
            {
                H = A[j];
            }
            else
            {
                (H->l)->r = A[j];
                A[j]->r = H;
                A[j]->l = H->l;
                H->l = A[j];
                if (A[j]->x < H->x)
                    H = A[j];
            }
        }
    }
    display(H);
}

Node* unite(Node* H1, Node* H2, int* nH1, int* nH2, int* nH)
{

    Node* np;
    Node* H = NULL;

    H = H1;
    (H->l)->r = H2;
    (H2->l)->r = H;

    np = H->l;
    H->l = H2->l;
    H2->l = np;

    *nH = *nH1 + *nH2;

    return H;

}

Node* extractMin(Node* H, int* nH)
{
    Node* p;
    Node* ptr;
    Node* z = H;
    p = z;
    ptr = z;

    if (z == NULL)
        return z;

    Node* x;
    Node* np;

    x = NULL;
    if (z->c != NULL)
        x = z->c;

    if (x != NULL)
    {
        ptr = x;
        do
        {
            np = x->r;
            (H->l)->r = x;
            x->r = H;
            x->l = H->l;
            H->l = x;

            if (x->x < H->x)
                H = x;

            x->p = NULL;
            x = np;
        }while (np != ptr);
    }

    (z->l)->r = z->r;
    (z->r)->l = z->l;

    if (z == z->r && z->c == NULL)
        H = NULL;
    else
    {
        H = z->r;
        cout<<"intermediate root list: \n\n";
    display(H);
        consolidate(H, nH);
    }

    *nH = *nH - 1;
    display(H);
    return p;
}

int decreaseKey(Node* H, int x, int k)
{
    Node* y;

    if(x < k)
    {
        cout<<"Entered key greater than current key"<<endl;
        return 0;
    }
    if (H == NULL)
    {
        cout<<"The Heap is Empty"<<endl;
        return 0;
    }

    Node* ptr = find(H, x);
    if (ptr == NULL)
    {
        cout<<"Node not found in the Heap"<<endl;
        return 1;
    }

    ptr->x = k;
    y = ptr->p;
    if (y != NULL && ptr->x < y->x)
    {
        cut(H, ptr, y);
        cascadingCut(H, y);
    }

    if (ptr->x < H->x)
        H = ptr;

    return 0;
}

int deleteKey(Node* H, int k, int* nH)
{
    Node* np = NULL;
    int returnVal;
    returnVal = decreaseKey(H, k, INT_MIN);
    if (!returnVal)
        np = extractMin(H, nH);
    if (np != NULL)
        cout<<"Key Deleted"<<endl;
    else
        cout<<"Key not Deleted"<<endl;
    return 0;
}

int main()
{
    int n, m, choice,l;
    Node* p;
    Node* H = NULL;
    int nH=0;

    p = createNode(10);
    H = insert(H, p, &nH);
    p = createNode(20);
    H = insert(H, p, &nH);
    p = createNode(25);
    H = insert(H, p, &nH);
    p = createNode(6);
    H = insert(H, p, &nH);
    p = createNode(17);
    H = insert(H, p, &nH);
    p = createNode(12);
    H = insert(H, p, &nH);

    cout << "Heap elements after insertion:\n";
    display(H);

    p = extractMin(H, &nH);
    if (p != NULL)
        cout<<"The node with minimum key: "<<p->x<<endl;
    else
        cout<<"Heap is empty"<<endl;

    decreaseKey(H, 27, 2);

    deleteKey(H, 2, &nH);

    return 0;
}