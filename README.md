# this is a terminal.
This is a simple shell I created. It's built on C++. It works, allegedly. ON WINDOWS TOO! It uses CMake for building, so read below for help in case you need it.

## Dependencies

- Google Test
- Replxx

## Getting Started

### Prerequisites

Ensure you have the following installed on your local development machine:

- Git
- CMake
- A C++ compiler that supports at least C++17, which shouldn't be hard.

### Cloning the Repository

#### For Unix/Linux/MacOS

1. Open your terminal

2. Clone the repository:
    ```sh
    git clone https://github.com/ricardoprins/thisisaterminal.git
    ```

3. Navigate to the project's root directory:
    ```sh
    cd thisisaterminal
    ```

4. Run the build script:
    ```sh
    ./build.sh
    ```

#### For Windows

This requires a POSIX compatible environment like Git Bash, Cygwin, or the Windows Subsystem for Linux (WSL), or you can use PowerShell. Note that the dependencies (`git`, `cmake`, and `make`) must also be installed and accessible from these environments.

1. Open your terminal or PowerShell

2. Clone the repository:
    ```sh
    git clone https://github.com/ricardoprins/thisisaterminal.git
    ```

3. Navigate to the project's root directory:
    ```sh
    cd thisisaterminal
    ```

4. Run the build script. For Bash or similar:
    ```sh
    ./build.sh
    ```
   For PowerShell:
    ```powershell
    .\build.ps1
    ```

This script will take care of building the project and downloading the necessary dependencies. Now, you have successfully built the project and are ready to go!

### Running the Tests

After building the project, you can run the test suite, which is still incomplete, obviously:

```bash
./test_commands
```

## Contributing

HELP! Please see the [CONTRIBUTING.md](CONTRIBUTING.md) file for more details.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
