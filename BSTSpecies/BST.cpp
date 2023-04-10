#include "BST.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

/**************************************************************/
/* These are the methods you are to write for a BST           */
/* More Detailed Instructions can be found in the doc and in  */
/* the BST.hpp file                                           */
/**************************************************************/

BST::BST(string n, string st, string descr, bool Xtra) {
	BSTNode *newNode = new BSTNode(n,st, descr);
	root = newNode;
	Xt = Xtra;
}

bool BST::insert(string n, string st, string descr) {
	if(root == NULL){
		BSTNode *newNode = new BSTNode(n,st, descr);
		root = newNode;
	}
	else{
		BSTNode *temp = root;
		BSTNode *newNode = new BSTNode(n,st, descr);

		while (temp != NULL){

			if(newNode->animal->name < temp->animal->name){
				if(temp->left == NULL){
					 temp->left = newNode;
					 newNode->parent = temp;
					 setHeight(newNode);
					 return true;
				}
				else{
					temp = temp->left;
				}
			}

			else if(newNode->animal->name > temp->animal->name){
				if(temp->right == NULL){
					temp->right = newNode;
					newNode->parent = temp;
					setHeight(newNode);
					return true;
				}
				else{
					temp = temp->right;
				}
			}

			else{
				cout << "Animal is already in the tree" << endl;
				return false;
			}
		}

	}
}

BSTNode *BST::find(string n) {
	bool found = false;
	if(root == NULL){
		cout << "BST is empty, that animal cannot exist" << endl;
	}
	else{
		BSTNode *temp = root;

		while (temp != NULL){

			if(n < temp->animal->name){
				temp = temp->left;
			}

			else if(n > temp->animal->name){
				temp = temp->right;
			}

			else{
				found = true;
				break;
			}
		}
		if(found){
			cout << "Found: ";
			cout << n << endl;
			return temp;
		}
		else{
			cout << n;
			cout << ":";
			cout << " Not Found" << endl;
			return NULL;

		}
	}
}

void BST::updateStatus(string name, string st) {
	BSTNode *node = find(name);
	if(node != NULL){
		node->animal->status = st;
		node->printNode(true);
	}
}

void BST::printTreeIO(BSTNode *tmp) {
	if(tmp == NULL){
		return;
	}
	else{
		printTreeIO(tmp->left);
		tmp->printNode(Xt);
		printTreeIO(tmp->right);
	}
}

void BST::printTreePre(BSTNode *tmp) {
	if(tmp == NULL){
		return;
	}
	else{
		tmp->printNode(Xt);
		printTreePre(tmp->left);
		printTreePre(tmp->right);
	}
}


void BST::printTreePost(BSTNode *tmp) {
	if(tmp == NULL){
		return;
	}
	else{
		printTreePost(tmp->left);
		printTreePost(tmp->right);
		tmp->printNode(Xt);
	}
}

void BST::setHeight(BSTNode *tmp) {
	 BSTNode *ancestor;
	 int heightCheck = 1;
	 while(tmp->parent != NULL){
		 if(heightCheck == tmp->parent->height){
			 tmp->parent->height +=1;
		 }
		 tmp = tmp->parent;
		 heightCheck +=1;
	 }
}

int BST::propHeightFinder(BSTNode *tmpParent){
	int propHeight;
	if(tmpParent->left != NULL && tmpParent->right != NULL){
		if(tmpParent->left->height > tmpParent->right->height){
			propHeight = tmpParent->left->height + 1;
			return propHeight;
		}
		else if(tmpParent->left->height < tmpParent->right->height ){
			propHeight = tmpParent->right->height + 1;
			return propHeight;
		}
		else{
			propHeight = tmpParent->right->height + 1;
			return propHeight;
		}
	}
	else{
		if(tmpParent->left == NULL){ //we know to check the right
			propHeight = tmpParent->right->height + 1;
			return propHeight;
		}
		//we know to check the left
		else{
			propHeight = tmpParent->left->height + 1;
			return propHeight;
		}
	}
}


BSTNode *BST::removeNoKids(BSTNode *tmp) {
	 BSTNode *tmpParent = tmp->parent;
	 int propHeight;

	 if(tmpParent->left != NULL){
		 if(tmpParent->left->animal->name == tmp->animal->name){
			 tmpParent->left = NULL;
		 }
		 else{
			 tmpParent->right = NULL;
		 }

	 }
	 else{
		 tmpParent->right = NULL;
	 }

	 /*Check heights*/
	 //check case where we know the parent is now a leaf node
	 if(tmpParent->right == NULL && tmpParent->left == NULL){
		 tmpParent->height = 1;
		 tmpParent = tmpParent->parent;

		 //find propHeight
		 propHeight = propHeightFinder(tmpParent);

		 while(tmpParent != NULL){
			 if(propHeight == tmpParent->height){
				 break;
			 }
			 tmpParent->height = tmpParent->height - 1;
			 tmpParent = tmpParent->parent;
			 if(tmpParent != NULL){
				 propHeight = propHeightFinder(tmpParent);
				 if(propHeight == tmpParent->height){
					 break;
				 }
			 }
		 }

	 }
	 //if its not a leaf node, we can begin looping
	 else {

		 //find prop height
		 propHeight = propHeightFinder(tmpParent);
		 while(tmpParent != NULL){
		 if(propHeight == tmpParent->height){
			 break;
		 }
		 tmpParent->height = tmpParent->height - 1;
		 tmpParent = tmpParent->parent;
		 if(tmpParent != NULL){
			 propHeight = propHeightFinder(tmpParent);
			 if(propHeight == tmpParent->height){
				 break;
			 }
		 }
	 }
	 }
	 return tmp;
}

BSTNode *BST::removeOneKid(BSTNode *tmp,bool leftFlag) {
// you write
}
BSTNode *BST::remove(string s) {
	BSTNode *temp = find(s);
	if(temp != NULL){
		//if BSTNode is a leaf node
		if(temp->height == 1){
			temp = removeNoKids(temp);
			cout << "successfully removed a node with no kids" << endl;
			return temp;
		}
		//if two childs
		else if(temp->left !=NULL && temp->right != NULL){

		}
		//if one child
		else{

		}
	}
	else{
		return NULL;
	}
}

/**************** Written for you  ***********************/

BST::BST(bool Xtra) {
	root = NULL;
	Xt = Xtra;
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void BST::clearTree(BSTNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode(Xt);
		delete(tmp);
	}
}
void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}

void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}






