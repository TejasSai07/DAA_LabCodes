#include<stdio.h>
#include<stdlib.h>

struct Node{
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* createNode(int data){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct Node* insertNode(struct Node* root, int data){
	struct Node* newNode = createNode(data);

	if(root==NULL){
		root=newNode;
		return root;
	}

	else{
		if(newNode->data < root->data) {
			root->left = insertNode(root->left,data);
		}
		else{
			root->right = insertNode(root->right,data);
		}
	}
}


struct Node* Search(struct Node* root, int key) {
	if (root->data == key){
		printf("Element Found\n");
		return root;
	}

	else if(root==NULL){
		root = insertNode(root,key);
		return root;
	}

    else if (root->data < key)
        return Search(root->right, key);
    return Search(root->left, key);
	}

void InOrder(struct Node* root){
	if(root!=NULL){
		InOrder(root->left);
		printf("%d",root->data);
		printf("\n");
		InOrder(root->right);
	}
}
void PreOrder(struct Node* root){
	if(root!=NULL){
		printf("%d",root->data);
		printf("\n");
		PreOrder(root->left);
		PreOrder(root->right);
	}
}
void PostOrder(struct Node* root){
	if(root!=NULL){
		PostOrder(root->left);
		PostOrder(root->right);
		printf("%d",root->data);
		printf("\n");
	}
}


int main(){
	int choice,data;
	struct Node* root = NULL;
	do{
		printf("Enter 1 to Insert Node\nEnter 2 to Search Node\nEnter 3 to Display using Inorder\nEnter 4 to Display using PreOrder\nEnter 5 to Display using PostOrder\nEnter 6 to Exit....\n");
		scanf("%d",&choice);
		if(choice==1){
		printf("Enter the Value to Insert : \n");
		scanf("%d",&data);
		root = insertNode(root,data);                                                   
		}
		else if(choice==2){
		printf("Enter the Value to Search : \n");
		scanf("%d",&data);
		root = Search(root,data);                                                   
		}
		else if(choice==3){
		InOrder(root);                                                   
		}
		else if(choice==4){
		PreOrder(root);                                                   
		}
		else if(choice==5){
		PostOrder(root);                                                   
		}
		else{
			printf("Exiting......");
		}
	}while(choice!=6);
}
