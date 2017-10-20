
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


void print_level_order(HeapTree* node) {
	if(!node) return;
	queue<HeapTree*> nodesQueue;

	int current_level = 1;
	int next_level = 0;

	nodesQueue.push(node);

	while(!nodesQueue.empty()) {
		HeapTree *currnode = nodesQueue.front();
		nodesQueue.pop();

		current_level--;
		if(currnode) {
			cout << currnode->data << " ";
		}
		if(current_level == 0) cout << endl;

		if(currnode->left) {

			nodesQueue.push(currnode->left);
			next_level++;
		}

		if(currnode->right) {

			nodesQueue.push(currnode->right);
			next_level++;
		}

		if(current_level == 0) swap(current_level, next_level);
	} 

}





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


