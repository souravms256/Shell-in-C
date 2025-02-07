#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

// Function to read user input
void read_input(char *input) {
    char cwd[MAX_INPUT];
    GetCurrentDirectory(MAX_INPUT, cwd);
    printf("%s> ", cwd); // Display prompt with current working directory
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character
}

// Function to parse input into arguments
void parse_input(char *input, char **args) {
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Null-terminate the arguments array
}

// Function to execute built-in commands
int execute_builtin(char **args) {
    // exit command: Exits the shell
    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting shell...\n");
        exit(0);
    }
    // cd command: Changes the current directory
    else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            printf("Usage: cd <directory>\n");
        } else {
            if (SetCurrentDirectory(args[1]) == 0) {
                printf("Error: Directory not found\n");
            }
        }
        return 1;
    }
    // clear command: Clears the console screen
    else if (strcmp(args[0], "clear") == 0) {
        system("cls");  // Clears the console in Windows
        return 1;
    }
    // greet command: Prints a greeting message
    else if (strcmp(args[0], "greet") == 0) {
        printf("Hello, %s! Welcome to your custom shell.\n", (args[1] != NULL) ? args[1] : "User");
        return 1;
    }
    // ls command: Lists the contents of the current directory
    else if (strcmp(args[0], "ls") == 0) {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        char dirSpec[MAX_INPUT] = "*.*"; // Search pattern

        hFind = FindFirstFile(dirSpec, &findFileData);
        if (hFind == INVALID_HANDLE_VALUE) {
            printf("Error listing directory contents\n");
            return 1;
        }

        do {
            printf("%s\n", findFileData.cFileName);
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
        return 1;
    }
    // mkdir command: Creates a new directory
    else if (strcmp(args[0], "mkdir") == 0) {
        if (args[1] == NULL) {
            printf("Usage: mkdir <directory>\n");
        } else {
            if (CreateDirectory(args[1], NULL) == 0) {
                printf("Error: Could not create directory\n");
            }
        }
        return 1;
    }
    return 0; // Not a built-in command
}

// Function to execute external commands using Windows API
void execute_command(char **args) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char command[MAX_INPUT] = "";

    // Construct the command string
    for (int i = 0; args[i] != NULL; i++) {
        strcat(command, args[i]);
        strcat(command, " ");
    }

    // Initialize structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create the process
    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Error executing command: %s\n", command);
        return;
    }

    // Wait for the command to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// Main loop
int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {
        read_input(input);
        parse_input(input, args);
        if (args[0] != NULL) {
            if (!execute_builtin(args)) { // Check if it's a built-in command first
                execute_command(args);  // Otherwise, execute as an external command
            }
        }
    }
    return 0;
}
