# this is a terminal.
This is a simple shell I created. It's built on C++. It works, allegedly. It uses CMake for building, so read below for help in case you need it.

## Dependencies

- Google Test
- Replxx

These dependencies have been added as Git submodules in this project.

## Getting Started

### Prerequisites

Ensure you have the following installed on your local development machine:

- CMake
- A C++ compiler that supports at least C++17, which shouldn't be hard.

### Cloning the Repository

To clone the repository, run the following command:

```bash
git clone https://github.com/RicardoPrins/thisisaterminal.git
```
Then, because I haven't done my work right with the dependencies, run from within the project folder:

```bash
git clone https://github.com/google/googletest.git
git clone https://github.com/AmokHuginnsson/replxx.git  
```

### Building the Project

To build the project, navigate to the project directory and run:

```bash
mkdir build
cd build
cmake ..
make
```

This will create a `build` directory, generate the Makefile with CMake, and then compile the project with Make.

### Running the Tests

After building the project, you can run the test suite, which is still incomplete, obviously:

```bash
./test_commands
```

## Contributing

HELP! Please see the [CONTRIBUTING.md](CONTRIBUTING.md) file for more details.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
