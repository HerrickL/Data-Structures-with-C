/*********************************************************************
** Program Filename: bst.c
** Author: L. Herrick
** Date: 5/4/15
** Description: Implenation file and debugging file for binary search tree
function.  Implementation functions include: initBSTree, clearBSTree,
deleteBSTree, isEmptyBSTree, sizeBSTree, addBSTree, containsBSTree,
removeBSTree.  Helper functions include: _freeBST, _addNode, _leftMost,
_removeLeftMost, _removeNode.  Testing (debugging) mode is currently 
activated on line 379 downwards.  Functions have been built based
off of understandings from worksheet 29.  Output is set to test functions.
** Output: Debugging mode is currently set.  
addNode() test: PASS when adding 50 as root
addNode() test: PASS when adding 13 as left of root
addNode() test: PASS when adding 110 as right of root
addNode() test: PASS when adding 10 as left of left of root

containsBSTree(): PASS when test containing 50 as root
containsBSTree(): PASS when test containing 13 as left of root
containsBSTree(): PASS when test containing 110 as right of root
containsBSTree(): PASS when test containing 10 as left of left of root
containsBSTree(): PASS when test containing 111, which is not in the tree

_leftMost(): PASS left most of root
_leftMost(): PASS left most of left of root
_leftMost(): PASS left most of left of left of root
_leftMost(): PASS left most of right of root

_removeLeftMost(): PASS removing leftmost of root 1st try
_removeLeftMost(): PASS removing leftmost of right of root 1st try
_removeLeftMost(): PASS removing leftmost of root 2st try

_removeNode(): PASS remove left of left of root 1st try
_removeNode(): PASS remove right of root 2st try
_removeNode(): PASS remove right of root 3st try
_removeNode(): PASS remove right of root 4st try
*********************************************************************/

/*
 File: bst.c
 Implementation of the binary search tree data structure.
 
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"


struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
 function to initialize the binary search tree.
 param tree
 pre: tree is not null
 post:	tree size is 0
		root is null
 */

void initBSTree(struct BSTree *tree)
{
	tree->cnt  = 0;
	tree->root = 0;
}

/*
 function to create a binary search tree.
 param: none
 pre: none
 post: tree->count = 0
		tree->root = 0;
 */

struct BSTree*  newBSTree()
{
	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != 0);

	initBSTree(tree);
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
 pre: none
 post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
	if (node != 0) {
		_freeBST(node->left);
		_freeBST(node->right);
		free(node);
	}
}

/*
 function to clear the nodes of a binary search tree
 param: tree    a binary search tree
 pre: tree ! = null
 post: the nodes of the tree are deallocated
		tree->root = 0;
		tree->cnt = 0
 */
void clearBSTree(struct BSTree *tree)
{
	_freeBST(tree->root);
	tree->root = 0;
	tree->cnt  = 0;
}

/*
 function to deallocate a dynamically allocated binary search tree
 param: tree   the binary search tree
 pre: tree != null;
 post: all nodes and the tree structure itself are deallocated.
 */
void deleteBSTree(struct BSTree *tree)
{
	clearBSTree(tree);
	free(tree);
}

/*----------------------------------------------------------------------------*/
/*
 function to determine if  a binary search tree is empty.

 param: tree    the binary search tree
 pre:  tree is not null
 */
int isEmptyBSTree(struct BSTree *tree) { return (tree->cnt == 0); }

/*
 function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { return tree->cnt; }

/*----------------------------------------------------------------------------*/
/*
 recursive helper function to add a node to the binary search tree.
 HINT: You have to use the compare() function to compare values.
 param:  cur	the current root node
		 val	the value to be added to the binary search tree
 pre:	val is not null
 */
struct Node *_addNode(struct Node *cur, TYPE val)
{ 
	/*Added Code Here*/
	assert(val != NULL);

	/* empty tree or branch*/
	if(cur == 0){
		
		/*create node */
		struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
		assert(newNode != 0);

		newNode->val = val;
		newNode->left = newNode->right = 0;
		
		return newNode;
	}
	/* value < Node.value */
	if(compare(val, cur->val) == -1){
	
		/* recursion: left child = addNode(left child, value */
		cur->left  = _addNode(cur->left, val);
	}
	/* value > Node.value */
	else if (compare(val, cur->val) == 1){ 

		/*recursion:  right child = addNode(right child, value)*/
		cur->right = _addNode(cur->right, val);
	}

	/* return current node: it equals something already there or prev recursion added */
	return cur;

}

/*
 function to add a value to the binary search tree
 param: tree   the binary search tree
		val		the value to be added to the tree

 pre:	tree is not null
		val is not null
 pose:  tree size increased by 1
		tree now contains the value, val
 */
void addBSTree(struct BSTree *tree, TYPE val)
{
	tree->root = _addNode(tree->root, val);
	tree->cnt++;
}


/*
 function to determine if the binary search tree contains a particular element
 HINT: You have to use the compare() function to compare values.
 param:	tree	the binary search tree
		val		the value to search for in the tree
 pre:	tree is not null
		val is not null
 post:	none
 */

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
	/*Added Code Here*/
	assert(val != NULL);
	assert(tree != 0);

	struct Node *current = tree->root;

	/* while not the end, iterate */
	while( current != 0){

		/* if larger */
		if(compare(current->val, val) == -1){

			/* go right */
			current = current->right;
		}
		/* else if smaller */
		else if(compare(current->val, val) == 1){

			/* go left */
			current = current -> left;
		}
		/*else equal */
		else{
		
			/*  found!!!! */
			return 1;
		}	
	}

	/* not found*/
	return 0;
}

/*
 helper function to find the left most child of a node
 return the value of the left most child of cur
 param: cur		the current node
 pre:	cur is not null
 post: none
 */

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{
	/* Added Code Here */
	assert(cur != 0);

	/* find leftmost of current */
	while(cur->left != 0){

			cur = cur->left;
	}

	return cur->val;
}


/*
 recursive helper function to remove the left most child of a node
 HINT: this function returns cur if its left child is NOT NULL. Otherwise,
 it returns the right child of cur and free cur.

Note:  If you do this iteratively, the above hint does not apply.

 param: cur	the current node
 pre:	cur is not null
 post:	the left most node of cur is not in the tree
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
	/* Added Code Here */
	assert(cur != 0);

	struct Node* rightSide;

	/* iterate until leftmost */
	if(cur->left == 0){
		rightSide = cur->right;
		free(cur);
		return rightSide; 
	}

	/* use of recursion as specified */
	cur->left = _removeLeftMost(cur->left);
	return cur;

}
/*
 recursive helper function to remove a node from the tree
 HINT: You have to use the compare() function to compare values.
 param:	cur	the current node
		val	the value to be removed from the tree
 pre:	val is in the tree
		cur is not null
		val is not null
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
	/* Added Code Here */
	assert(cur != 0);
	assert(val != NULL);
	/* contains is checked for in removeBSTree */

	struct Node *adjusted;	

	/* if value == current.value */
	if(compare(val, cur->val) == 0){
		
		/* if right child is null */
		if(cur->right == 0){
			
			/* it doesn't matter to check if current->left is 				null, you still need to return */

			/* go left */
			adjusted = cur->left;
			free(cur);
				
			/* return left child */
			/* this will be reattached in removeBST */
			return adjusted;				
		}
		
		/* Not above condition: go right and make adjustments */

		/* replace value with leftmost child of right child*/
		adjusted->val = _leftMost(cur->right);

		/* set right child to be removeLeftMost(right) */
		adjusted->right = _removeLeftMost(cur->right);	
	}

	/*else if value < current.value */
	else if(compare(val, cur->val) == -1){
	
		/* recursion */
		/* left child = removeNode(left child, value) */
		cur->left = _removeNode(cur->left, val);
	}		
	/* else */
	else{
		/* recursion */
		/* right child = removeNode(right child, value) */
		cur->right = _removeNode(cur->right, val);

	}

	/* return current node */
	return cur;
}


/*F
 function to remove a value from the binary search tree
 param: tree   the binary search tree
		val		the value to be removed from the tree
 pre:	tree is not null
		val is not null
		val is in the tree
 pose:	tree size is reduced by 1
 */
void removeBSTree(struct BSTree *tree, TYPE val)
{
	if (containsBSTree(tree, val)) {
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}

/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used 
  in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
	 if (cur == 0) return;
	 printf("(");
	 printNode(cur->left);	 
	 /*Call print_type which prints the value of the TYPE*/
	 print_type(cur->val);
	 printNode(cur->right);
	 printf(")");
}

void printTree(struct BSTree *tree) {
	 if (tree == 0) return;	 
	 printNode(tree->root);	 
}
/*----------------------------------------------------------------------------*/

#endif


#if 1
/************************************************************************************************************************
from here to the end of this file are a set of fucntions for testing the fucntions of the BST - This is also provided in a 
separate file .
***************************************************************************************************************************/
/*
function to built a Binary Search Tree (BST) by adding numbers in this specific order
the graph is empty to start: 50, 13, 110 , 10

*/
struct BSTree *buildBSTTree() {
    /*     50
         13  110
        10 
    */
    struct BSTree *tree	= newBSTree();		
		
	/*Create value of the type of data that you want to store*/
	struct data *myData1 = (struct data *) malloc(sizeof(struct data));
	struct data *myData2 = (struct data *) malloc(sizeof(struct data));
	struct data *myData3 = (struct data *) malloc(sizeof(struct data));
	struct data *myData4 = (struct data *) malloc(sizeof(struct data));
		
	myData1->number = 50;
	myData1->name = "rooty";
	myData2->number = 13;
	myData2->name = "lefty";
	myData3->number = 110;
	myData3->name = "righty";
	myData4->number = 10;
	myData4->name = "lefty of lefty";
	
	/*add the values to BST*/
	addBSTree(tree, myData1);
	addBSTree(tree, myData2);
	addBSTree(tree, myData3);
	addBSTree(tree, myData4);
    
    return tree;
}

/*
function to print the result of a test function
param: predicate:  the result of the test 
       nameTestFunction : the name of the function that has been tested
	   message

*/
void printTestResult(int predicate, char *nameTestFunction, char *message){
	if (predicate)
	   printf("%s(): PASS %s\n",nameTestFunction, message);
    else
	   printf("%s(): FAIL %s\n",nameTestFunction, message);        
}

/*
fucntion to test each node of the BST and their children

*/
void testAddNode() {
    struct BSTree *tree	= newBSTree();
    
    struct data myData1,  myData2,  myData3,  myData4;
		
	myData1.number = 50;
	myData1.name = "rooty";
    addBSTree(tree, &myData1);
    //check the root node
    if (compare(tree->root->val, (TYPE *) &myData1) != 0) {
        printf("addNode() test: FAIL to insert 50 as root\n");
        return;
    }
	//check the tree->cnt value after adding a node to the tree
    else if (tree->cnt != 1) {
        printf("addNode() test: FAIL to increase count when inserting 50 as root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 50 as root\n");
    
    
	myData2.number = 13;
	myData2.name = "lefty";
    addBSTree(tree, &myData2);
    
    //check the position of the second element that is added to the BST tree
    if (compare(tree->root->left->val, (TYPE *) &myData2) != 0) {
        printf("addNode() test: FAIL to insert 13 as left child of root\n");
        return;
    }
    else if (tree->cnt != 2) {
        printf("addNode() test: FAIL to increase count when inserting 13 as left of root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 13 as left of root\n");
    
    
	myData3.number = 110;
	myData3.name = "righty";
    addBSTree(tree, &myData3);
        
    //check the position of the third element that is added to the BST tree    
    if (compare(tree->root->right->val, (TYPE *) &myData3) != 0) {
        printf("addNode() test: FAIL to insert 110 as right child of root\n");
        return;
    }
    else if (tree->cnt != 3) {
        printf("addNode() test: FAIL to increase count when inserting 110 as right of root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 110 as right of root\n");
    
    
	myData4.number = 10;
	myData4.name = "righty of lefty";
	addBSTree(tree, &myData4);
    
	//check the position of the fourth element that is added to the BST tree
    if (compare(tree->root->left->left->val, (TYPE *) &myData4) != 0) {
        printf("addNode() test: FAIL to insert 10 as left child of left of root\n");
        return;
    }
    else if (tree->cnt != 4) {
        printf("addNode() test: FAIL to increase count when inserting 10 as left of left of root\n");
        return;
    }
    else printf("addNode() test: PASS when adding 10 as left of left of root\n");
}

/*
fucntion to test that the BST contains the elements that we added to it

*/
void testContainsBSTree() {
    struct BSTree *tree = buildBSTTree();
    
    struct data myData1,  myData2,  myData3,  myData4, myData5;
	
	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    myData5.number = 111;
	myData5.name = "not in tree";
    
    printTestResult(containsBSTree(tree, &myData1), "containsBSTree", "when test containing 50 as root");
        
    printTestResult(containsBSTree(tree, &myData2), "containsBSTree", "when test containing 13 as left of root");
    
	printTestResult(containsBSTree(tree, &myData3), "containsBSTree", "when test containing 110 as right of root");
        
    printTestResult(containsBSTree(tree, &myData4), "containsBSTree", "when test containing 10 as left of left of root");

     //check containsBSTree fucntion when the tree does not contain a node    
    printTestResult(!containsBSTree(tree, &myData5), "containsBSTree", "when test containing 111, which is not in the tree");
    
}

/*
fucntion to test the left_Most_element 

*/
void testLeftMost() {
    struct BSTree *tree = buildBSTTree();
    
	struct data myData3, myData4;

	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    
	printTestResult(compare(_leftMost(tree->root), &myData4) == 0, "_leftMost", "left most of root");
    
	printTestResult(compare(_leftMost(tree->root->left), &myData4) == 0, "_leftMost", "left most of left of root");
    
	printTestResult(compare(_leftMost(tree->root->left->left), &myData4) == 0, "_leftMost", "left most of left of left of root");
    
	printTestResult(compare(_leftMost(tree->root->right), &myData3) == 0, "_leftMost", "left most of right of root");

}

void testRemoveLeftMost() {
    struct BSTree *tree = buildBSTTree();
    struct Node *cur;
    
    cur = _removeLeftMost(tree->root);

	printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");
    
    cur = _removeLeftMost(tree->root->right);
    printTestResult(cur == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");
   
 	cur = _removeLeftMost(tree->root);
    printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");
}

void testRemoveNode() {
    struct BSTree *tree = buildBSTTree();
    struct Node *cur;
     struct data myData1,  myData2,  myData3,  myData4;
		
	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    
    _removeNode(tree->root, &myData4);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");
	        
    _removeNode(tree->root, &myData3);
	 printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->right == NULL, "_removeNode", "remove right of root 2st try");
	   
    _removeNode(tree->root, &myData2);
	printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "_removeNode", "remove right of root 3st try");
        
    cur = _removeNode(tree->root, &myData1);
    printTestResult(cur == NULL, "_removeNode", "remove right of root 4st try");       
}

/*

Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]){	

   //After implementing your code, please uncommnet the following calls to the test functions and test your code 

   testAddNode();
	
	printf("\n");
   testContainsBSTree();
	
	printf("\n");
    testLeftMost();
	
	printf("\n");
    testRemoveLeftMost();
	
	printf("\n");
    testRemoveNode();
    
	
	return 0;


}

#endif
