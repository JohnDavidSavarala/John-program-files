// Employee Binary Tree

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>

#define MAXIDLENGTH 20
#define MAXNAMELENGTH 100
#define DATA_FILE "EmployeeTree.dat"

typedef struct EmployeeDetails 
{
    char EmployeeId[MAXIDLENGTH];
    char EmployeeName[MAXNAMELENGTH];
    float EmployeeSalary;
} EmployeeDetails;

typedef struct EmployeeNode 
{
    struct EmployeeNode *LeftChild;
    EmployeeDetails EmployeeRecord;
    struct EmployeeNode *RightChild;
} EmployeeNode;

FILE *FpEmployees;
EmployeeNode *RootNode = NULL;
char EmployeeId[MAXIDLENGTH];

void ShowMenu();
void LoadBinaryTree();
void GetDetails(EmployeeDetails *employee);
void AddEmployee();
void ShowAllEmployees(EmployeeNode *);
void UpdateEmployeeDetails(char *);
void DeleteEmployeeRecord(EmployeeNode **, char *);
void SearchEmployeeRecord(char *);
void GetProcessMemoryUsage();
int getNewSalary();

int main() 
{
    time_t StartTime, EndTime;
    StartTime = clock();

    LoadBinaryTree();
    ShowMenu();
    EndTime = clock();
    double ExecutionTimeInSeconds = (double)(EndTime - StartTime) / CLOCKS_PER_SEC;
    double ExecutionTimeInMilliseconds = (double)(EndTime - StartTime) / (CLOCKS_PER_SEC / 1000);
    double ExecutionTimeInMinutes = ExecutionTimeInSeconds / 60;
    printf("Execution time: %.3f minutes\n", ExecutionTimeInMinutes);
    printf("Execution time: %.3f seconds\n", ExecutionTimeInSeconds);
    printf("Execution time: %.3f milliseconds\n", ExecutionTimeInMilliseconds);
    GetProcessMemoryUsage();
    return 0;
}

char *GetEmployeeId()
{
	printf("Enter employee id : ");
	scanf("%s", EmployeeId);
	return EmployeeId;
}

void ShowMenu() 
{
    int choice;
    do 
    {
        printf("\n---------- Employee Management System ----------\n");
        printf("0. Exit\n");
        printf("1. Add an employee\n");
        printf("2. Show all employees\n");
        printf("3. Update employee details\n");
        printf("4. Delete an employee\n");
        printf("5. Search an employee\n");
        printf("------------------------------------\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 0: 
                exit(0);
                break;
            case 1: 
                AddEmployee();
                break;
            case 2: 
                ShowAllEmployees(RootNode);
                break;
            case 3: 
                UpdateEmployeeDetails(GetEmployeeId());
                break;
            case 4: 
                DeleteEmployeeRecord(&RootNode, GetEmployeeId());
                break;
            case 5: 
                SearchEmployeeRecord(GetEmployeeId());
                break;
            default: 
                printf("Invalid choice.\n");
        }
    } while (1);
}

EmployeeNode* LoadBinaryTreeHelper(FILE* FpEmployees) 
{
    if (FpEmployees == NULL) 
    {
        return NULL;
    }

    EmployeeDetails employee;
    if (fread(&employee, sizeof(EmployeeDetails), 1, FpEmployees) == 0) 
    {
        return NULL;
    }

    EmployeeNode* newNode = (EmployeeNode*)malloc(sizeof(EmployeeNode));
    newNode->EmployeeRecord = employee;
    newNode->LeftChild = LoadBinaryTreeHelper(FpEmployees);
    newNode->RightChild = LoadBinaryTreeHelper(FpEmployees);

    return newNode;
}

void LoadBinaryTree() 
{
    FpEmployees = fopen(DATA_FILE, "rb");
    RootNode = LoadBinaryTreeHelper(FpEmployees);
    fclose(FpEmployees);
}

void SaveBinaryTree(EmployeeNode *node, FILE *FpEmployees) 
{
    if (node == NULL) 
    {
        return;
    }
    SaveBinaryTree(node->LeftChild, FpEmployees);
    SaveBinaryTree(node->RightChild, FpEmployees);
    fwrite(&(node->EmployeeRecord), sizeof(EmployeeDetails), 1, FpEmployees);
}

void SaveDetails() 
{
    FpEmployees = fopen(DATA_FILE, "wb");
    SaveBinaryTree(RootNode, FpEmployees);
    fclose(FpEmployees);
}

EmployeeNode* getMatchingNode(EmployeeNode* node, const char* employeeId) 
{
    if (node == NULL || strcmp(node->EmployeeRecord.EmployeeId, employeeId) == 0) 
    {
        return node;
    }

    if (strcmp(employeeId, node->EmployeeRecord.EmployeeId) < 0) 
    {
        return getMatchingNode(node->LeftChild, employeeId);
    } 
    else 
    {
        return getMatchingNode(node->RightChild, employeeId);
    }
}

void GetDetails(EmployeeDetails *employee) 
{
    srand(time(NULL));
    int randomID = rand() % 10000; 
    sprintf(employee->EmployeeId, "%04d", randomID);
    printf("Enter employee name: ");
    scanf(" %99[^\n]s", employee->EmployeeName);
    printf("Enter employee salary: ");
    scanf("%f", &employee->EmployeeSalary);
}

EmployeeNode* AddEmployeeHelper(EmployeeNode* node, EmployeeDetails* newEmployee) 
{
    if (node == NULL) 
    {
        EmployeeNode* newNode = (EmployeeNode*)malloc(sizeof(EmployeeNode));
        newNode->EmployeeRecord = *newEmployee;
        newNode->LeftChild = NULL;
        newNode->RightChild = NULL;
        return newNode;
    }

    if (strcmp(newEmployee->EmployeeId, node->EmployeeRecord.EmployeeId) < 0) 
    {
        node->LeftChild = AddEmployeeHelper(node->LeftChild, newEmployee);
    } 
    else 
    {
        node->RightChild = AddEmployeeHelper(node->RightChild, newEmployee);
    }

    return node;
}

void AddEmployee() 
{
    EmployeeDetails newEmployee;
    GetDetails(&newEmployee);
    RootNode = AddEmployeeHelper(RootNode, &newEmployee);
    SaveDetails();
}

void ShowAllEmployees(EmployeeNode *node) 
{
    if (node == NULL) 
    {
        return;
    }
    ShowAllEmployees(node->LeftChild);
    printf("Employee ID: %s\n", node->EmployeeRecord.EmployeeId);
    printf("Employee Name: %s\n", node->EmployeeRecord.EmployeeName);
    printf("Employee Salary: %.2f\n", node->EmployeeRecord.EmployeeSalary);
    printf("-----------------------------\n");
    ShowAllEmployees(node->RightChild);
}

void UpdateEmployeeDetails(char *employeeId) 
{
    EmployeeNode *targetNode = getMatchingNode(RootNode, employeeId);
    if (targetNode != NULL) 
    {
        targetNode->EmployeeRecord.EmployeeSalary = getNewSalary();
        printf("Record with Id %s Updated succesffully.\n", employeeId);
    }
    else
    {
        printf("Record with Id %s not found.\n", employeeId);
    }
    SaveDetails();
}

EmployeeNode* FindLeafNode(EmployeeNode* node) 
{
    while (node->LeftChild != NULL) 
    {
        node = node->LeftChild;
    }
    return node;
}

void DeleteEmployeeRecord(EmployeeNode** currentPtr, char* employeeId) 
{
    if (*currentPtr == NULL) 
    {
        printf("No employees found.\n");
        return;
    }
    EmployeeNode* nodeToDelete = getMatchingNode(*currentPtr, employeeId);

    if (nodeToDelete->LeftChild == NULL) 
    {
        *currentPtr = nodeToDelete->RightChild;
        free(nodeToDelete);
    } 
    else if (nodeToDelete->RightChild == NULL) 
    {
        *currentPtr = nodeToDelete->LeftChild;
        free(nodeToDelete);
    } 
    else 
    {
        EmployeeNode* temp = FindLeafNode(nodeToDelete->RightChild);
        strcpy(nodeToDelete->EmployeeRecord.EmployeeId, temp->EmployeeRecord.EmployeeId);
        strcpy(nodeToDelete->EmployeeRecord.EmployeeName, temp->EmployeeRecord.EmployeeName);
        nodeToDelete->EmployeeRecord.EmployeeSalary = temp->EmployeeRecord.EmployeeSalary;
        DeleteEmployeeRecord(&(nodeToDelete->RightChild), temp->EmployeeRecord.EmployeeId);
    }

    printf("Employe Record with Id %s Deleted succesfully.\n", employeeId);
    SaveDetails();
}

void SearchEmployeeRecord(char *employeeId) 
{
    EmployeeNode *MatchedNode = getMatchingNode(RootNode, EmployeeId);
    if (MatchedNode != NULL) 
    {
        printf("Employee found:\n");
        printf("ID: %s\n", MatchedNode->EmployeeRecord.EmployeeId);
        printf("Name: %s\n", MatchedNode->EmployeeRecord.EmployeeName);
        printf("Salary: %.2f\n", MatchedNode->EmployeeRecord.EmployeeSalary);
    } 
}

void GetProcessMemoryUsage() 
{
    PROCESS_MEMORY_COUNTERS_EX MemoryCounters;

    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*) &MemoryCounters, sizeof MemoryCounters))
    {
        SIZE_T memoryUsedBytes = MemoryCounters.PrivateUsage;
        SIZE_T memoryUsedMB = memoryUsedBytes / (1024 * 1024);
        SIZE_T memoryUsedKB = memoryUsedBytes / 1024;
        printf("Memory used by the process: %u bytes\n", (unsigned int)memoryUsedBytes);
        printf("Memory used by the process: %u KB\n", (unsigned int)memoryUsedKB);
        printf("Memory used by the process: %u MB\n", (unsigned int)memoryUsedMB);
    }
    else
    {
        printf("Error getting process memory info.\n");
    }
}

int getNewSalary()
{
    float newEmployeeSalary;
    printf("Enter the new salary of the employee: ");
    scanf("%f", &newEmployeeSalary);

    return newEmployeeSalary;
}
