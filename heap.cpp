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

    int size;

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

inline int getSize() { return size; }
inline int setSize(int s) {size = s;}

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
		max_heapify(root->left);
	}
	if(root->right) {
		max_heapify(root->right);
	}

	int leftdata = 0;
	int rightdata = 0;
	if(root->left) {

		leftdata = root->left->data;
	}
	if(root->right) {

		rightdata = root->right->data;
	}

	int greaterdata = max(leftdata, rightdata);

	if(greaterdata > root->data && greaterdata > 0) {

		if(leftdata > rightdata) {
			root->left->data = root->data;
			root->data = greaterdata;
			max_heapify(root->left);
		}
		if(rightdata > leftdata) {
			root->right->data = root->data;
			root->data = greaterdata;
			max_heapify(root->right);
		}




	}

}

















void deleteMax(HeapTree* root) {

	HeapTree* replacerNode = searchN(root, 0, root->getSize());
	int replacerData = replacerNode->data;
	root->data = replacerData;

	HeapTree* replacerptr;
	*replacerNode = *replacerptr;
	replacerNode->data = NULL;
	replacerNode->left = NULL;
	replacerNode->right = NULL;

	root->setSize(root->getSize()-1);

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
	    node->setSize(arr.size());
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

void deleteNode(HeapTree* root, int n) {

    HeapTree* dnode = searchN(root, 0, n);
    HeapTree* last = searchN(root, 0, root->getSize());

    swap(dnode->data, last->data);

    HeapTree* replacePtr;
    *dnode = *replacePtr;
    dnode->data = NULL;
    dnode->left = NULL;
    dnode->right = NULL;

    root->setSize(root->getSize()-1);

    max_heapify(root);

}


void getPriorityQueue(HeapTree* root, deque<pair<HeapTree*, int>>& order, int level=0) {

	
    if(root->left && root->right) {
    	getPriorityQueue(root->right, order, level+1);
	getPriorityQueue(root->left, order, level+1);
    }
    else {
	if(!order.empty()) {
	    int backlevel = order.back().second;
	    if(level <= backlevel) {
	        order.push_front(pair<HeapTree*, int>(root, level));
	    
	    }
	
	}
	else {
            order.push_front(pair<HeapTree*, int>(root, level));
	}
    }



}

void insertNode(HeapTree* root, int data, deque<HeapTree*>& dbucket) {

    deque<pair<HeapTree*, int>> order;
    getPriorityQueue(root, order);

    HeapTree* topNode = order.front().first;
    order.pop_front();

    if(!topNode->left) {
	topNode->left = new HeapTree(data);
	dbucket.push_front(topNode->left);
    }
    else {
	if (!topNode->right) {
            topNode->right = new HeapTree(data);
	    dbucket.push_front(topNode->right);
	}
    }
    max_heapify(root);

}






int main(int argc, char** argv) {

    vector<int> myvec;
    int heap_size = -1;

   //myvec = {100, 43, 45, 23, 54, 2, 1, 3, 5, 80, 98, 45};

    myvec = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
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
    cout << "Heap max-heapified" << endl;

    deleteMax(&root);
    cout << endl;
    cout << endl;

    print_level_order(&root);
    cout << "root node deleted" << endl;


    
    deleteNode(&root, 5);
    cout << endl;
    cout << endl;

    print_level_order(&root);
    cout << "Element at index 5 deleted" << endl;

    for(int i = 0; i < 8; ++i) {
	
   	insertNode(&root, (i+100)*2, dbucket); 
	cout << endl;
	cout << endl;
	print_level_order(&root);
	
    }
    cout << endl;
    cout << endl;

    print_level_order(&root);
    cout << "Element added with key of 5000" << endl;

    deleteHeap(dbucket);




    return 0;
}

