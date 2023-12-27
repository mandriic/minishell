# Minishell Project

## Description

The Minishell project is a simplified Unix shell created as part of the curriculum at 42school. This project focuses on reinforcing knowledge in processes, signals, file descriptors, and basic shell functionality.

## Key Features

- **Prompt and Command Execution:**
  - Display a command prompt.
  - Read and parse user input.
  - Execute basic shell commands.

- **Built-in Commands:**
  - Implement built-in shell commands (e.g., echo, cd, pwd).
  - Handle the PATH environment variable for command execution.

- **Environment Variables:**
  - Manage environment variables (set, unset).
  - Expand environment variables in command arguments.

- **Redirection and Pipes:**
  - Implement basic input/output redirection (>, <).
  - Support command piping (|).

- **Signals:**
  - Handle signals (Ctrl-C, Ctrl-\) and provide custom behavior.
  - Implement signal handling for child processes.

...

## Getting Started

### Prerequisites

Ensure you have the following installed on your system:

- [GCC](https://gcc.gnu.org/)
- [Make](https://www.gnu.org/software/make/)
- [Readline Library](https://tiswww.cwru.edu/php/chet/readline/rltop.html)
  - You can install it using your system's package manager:
    - On Ubuntu/Debian: `sudo apt-get install libreadline-dev`
    - On macOS (using Homebrew): `brew install readline`
    - On CentOS/RHEL: `sudo yum install readline-devel`


### Installation

Clone the repository and compile the Minishell project.

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
make


```bash
# Example build and run commands
git clone https://github.com/yourusername/minishell.git
cd minishell
make
./minishell


# Example commands
echo "Hello, Minishell!"
cd /path/to/directory
ls -l
...
