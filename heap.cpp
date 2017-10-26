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


HeapTree* construct(vector<int>& arr, HeapTree* node, int index) {
        cout << "in construct method" << endl;

        if(index < arr.size()) {
            cout << "passed if conditional " << arr[index] << endl;
            HeapTree* temp = new HeapTree(arr[index]);
            node = temp;
            node->left = new HeapTree();
            node->left = construct(arr, node->left, index*2 + 1);
            if(node->left) cout << "printing left: " << node->left->data << endl;

            node->right = new HeapTree();
            node->right = construct(arr, node->right, index*2 + 2);

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
   //vec = {67, 23, 40, 85, 1, 2, 30, 90, 123};
   //yvec = {100, 43, 45, 23, 54, 2, 1, 3, 5, 80, 98, 45};
    for(int i = 1;i < 100; ++i) {
    	myvec.push_back(i);
    }

    std::sort(myvec.begin(), myvec.end());
    std::reverse(myvec.begin(), myvec.end());
    for(int x : myvec) cout << x << " ";
        cout << endl;



    HeapTree root(10);
    cout << root.data << endl;
    cout << "Root node constructed" << endl;


    root = *construct(myvec, &root, 0);
    cout << "Heap fully constructed" << endl;


    print_level_order(&root);



    return 0;
}
