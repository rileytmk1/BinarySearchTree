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

void add (Node* &root, int data);
void print(Node*& root, int depth);
void remove(Node* &root, int r);
void search(Node* &root, int num);

int main()
{
  Node* root = NULL;
  char input[20];
  while (strcmp(input, "QUIT") != 0){
    cout << "ADD, DELETE, PRINT, or SEARCH: ";
    cin.get(input, 20);
    cin.get();
    if (strcmp(input, "ADD") == 0){
      char input2[20];
      cout << "manual or file? ";
      cin.get(input2, 20);
      cin.get();
      if (strcmp(input2, "manual") == 0){
	int n;
	cout << "How many numbers do you want to add? ";
	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; i++){
	  int n2;
	  cout << "Enter Numbber: ";
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
  if (root == NULL){
    root = new Node();
    root->value = data;
    root->left = NULL;
    root->right = NULL;
    return;
  }
  if (data < root->value){
    add(root->left, data);
  }
  else{
    add(root->right, data);
  }
  
}

void remove(Node* &root, int r)
{
  if (root == NULL){
    cout << "Number not found!" << endl;
    return;
  }
  else if (root->value == r){
    if (root->left == NULL && root->right == NULL){
      delete root;
      root = NULL;
    }
    else if (root->left != NULL && root->right == NULL){
      Node* temp = root;
      root = root->left;
      delete temp;
    }
    else if (root->left == NULL && root->right != NULL){
      Node* temp = root;
      root = root->right;
      delete temp;
    }
    else{
      Node* successor = root->right;
      while(successor->left != NULL){
	successor = successor->left;
      }
      root->value = successor->value;
      remove(root->right, successor->value);
    }
  }
  else{
    if (r < root->value){
      remove(root->left, r);
    }
    else{
      remove(root->right, r);
    }
  }
}


void print(Node*& root, int depth = 0)
{
  if (root == NULL){
    return;
  }
  print(root->right, depth+1);

  for (int i = 0; i < depth; i++){
    cout << "   ";
  }

  cout << root->value << endl;

  print(root->left, depth+1);
}

void search(Node*& root, int num)
{
  if (root == NULL){
    cout << "Number not found." << endl;
    return;
  }
  if (root->value == num){
    cout << "Value found! Number: " << num << " is in the tree." << endl;
    return;
  }
  else if (num > root->value){
    search(root->right, num);
  }
  else{
    search(root->left, num);
  }

}

