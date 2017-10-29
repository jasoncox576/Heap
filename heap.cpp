#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
#include <stack>

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




};


HeapTree* searchN(HeapTree* root, int start, int end) {
	if(start == end) return root;
	if(start != end) {
		if(root->left) {
			HeapTree* leftreturn = searchN(root->left, start*2+1, end);
			if(leftreturn->data) {
				root = leftreturn;
				return root;
			}
		}

		if(root->right) {
			HeapTree* rightreturn = searchN(root->right, start*2+2, end);
			if(rightreturn->data) {
				root = rightreturn;
				return root;
			}
		}
	}


		return new HeapTree;


}




void max_heapify(HeapTree* root) {

	if(root->left) {

		if(root->left->data > root->data) {
			int leftdata = root->left->data;
			int rootdata = root->data;
			root->left->data = rootdata;
			root->data = leftdata;
		}
		max_heapify(root->left);
	}

	if(root->right) {

		if(root->right->data > root->data) {
			int rightdata = root->right->data;
			int rootdata = root->data;
			root->right->data = rootdata;
			root->data = rightdata;

		}
		max_heapify(root->right);
	}

}

















void deleteMax(HeapTree* root, int heapSize) {

	HeapTree* replacerNode = searchN(root, 0, heapSize);
	int replacerData = replacerNode->data;
	root->data = replacerData;

	HeapTree* replacerptr;
	*replacerNode = *replacerptr;
	replacerNode->left = NULL;
	replacerNode->right = NULL;

	max_heapify(root);


}










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
		if(currnode->data) {
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


HeapTree* construct(vector<int>& arr, HeapTree* node, int index, deque<HeapTree*>& dbucket) {

        if(index < arr.size()) {

            HeapTree* temp = new HeapTree(arr[index]);
            node = temp;
            dbucket.push_front(node);
            node->left = construct(arr, node->left, index*2 + 1, dbucket);

            node->right = construct(arr, node->right, index*2 + 2, dbucket);

        }
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

void deleteHeap(deque<HeapTree*> tree) {

    // deleting all of the nodes in tree (getting rid of the heap)
    for(HeapTree* ptr : tree) {
    	delete ptr;
    }

}







int main(int argc, char** argv) {

    vector<int> myvec;
    int heap_size = -1;

   //myvec = {100, 43, 45, 23, 54, 2, 1, 3, 5, 80, 98, 45};

    myvec = {12, 4243, 34, 12, 60, 43, 5, 34, 6, 3, 5, 7, 8, 23, 21, 23, 4, 44, 55, 66, 45, 20, 23, 45, 69, 39, 46, 13};
    heap_size = myvec.size() - 1;

    //std::sort(myvec.begin(), myvec.end());
    //std::reverse(myvec.begin(), myvec.end());
    for(int x : myvec) cout << x << " ";
        cout << endl;



    HeapTree root(10);


    deque<HeapTree*> dbucket;

    root = *construct(myvec, &root, 0, dbucket);
    cout << "Heap fully constructed" << endl;

    max_heapify(&root);


    print_level_order(&root);

    deleteMax(&root, heap_size);
    cout << endl;
    cout << endl;

    print_level_order(&root);
    cout << "root node deleted" << endl;


    cout << "deleted" << endl;
    cout << "It worked!" << endl;


    deleteHeap(dbucket);




    return 0;
}
