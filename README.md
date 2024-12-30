# Race Simulation with Concurrency

This project is a simulation of a race using concurrency principles in C++. It models racers competing in a controlled environment, managed by a game master. The project demonstrates advanced use of concurrency constructs to manage and coordinate multiple threads.

## Features
- **Concurrent Race Simulation**: Simulates multiple racers competing, with their actions executed concurrently.
- **Game Master Coordination**: Implements a centralized game master to manage racer interactions and ensure smooth execution.
- **Thread-Safe Design**: Uses mutexes and condition variables to avoid race conditions and ensure thread-safe operations.
- **Modular Codebase**: Organized structure with dedicated files for racers, game master, and race logic.

## Project Structure
```
kkp56_assn5/
|-- makefile           # Build instructions
|-- docconfig          # Documentation configuration (if applicable)
|-- src/               # Source code
    |-- gamemaster.cpp # Game master implementation
    |-- gamemaster.h   # Game master definitions
    |-- racer.cpp      # Racer implementation
    |-- racer.h        # Racer definitions
    |-- race.cpp       # Core race logic
```

## Prerequisites
- **Compiler**: GCC or any C++17 compatible compiler.
- **Build Tools**: Make utility.

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/race-simulation.git
   ```
2. Navigate to the project directory:
   ```bash
   cd race-simulation
   ```

## Usage
### Build the Project
Run the following command in the project directory:
```bash
make
```
This will compile the source files and generate an executable named `race_simulation`.

### Run the Program
Execute the program to start the race simulation:
```bash
./race_simulation
```
Follow the on-screen instructions to interact with the simulation.

## Key Files
- **`gamemaster.cpp` & `gamemaster.h`**: Implement the game master logic, managing racer coordination and ensuring orderly execution of the race.
- **`racer.cpp` & `racer.h`**: Define and implement racer behavior, simulating their progress through the race.
- **`race.cpp`**: Contains the main race logic, integrating racers and the game master.

## Technical Highlights
- **Concurrency Constructs**:
  - Utilized **std::mutex** and **std::condition_variable** to synchronize threads.
  - Managed multiple threads representing racers to simulate real-time racing behavior.
- **Object-Oriented Design**:
  - Encapsulated racer and game master logic in separate classes for clarity and modularity.
  - Facilitated clean integration of components through well-defined interfaces.
- **Thread Safety**:
  - Ensured race conditions were avoided using proper locking mechanisms.
  - Coordinated racer progress and game master commands efficiently.

## Learning Outcomes
- Practical experience with concurrency in C++.
- Hands-on understanding of thread synchronization techniques.
- Insights into modular software design and simulation modeling.

## Author
- **Kavin Parakh**

Feel free to contribute or reach out for collaboration opportunities!
