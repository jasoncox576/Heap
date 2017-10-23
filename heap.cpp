#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
 * 
 */


class HeapTree {
    
public:
    HeapTree(int val) {
        
        data = val;
        
    }
    HeapTree() {

        data = 0;
    }
    int data;
    HeapTree* left;
    HeapTree* right;

    
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

    
HeapTree construct(vector<int>& arr, HeapTree node, int index) {
        cout << "in construct method" << endl;

        if(index < arr.size()) {
            cout << "passed if conditional " << arr[index] << endl;
            HeapTree temp = HeapTree(arr[index]);
            node = temp;
            cout << "Node being set to: " << arr[index] << " at index " << index << endl;
            //for(int x : arr) cout << x << endl;
            HeapTree left = construct(arr, *node.left, index*2 + 1);
            node.left = &left;

            HeapTree right = construct(arr, *node.right, index*2 + 2);
            node.right = &right;
        }
        //node.left = &left;
        //node.right = &right;
        return node;
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
    
    //myvec = getInts();
    myvec = {67, 23, 40, 85, 1, 2, 30, 90, 123};

    std::sort(myvec.begin(), myvec.end());
    std::reverse(myvec.begin(), myvec.end());
    for(int x : myvec) cout << x << " ";
        cout << endl;
    


    
    HeapTree root(10);
    cout << "Root node constructed" << endl;

    root = construct(myvec, root, 0);
    cout << "Heap fully constructed" << endl;


    print_level_order(&root);
    


    return 0;
}

