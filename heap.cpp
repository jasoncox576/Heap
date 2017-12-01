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


    HeapTree* left = NULL;
    HeapTree* right = NULL;

    inline int getSize() { return size; }
    inline int setSize(int s) {size = s;}

    ~HeapTree() {

		if(left) delete left;
		if(right) delete right;


    }


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

HeapTree* extractMax(HeapTree* root) {

	HeapTree* max = new HeapTree(root->data);
	deleteMax(root);


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




HeapTree* construct(vector<int>& arr, HeapTree* node, int index=0) {
        if(index < arr.size()) {
            HeapTree* temp = new HeapTree(arr[index]);
            node = temp;
            node->setSize(arr.size()-1);
            node->left = construct(arr, node->left, index*2 + 1);

            node->right = construct(arr, node->right, index*2 + 2);

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


bool isNotNull(HeapTree* node) {


	if(node) {
		if(node->data)
			return true;
	}
	return false;
}





void deleteNode(HeapTree* root, int n) {

    HeapTree* dnode = searchN(root, 0, n);
    HeapTree* last = searchN(root, 0, root->getSize());

    swap(dnode->data, last->data);

    HeapTree* replacePtr;
    *last = *replacePtr;
    last->data = NULL;
    last->left = NULL;
    last->right = NULL;

    root->setSize(root->getSize()-1);

    max_heapify(root);

}


void getPriorityQueue(HeapTree* root, deque<pair<HeapTree*, int>>& order, int level=0) {

	HeapTree* null;
    if(isNotNull(root->left) && isNotNull(root->right)) {
    	getPriorityQueue(root->right, order, level+1);
    	getPriorityQueue(root->left, order, level+1);
    }
    else if(!order.empty()) {
	    int backlevel = order.back().second;
	    if(level <= backlevel) {
	        order.push_front(pair<HeapTree*, int>(root, level));

	    }

	}
	else {
            order.push_front(pair<HeapTree*, int>(root, level));
	}



}

void insertNode(HeapTree* root, int data) {

    deque<pair<HeapTree*, int>> order;
    getPriorityQueue(root, order);

    HeapTree* topNode = order.front().first;
    order.pop_front();

    if(!isNotNull(topNode->left)) {
		topNode->left = new HeapTree(data);
		topNode->left->left = NULL;
		topNode->left->right = NULL;
    }
    else {
		if(!isNotNull(topNode->right)) {
			topNode->right = new HeapTree(data);
			topNode->right->left = NULL;
			topNode->right->right = NULL;
		}
    }
    int size = root->getSize();
    root->setSize(++size);
    max_heapify(root);

}
HeapTree* mergeRecursive(HeapTree* root, HeapTree* merger, deque<pair<HeapTree*, int>>& order) {


	if(isNotNull(merger->left)) {
		mergeRecursive(root, merger->left, order);
	}
	if(isNotNull(merger->right)) {
		mergeRecursive(root, merger->right, order);
	}

	if(order.empty()) {
		getPriorityQueue(root, order);
	}

	HeapTree* topNode = order.front().first;
	order.pop_front();

	if(!isNotNull(topNode->left)) {
		topNode->left = new HeapTree(merger->data);
		topNode->left->left = NULL;
		topNode->left->right = NULL;
	}
	else {
		if(!isNotNull(topNode->right)) {
			topNode->right = new HeapTree(merger->data);
			topNode->right->left = NULL;
			topNode->right->right = NULL;
		}
	}
		int size = root->getSize();
	    root->setSize(++size);




	return root;


}


HeapTree* merge(HeapTree* root, HeapTree* merger) {


	deque<pair<HeapTree*, int>> order;
	mergeRecursive(root, merger, order);
	max_heapify(root);


	return root;


}


deque<int> heapsort(vector<int> unsorted) {
	
	HeapTree* root = new HeapTree();
	deque<int> sorted;
	construct(unsorted, root);	
	max_heapify(root);
	while(root) {
		sorted.push_front(extractMax(root)->data);
	}
	delete root;
	return sorted;

	

}





int main(int argc, char** argv) {

    vector<int> myvec;
    int heap_size = -1;

   //myvec = {100, 43, 45, 23, 54, 2, 1, 3, 5, 80, 98, 45};

    myvec = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    //std::sort(myvec.begin(), myvec.end());
    //std::reverse(myvec.begin(), myvec.end());
    for(int x : myvec) cout << x << " ";
        cout << endl;



    HeapTree* root = new HeapTree(5);



    root = construct(myvec, root, 0);
    cout << "Heap fully constructed" << endl;
    max_heapify(root);


    print_level_order(root);
    cout << "Heap max-heapified" << endl;

    deleteMax(root);
    cout << endl;
    cout << endl;

    print_level_order(root)
    cout << "root node deleted" << endl;



    deleteNode(root, 5);
    cout << endl;
    cout << endl;

    print_level_order(root);
    cout << "Element at index 5 deleted" << endl;

    for(int i = 0; i < 5; ++i) {

    	insertNode(root, (i+100)*2);
    	cout << endl;
    	cout << endl;
    	print_level_order(root);

    }
    cout << endl;
    cout << endl;

    cout << "Lots of elements just added" << endl;
    cout << endl;
    cout << endl;


    //Testing merge function
    vector<int> myvec2 = {23, 45, 34, 99, 87, 76, 54, 43, 33, 100};
    HeapTree merger = HeapTree(10);
    merger = *construct(myvec2, &merger, 0);
    cout << "Merging"  << endl;
    cout << endl;
    print_level_order(&merger);
    cout << endl;
    cout << "Plus" << endl;
    cout << endl;
    print_level_order(root);


    merge(root, &merger);

    cout << endl;
    cout << endl;
    print_level_order(root);
    cout << endl;
    cout << endl;
    cout << "Merged two trees together!" << endl;
	cout << endl;
	cout << endl;
	cout << "Attempting Heapsort from vector:""
	


    delete root;




    return 0;
}
