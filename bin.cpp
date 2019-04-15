#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int x, d;
    Node *c, *s, *p;
};

Node* newNode(int key)
{
    Node *temp = new Node;
    temp->x = key;
    temp->d = 0;
    temp->c = temp->p = temp->s = NULL;
    return temp;
}

Node* binomialLink(Node *b1, Node *b2)
{
    if (b1->x > b2->x)
        swap(b1, b2);
    b2->p = b1;
    b2->s = b1->c;
    b1->c = b2;
    b1->d++;
    return b1;
}

list<Node*> binomialHeapUnion(list<Node*> heap1, list<Node*> heap2)
{
    list<Node*> newHeap;
    list<Node*>::iterator it1 = heap1.begin();
    list<Node*>::iterator it2 = heap2.begin();
    while (it1!=heap1.end() && it2!=heap2.end())
    {
        if((*it1)->d <= (*it2)->d)
        {
            newHeap.push_back(*it1);
            it1++;
        }
        else
        {
            newHeap.push_back(*it2);
            it2++;
        }
    }
    while (it1 != heap1.end())
    {
        newHeap.push_back(*it1);
        it1++;
    }
    while (it2 != heap2.end())
    {
        newHeap.push_back(*it2);
        it2++;
    }
    return newHeap;
}

list<Node*> adjust(list<Node*> heap)
{
    if (heap.size() <= 1)
        return heap;
    list<Node*> newHeap;
    list<Node*>::iterator it1,it2,it3;
    it1 = it2 = it3 = heap.begin();

    if (heap.size() == 2)
    {
        it2 = it1;
        it2++;
        it3 = heap.end();
    }
    else
    {
        it2++;
        it3=it2;
        it3++;
    }
    while (it1 != heap.end())
    {
        if (it2 == heap.end())
            it1++;
        else if ((*it1)->d < (*it2)->d)
        {
            it1++;
            it2++;
            if(it3!=heap.end())
                it3++;
        }
        else if (it3!=heap.end() && (*it1)->d == (*it2)->d && (*it1)->d == (*it3)->d)
        {
            it1++;
            it2++;
            it3++;
        }
        else if ((*it1)->d == (*it2)->d)
        {
            Node *temp;
            *it1 = binomialLink(*it1,*it2);
            it2 = heap.erase(it2);
            if(it3 != heap.end())
                it3++;
        }
    }
    return heap;
}

list<Node*> insertion(list<Node*> heap, Node *tree)
{
    list<Node*> temp;
    temp.push_back(tree);

    temp = binomialHeapUnion(heap,temp);

    return adjust(temp);
}

list<Node*> removeMinFromTree(Node *tree)
{
    list<Node*> heap;
    Node *temp = tree->c;
    Node *l;

    while (temp)
    {
        l = temp;
        temp = temp->s;
        l->s = NULL;
        heap.push_front(l);
    }
    delete(tree);
    return heap;
}

list<Node*> insert(list<Node*> head, int key)
{
    Node *temp = newNode(key);
    return insertion(head,temp);
}

Node* getMin(list<Node*> heap)
{
    list<Node*>::iterator it = heap.begin();
    Node *temp = *it;
    while (it != heap.end())
    {
        if ((*it)->x < temp->x)
            temp = *it;
        it++;
    }
    return temp;
}

list<Node*> extractMin(list<Node*> heap)
{
    list<Node*> newHeap,H;
    Node *temp;

    temp = getMin(heap);
    list<Node*>::iterator it;
    it = heap.begin();
    while (it != heap.end())
    {
        if (*it != temp)
        {
            newHeap.push_back(*it);
        }
        it++;
    }
    H = removeMinFromTree(temp);
    newHeap = binomialHeapUnion(newHeap,H);
    newHeap = adjust(newHeap);
    return newHeap;
}

void printTree(Node *h)
{
    while(h)
    {
        cout<<h->x<<" ";
        printTree(h->c);
        h = h->s;
    }
}

void printHeap(list<Node*> heap)
{
    list<Node*> ::iterator it;
    it = heap.begin();
    while (it != heap.end())
    {
        printTree(*it);
        it++;
    }
}

int main()
{
    int ch,key;
    list<Node*> heap;

    heap = insert(heap,10);
    heap = insert(heap,20);
    heap = insert(heap,25);
    heap = insert(heap,6);
    heap = insert(heap,12);

    cout << "Heap elements after insertion:\n";
    printHeap(heap);
    cout<<"\n";

    Node *temp = getMin(heap);
    cout << "Minimum element of heap "
         << temp->x << "\n";

    heap = extractMin(heap);
    cout << "Heap after deletion of minimum element\n";
    printHeap(heap);

    return 0;
}
