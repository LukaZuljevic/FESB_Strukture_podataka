#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LENGTH (1024)

struct _stackElement;
typedef struct _stackElement* Position;
typedef struct _stackElement {
    double number;
    Position next;
} StackElement;


int calculatePostfixFromFile(Position head, char* fileName, double* result);
int readFile(char* fileName, char* buffer);
int parseStringIntoPostfix(Position head, char* buffer, double* result);
int checkStackAndExtractResult(Position head, double* result);
Position createStackElement(double number);
int push(Position head, Position newStackElement);
int printStack(Position first);
int pop(Position head, double* result);
int popAndPerformOperation(Position head, char operation, double* result);

int main() {
    StackElement head = { .number = 0, .next = NULL };
    double result = 0;

    if (calculatePostfixFromFile(&head, "postfix.txt", &result) == EXIT_SUCCESS) {
        printf("Result is: %0.1lf\n", result);
    }

    return 0;
}

int calculatePostfixFromFile(Position head, char* fileName, double* result) {
    char buffer[MAX_LENGTH] = { 0 };
    int status = 0;

    if (readFile(fileName, buffer) != 0 || !buffer) {
        return 1;
    }

    status = parseStringIntoPostfix(head, buffer, result);
    if (status != 0) {
        return 1;
    }

    return 0;
}

int readFile(char* fileName, char* buffer) {
    FILE* filePointer = NULL;
    filePointer = fopen(fileName, "r");
    if (!filePointer) {
        perror("Can't open file!\n");
        return NULL;
    }

    fgets(buffer, MAX_LENGTH, filePointer);
    printf("|%s|\n", buffer);

    fclose(filePointer);

    return 0;
}

int parseStringIntoPostfix(Position head, char* buffer, double* result)
{
    char* currentBuffer = buffer;
    int status = 0;
    int numBytes = 0;
    char operation = 0;
    double number = 0.0;
    Position newStackElement = NULL;

    while (strlen(currentBuffer) > 0) {
        status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
        if (status != 1) {
            sscanf(currentBuffer, " %c %n", &operation, &numBytes);
            status = popAndPerformOperation(head, operation, result);

            if (status != 0) {
                return 1;
            }

            number = *result;
        }

        newStackElement = createStackElement(number);
        if (!newStackElement) {
            return 1;
        }

        currentBuffer += numBytes;
        printf("|%s| <-->", currentBuffer);
        push(head, newStackElement);
    }

    return checkStackAndExtractResult(head, result);
}

int checkStackAndExtractResult(Position head, double* result) {
    int status = 0;

    status = pop(head, result);

    if (status != 0) {
        return status;
    }

    if (head->next) {
        system("cls"); //clear screen
        printf("Invalid postfix, please check the file!\r\n");
        return 1;
    }

    return 0;
}

Position createStackElement(double number)
{
    Position newStackElement = NULL;

    newStackElement = (Position)malloc(sizeof(StackElement));
    if (!newStackElement) {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    newStackElement->number = number;
    newStackElement->next = NULL;

    return newStackElement;
}

int push(Position head, Position newStackElement) {
    newStackElement->next = head->next;
    head->next = newStackElement;

    printStack(head->next);

    return 0;
}

int printStack(Position first) {
    Position current = first;

    while (current) {
        printf(" %0.1lf", current->number);
        current = current->next;
    }
    printf("\n");

    return 0;
}

int pop(Position head, double* result) {
    Position toDelete = NULL;

    toDelete = head->next;
    if (!toDelete) {
        printf("Stack is empty! Nothing to pop!\n");
        return -1;
    }

    head->next = toDelete->next;
    *result = toDelete->number;
    free(toDelete);

    return EXIT_SUCCESS;
}

int popAndPerformOperation(Position head, char operation, double* result) {
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = pop(head, &operand1);
    if (status1 != 0) {
        return 1;
    }

    status2 = pop(head, &operand2);
    if (status2 != 0) {
        return 1;
    }

    switch (operation) {
    case '+':
        *result = operand2 + operand1;
        break;
    case '-':
        *result = operand2 - operand1;
        break;
    case '*':
        *result = operand2 * operand1;
        break;
    case '/':
        *result = operand2 / operand1;
        break;
    default:
        printf("Operation %c not supported yet!\r\n", operation);
        return 1;
    }

    return 0;
}