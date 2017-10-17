
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 
 */


class HeapTree {
    
public:
    HeapTree(int val) {
        
        data = val;
        
    }
    int data;
    HeapTree* left;
    HeapTree* right;
    
    int construct(vector<int> arr, int index) {
        this->data = arr[index];
        this->left->data = construct(arr, index*2 + 1);
        this->right->data = construct(arr, index*2 + 2);
        return arr[index];
    }
    
    void print() {
        
    }
    
};





vector<int> getInts() {
    
    vector<int> retvec;
    int i;
    while(cin >> i) {
        if(i == -0) break;
        retvec.push_back(i);
        
    }
    return retvec;
    
    
    
    
}

int main(int argc, char** argv) {

    vector<int> myvec;
    
    myvec = getInts();
    
    std::sort(myvec.begin(), myvec.end());
    


    
    HeapTree root(myvec[0]);
    root
    
    
    return 0;
}


