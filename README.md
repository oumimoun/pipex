# pipex
pipes are actually just buffered streams that are associated with two file descriptors that are set up so that the first one can read in data that is written to the second one.

## Note
The file descriptors in the array pd[2] that got returned from `pipe()` are set up so that what is written to 4 can be read from 3.
`fork()` job is to creates a clone of the parent’s memory state and file descriptors.


### File Descriptors and Piping in Bash:

In Bash, a file descriptor is a unique identifier used to access files or streams. There are three default file descriptors:

- `0` (stdin): Standard input.
- `1` (stdout): Standard output.
- `2` (stderr): Standard error.

### Visual Explanation of `pipex` Function:

```
               [Parent Process]
                    /    \
      [Child Process 1]   [Child Process 2]
            (cmd1)               (cmd2)
               |                    |
     data->infile = open         data->pd[1]
               |                    |
          dup2(infile, 0)      dup2(pd[1], 1)
               |                    |
         close(infile)          close(pd[1])
               |                    |
            execve()             execve()
```


### Data Flow:
- The input data comes from the specified input file.
- The output of this process is redirected to the write end of the pipe (`pd[1]`), which will be read by the second process through its `stdin`.

### Visual Explanation:

```
              [Parent Process]
                  /       \
   [Child Process 1]       [Child Process 2]
    (cmd1, input)           (cmd2, output)
         |                       |
         |                       |
    [Pipe Input]           [Pipe Output]
```

### `first_process` Function:

1. Closes the read end of the pipe `data->pd[0]`.
2. Opens the input file (`argv[1]`) for reading.
3. Checks if opening the input file fails, closes the write end of the pipe, prints an error message, and returns NULL.
4. Redirects the standard input (`0`) to the input file descriptor (`data->infile`) using `dup2()`.
5. Redirects the standard output (`1`) to the write end of the pipe (`data->pd[1]`) using another `dup2()`.
6. Closes the write end of the pipe.
7. Splits the second command (`argv[2]`) and finds its path.
8. Closes the input file descriptor.
9. Executes the command using `execve()`. If execution fails, prints an error message.
10. Frees allocated memory and returns NULL.

### `second_process` Function:

1. Closes the write end of the pipe `data->pd[1]`.
2. Opens the output file (`argv[4]`) for writing or creates it if it doesn't exist.
3. Checks if opening the output file fails, closes the read end of the pipe, prints an error message, and returns NULL.
4. Redirects the standard output (`1`) to the output file descriptor (`data->outfile`) using `dup2()`.
5. Redirects the standard input (`0`) to the read end of the pipe (`data->pd[0]`) using another `dup2()`.
6. Closes the read end of the pipe.
7. Splits the third command (`argv[3]`) and finds its path.
8. Closes the output file descriptor.
9. Executes the command using `execve()`. If execution fails, prints an error message.
10. Frees allocated memory and returns NULL.

### Data Flow:

- The `first_process` reads from the input file and writes to the pipe.
- The data written by `first_process` is read by `second_process` from the pipe.
- `second_process` then writes its output to the output file.


# Understanding Pipelines and Interprocess Communication in C

Pipelines are a fundamental concept in Unix-like operating systems, facilitating communication between processes by allowing the output of one process to become the input of another. In C programming, the `pipe()` function is used to create interprocess communication channels, which are implemented as unidirectional pipes. Let's delve deeper into how pipelines work and how they are implemented in C.

## Pipelines in Unix-like Systems:

In Bash and other Unix-like shells, pipelines enable the chaining of multiple commands together, where the output of one command is directed as input to the next command. This is accomplished using the pipe operator `|`. For example:

```bash
command1 | command2
```

Here, the output of `command1` is redirected as input to `command2`, forming a pipeline.

## The `pipe()` Function in C:

In C programming, the `pipe()` function is used to create a unidirectional pipe, which establishes a communication channel between two processes. The function signature is:

```c
int pipe(int pipefd[2]);
```

The `pipefd` parameter is an array of two integers, where `pipefd[0]` represents the read end of the pipe and `pipefd[1]` represents the write end. Data written into `pipefd[1]` can be read from `pipefd[0]`, enabling communication between the two processes.

## Visual Explanation of Pipes:

```
              [Process A]             [Process B]
                 |                        |
           (pd[0])<----- pipe -------(pd[1])
                 |                        |
           Read end                   Write end
```

In the visual representation above:
- `pd[0]` represents the read end of the pipe, where data written by Process B can be read by Process A.
- `pd[1]` represents the write end of the pipe, where data written by Process A can be read by Process B.

## Process Management in C:

To utilize pipelines in C, processes are typically managed using functions like `fork()`, `execve()`, `dup2()`, and `close()`.
- `fork()`: Creates a new process by duplicating the calling process. After forking, two processes are created - the parent and the child.
- `execve()`: Executes a file in the context of the calling process. It replaces the current process image with a new one specified by the file path provided.
- `dup2()`: Duplicates one file descriptor to another specific descriptor. It's commonly used to redirect standard input and output.
- `close()`: Closes a file descriptor, freeing up system resources.

## Summary:

Pipelines are a powerful mechanism for connecting multiple processes and enabling communication between them. In C, the `pipe()` function, along with process management functions like `fork()`, `execve()`, `dup2()`, and `close()`, provides the necessary tools to implement pipelines and interprocess communication efficiently.

Understanding these concepts is essential for developing robust system utilities and handling processes effectively in C programming. By mastering pipelines and interprocess communication, developers can create sophisticated applications that leverage the full capabilities of Unix-like operating systems.

Here is a visulisation of what is going to happend in this code keep in mind that pipe os forked in the parent process and even we use it on the child it change also the parent onr 