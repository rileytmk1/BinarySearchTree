#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

struct Node{
  int value;
  Node* left;
  Node* right;
};

void add (Node* node, int data);
void print(Node* root);


int main()
{
  Node* root = new Node();
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
	/*
	for (int i = 0; i < n; i++){
	  
	}
	*/
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
      cout << root->value << endl;
    }
  }

  
}


void add(Node* node, int data)
{
  Node* newNode = new Node();
  newNode->value = data;
  if (node == NULL){
    node = newNode;
    cout << node->value << endl;
    return;
  }
  else if (data <= node->value){
    add(node->left, data);
  }
  else if (data > node->value){
    add(node->right, data);
  }
  
}

/*
void print(Node* root)
{
  cout << root->value << endl;
}
*/
