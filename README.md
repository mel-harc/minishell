# Introduction to **Minishell** 🐚

Welcome to **Minishell**, a project designed to help you build a **simplified shell** from scratch! This project immerses you in the world of **operating systems**, **process management**, and **command-line interfaces**, allowing you to understand how a shell functions internally while sharpening your C programming skills. 🚀

---

## **What is a Shell?** 🖥️

A **shell** is a command-line interface that allows users to interact with the operating system. It's a program that reads user inputs (commands), interprets them, and executes the appropriate actions—whether running programs, managing files, or controlling system processes.  

The most popular shell is **Bash**, but in this project, you'll create your own mini version, aptly named **Minishell**!

---

## **Project Goals** 🎯

This project aims to teach you to:
- **Handle input/output**: Create a prompt that interacts dynamically with user input.  
- **Implement a parser**: Break down commands, handle quotes, and manage special characters like pipes (`|`) and redirections (`<`, `>`).  
- **Execute commands**: Use system calls like `execve` to run programs.  
- **Manage processes**: Learn about **forking**, **piping**, and process control.  
- **Understand signals**: Handle user interrupts like `Ctrl+C` and manage terminal behavior.  
- **Work with environment variables**: Parse and utilize `$PATH`, `$HOME`, and others.  

By the end, you'll gain a deep understanding of how the shell interprets and executes commands. 🔍

---

## **Your Minishell Should...** 📋

- Mimic the behavior of **Bash** as closely as possible in terms of features and functionality.  
- Handle complex operations like:
  - **Redirections** (`>`, `<`, `>>`, `<<`).  
  - **Pipes** (`|`) for chaining commands.  
  - **Environment variables** (e.g., `$USER`, `$PATH`).  
- Implement **built-in commands** like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.  

---

## **Why Build Minishell?** 🤔

Creating a shell isn't just about coding a program—it’s about:
- Understanding **low-level system interactions** (like process management and file descriptors).  
- Gaining expertise in **UNIX system calls**.  
- Developing robust error handling for real-world scenarios.  
- Becoming proficient in working with the **command line** and **interactive programs**.  

By completing Minishell, you'll bridge the gap between theoretical knowledge and practical system-level programming. 🌉

---

### **Start building your shell, and let the journey begin!** 🛠️


## Minishell Requirements 🐚

### Program Details

- **Name**: `minishell`  
- **Files**: `Makefile`, `*.h`, `*.c`  
- **Arguments**: Commands entered via prompt  
- **External Functions**:
  - Libraries like `readline`, `malloc`, `write`, and more 📖.  
- **Libft**: Authorized ✅.  

---

### Shell Features 🧩

- **Prompt**: Display a prompt when awaiting a new command 🖥️.  
- **History**: Maintain a working command history 📜.  
- **Executable Search**:
  - Locate executables using `$PATH`, relative, or absolute paths 🔍.  

---

### Command Handling ⚙️

- **Quoting**:
  - **Single quotes ('')**: Prevent shell from interpreting metacharacters.  
  - **Double quotes ("")**: Prevent interpretation except for `$` (variables).  
- **Redirections**:
  - `<`: Redirect input 🔄.  
  - `>`: Redirect output 🔄.  
  - `<<`: Read input until a delimiter line is encountered.  
  - `>>`: Redirect output in append mode 🔄.  
- **Pipes (`|`)**:
  - Connect commands; output of one is the input to the next 📦.  
- **Environment Variables**:
  - `$VARIABLE_NAME`: Expand to their values 🧩.  
  - `$?`: Expand to the exit status of the last foreground pipeline.  
- **Signal Handling**:
  - **Ctrl-C**: Display a new prompt 🔄.  
  - **Ctrl-D**: Exit the shell 🛑.  
  - **Ctrl-\\**: Do nothing 🚫.

---

### Built-in Commands 🔧

- `echo` with `-n` option 🗣️.  
- `cd` with relative/absolute paths 📂.  
- `pwd` to display the working directory 🗺️.  
- `export` for environment variables 🛠️.  
- `unset` to remove environment variables ❌.  
- `env` to display the environment 🌐.  
- `exit` to close the shell 🚪.  

--- 

# How to Use This Repository 📂

This guide will walk you through how to run the project. Follow the steps below to make the most of the repository.

---

## **Clone the Repository** 🖇️
Start by cloning this repository to your local machine:

```bash
git clone git@github.com:mel-harc/minishell.git
```
## **Entry to the Repository** 🖇️

To navigate into the repository after cloning it, use the following command:

```bash
cd minishell
```

This command changes your current directory to the Minishell project folder, allowing you to access the project's files and proceed with building or running the shell.

## **Run Minishell 🚀**

To run **Minishell** using Docker, follow these steps:

1. Build the Docker container:  
   ```bash
   docker build -t minishell .
   ```
2. Run the Minishell container:
   ```bash
   docker run -it minishell
   ```
You'll be greeted with your custom shell prompt inside the Docker container! 🎉

## **Usage Instructions 🖥️**

Here’s how to interact with your **Minishell**:

### **Run Commands**  
Execute system commands as you would in a regular shell:  
```bash
minishell$> ls -l
minishell$> echo "Hello, Minishell!"
```

## **Features of Minishell 🚀**

### **Built-in Commands 🛠️**  
Minishell supports the following built-in commands:  
- **`cd`**: Change the current directory.  
- **`pwd`**: Display the current working directory.  
- **`echo`**: Print text to the terminal.  
- **`env`**: Show environment variables.  
- **`export`**: Set new environment variables.  
- **`unset`**: Remove environment variables.  
- **`exit`**: Exit the shell.

---

### **Redirections 🔄**  
Minishell supports input/output redirection:  
```bash
minishell$> ls > file.txt            # Redirect standard output to a file.
minishell$> cat < file.txt           # Redirect standard input from a file.
minishell$> echo "append this" >> file.txt  # Append output to a file.
```

### **Pipes ⛓️**  
Leverage pipes to link the output of one command to the input of another:  
```bash
minishell$> ls | grep minishell
minishell$> ls | cat
minishell$> cat | cat | ls
```

### **Environment Variables 🌱** 

Interact with environment variables to enhance flexibility:

```bash
minishell$> echo $PATH               # Display the current PATH environment variable.
minishell$> export MY_VAR="Hello"    # Define a custom environment variable.
minishell$> echo $MY_VAR             # Retrieve the value of your custom variable.
```
## by mel-harc


