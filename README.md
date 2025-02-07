# Shell-in-C

## Overview
This is a simple command-line shell implemented in C for Windows. It allows users to execute built-in commands like `cd`, `ls`, `mkdir`, and `clear`, as well as run external commands.

## Features
- Displays the current working directory in the prompt.
- Supports built-in commands:
  - `exit` - Exits the shell.
  - `cd <directory>` - Changes the current directory.
  - `clear` - Clears the console screen.
  - `greet <name>` - Displays a greeting message.
  - `ls` - Lists the contents of the current directory.
  - `mkdir <directory>` - Creates a new directory.
- Executes external commands using the Windows API.

## Compilation
To compile the shell, use a C compiler like MinGW or MSVC:

```sh
gcc shell.c -o shell.exe
```

## Usage
To run the shell, execute the following command:

```sh
./shell.exe
```

Once inside the shell, you can start entering commands.

## Example Commands
```sh
C:\Users\User> ls
Documents
Downloads
Pictures

C:\Users\User> mkdir NewFolder

C:\Users\User> cd NewFolder

C:\Users\User\NewFolder> clear

C:\Users\User\NewFolder> greet Alice
Hello, Alice! Welcome to your custom shell.
```

## Notes
- The shell is designed to work on Windows.
- External commands are executed using the Windows API.
- Some features like `ls` use Windows-specific functions to list directory contents.

## License
This project is open-source and free to use.

