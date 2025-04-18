# Operating Systems Class Repository

Welcome to the Operating Systems Class repository! This repository is dedicated to storing the homework assignments (HW) completed during the operating systems course.

## Navigation

-   [HW1](HW1/)
    -   [myshell.c](HW1/myshell.c)
    -   [Makefile](HW1/Makefile)
    -   [tests](HW1/tests/) - tests provided by the course; we can also add our own.

## Using the Makefile

To use the Makefile in any HW directory, follow these steps:

1. **Navigate to the HW1 directory**:

    ```sh
    cd HW{NUM}
    ```

2. **Compile the program**:

    ```sh
    make
    ```

    This command will compile the source code and produce an executable.

3. **Run the program**:

    ```sh
    make run
    ```

    This command will execute the compiled program.

4. **Test the program**:

    ```sh
    make test
    ```

    This command will run predefined tests to verify the program's functionality.

5. **Clean the directory**:
    ```sh
    make clean
    ```
    This command will remove the compiled executable and any other files generated during the build process.

Make sure you are in the HW directory before running these commands to ensure they execute correctly.
