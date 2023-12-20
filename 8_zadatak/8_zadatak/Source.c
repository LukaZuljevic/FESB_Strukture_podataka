#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;

Position createNode(int value);
Position insert(Position root, int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
int levelOrder(Position root);
Position search(Position root, int value);
Position deleteNode(Position root, int value);
int replace(Position root);


int main() {
    Position root = NULL;
    Position rootRand = NULL;
    

    root = insert(root, 2);
    insert(root, 5);
    insert(root, 7);
    insert(root, 8);
    insert(root, 11);
    insert(root, 1);
    insert(root, 4);
    insert(root, 2);
    insert(root, 3);
    insert(root, 7);

    levelOrder(root);

    replace(root);

    printf("\n");
    levelOrder(root);

    rootRand = insert(rootRand, random());
    for (int i = 0; i < 10; i++) {
        insert(rootRand, random());
    }

    printf("\n");
    levelOrder(rootRand);

    

    return EXIT_SUCCESS;
}

Position createNode(int value) {
    Position newNode = NULL;
    newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Can't allocate memory!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Position insert(Position root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value)
        root->right = insert(root->right, value);

    return root;
}

int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(Position root) {
    if (root) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(Position root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

int levelOrder(Position root) {
    if (root == NULL)
        return;

    Position queue[100] = { 0 };
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Position current = queue[front++];

        printf("%d ", current->value);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
    return EXIT_SUCCESS;
}

Position search(Position root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);

    return search(root->right, value);
}

Position deleteNode(Position root, int value) {
    if (root == NULL)
        return root;

    // Find node
    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        // Node with one or no children
        if (root->left == NULL) {
            Position temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Position temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, find smallest in the right tree
        Position temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        // Copy value from smallest to current node
        root->value = temp->value;

        // Delete smallest from the right tree
        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}

int replace(Position root) {
    if (root == NULL) {
        return 0;
    }

    // Recursively update left and right subtrees first
    int leftValue = replace(root->left);
    int rightValue = replace(root->right);

    // Store the original value
    int originalValue = root->value;

    // Update the value of the current node to be the sum of its children
    root->value = leftValue + rightValue;

    // Return the sum of the node's value and the sum of its children
    return originalValue + root->value;
}

int random() {
    return (rand() % (90 - 10 + 1)) + 10;
}