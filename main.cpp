#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

//node struct for binary search tree
struct Node{
  int value;
  Node* left;
  Node* right;
};

// function prototypes
void add (Node* &root, int data);
void print(Node* & root, int depth);
void remove(Node* &root, int r);
void search(Node* &root, int num);

int main()
{
  // set root of BST to NULL to start
  Node* root = NULL;
  char input[20];
  while (strcmp(input, "QUIT") != 0){
    cout << "ADD, DELETE, PRINT, or SEARCH: ";
    cin.get(input, 20);
    cin.get();
    if (strcmp(input, "ADD") == 0){
      char input2[20];
      cout << "manual or file? "; // type manual to enter a multiple numbers manually, file to input all nums in file
      cin.get(input2, 20);
      cin.get();
      if (strcmp(input2, "manual") == 0){
	int n;
	cout << "How many numbers do you want to add? "; // input number of numbers to be manually added
	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; i++){
	  int n2;
	  cout << "Enter Number: ";
	  cin >> n2;
	  cin.ignore();
	  add(root, n2);
	}
	
      }
      if (strcmp(input2, "file") == 0) {
	ifstream inputFile("nums.txt");
	int num;
	while(inputFile >> num){
	  add(root, num);
	  cout << "Added: " << num << endl;
	}
	inputFile.close();
      }
    }
    else if (strcmp(input, "PRINT") == 0){
      print(root, 0);
    }

    else if (strcmp(input, "DELETE") == 0){
      cout << "What number do you want to delete? ";
      int n3;
      cin >> n3;
      cin.ignore();
      remove(root, n3);
    }

    else if (strcmp(input, "SEARCH") == 0 ){
      int num;
      cout << "What number do you want to search for? ";
      cin >> num;
      cin.ignore();
      search(root, num);
    }
  }

  
}


void add(Node* &root, int data)
{
  // once reached an empty node set num to be added to that node
  if (root == NULL){
    root = new Node();
    root->value = data;
    root->left = NULL;
    root->right = NULL;
    return;
  }
  if (data < root->value){ // go down left subtree if num to be added is less than current node
    add(root->left, data);
  }
  else{ // go down right subtree if num to be added is greater than or equal to current node.
    add(root->right, data);
  }
  
}

void remove(Node* &root, int r)
{
  // if gone through the whole tree and a match wasn't found, the num to be deleted does not exist.
  if (root == NULL){
    cout << "Number not found!" << endl;
    return;
  }
  // found a match
  else if (root->value == r){
    // is a leaf
    if (root->left == NULL && root->right == NULL){
      // just remove that node
      Node* temp = root;
      root = NULL;
      delete temp;
    }
    // has a left child and no right child
    else if (root->left != NULL && root->right == NULL){
      //current node removed, replaced with left child
      Node* temp = root;
      root = root->left;
      delete temp;
    }
    //has a right child and no left child
    else if (root->left == NULL && root->right != NULL){
      //current node removed, replaced with right child
      Node* temp = root;
      root = root->right;
      delete temp;
    }
    // has two children
    else{
      // find the inorder successor
      Node* successor = root->right; //start from the right child
      while(successor->left != NULL){ //go down as far left as possible
	successor = successor->left;
      }
      //replace root with the successor
      root->value = successor->value;
      remove(root->right, successor->value);
    }
  }
  // not matching
  else{
    // if less than current node, go down left subtree.
    if (r < root->value){
      remove(root->left, r);
    }
    //if greater than or equal to current node, go down right subtree.
    else{
      remove(root->right, r);
    }
  }
}

// prints the tree sideways
void print(Node*& root, int depth = 0)
{
  // stop when reached end of a subtree
  if (root == NULL){
    return;
  }
  //recurse through right subtree.
  print(root->right, depth+1);

  for (int i = 0; i < depth; i++){ // print indents based on current depth.
    cout << "   ";
  }

  cout << root->value << endl;

  //recurse through left subtree
  print(root->left, depth+1);
}

void search(Node*& root, int num)
{
  // if gone through whole tree and no match was found, the num to be found does not exist
  if (root == NULL){
    cout << "Number not found." << endl;
    return;
  }
  // found a match
  if (root->value == num){
    cout << "Value found! Number: " << num << " is in the tree." << endl;
    return;
  }
  // num to search for is greater than the current node, go down right subtree.
  else if (num > root->value){
    search(root->right, num);
  }
  // num to search for is less than the current node, go down left subtree
  else{
    search(root->left, num);
  }

}

