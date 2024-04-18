#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new node
TreeNode* newNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find the index of a value in an array
int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to construct binary search tree from in-order and post-order traversals
TreeNode* bst_construct(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    TreeNode* root = newNode(postorder[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd) {
        return root;
    }

    int inIndex = findIndex(inorder, inStart, inEnd, root->data);

    root->right = bst_construct(inorder, postorder, inIndex + 1, inEnd, postIndex);
    root->left = bst_construct(inorder, postorder, inStart, inIndex - 1, postIndex);

    return root;
}

// Function to traverse binary search tree in breadth-first-search (BFS) traversal
void bfs_traversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

int main() {
    int inorder[] = {5, 10, 15, 20, 25, 30, 45};
    int postorder[] = {5, 15, 10, 25, 45, 30, 20};
    int postIndex = 6; // Index of the last element in postorder traversal

    TreeNode* root = bst_construct(inorder, postorder, 0, 6, &postIndex);

    printf("BFS Traversal: ");
    bfs_traversal(root);
    printf("\n");

    return 0;
}