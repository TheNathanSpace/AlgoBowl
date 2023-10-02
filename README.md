# AlgoBowl

Group members:
- Davita Bird (Verification)
- Josh Hilgartner (Input)
- Kai Hoshijo (Algorithm Implementation)
- Nathan Panzer (Algorithm Implementation)

## Usage

### Algorithm Implementation

Frankly I'm not an expert in getting C++ code to run on different systems. But you should be able to run it in CLion like this:

1. Open `algo_impl` as a project in CLion.
2. Edit the run configurations to set the working directory to the `algo_impl` directory (e.g. `/home/nathan/CLionProjects/AlgoBowl/algo_impl`).
3. Run the project.

You'll be prompted for a graph input file, which should be placed in the `algo_impl` directory. Output files will be in the same directory (probably will be changed).

## TODO:

### Algorithm Implementation

Right now, `algo_impl` can read in a graph file, construct the `Graph` object, and output it to a `.DOT` file for visualization. It's ready for the actual algorithms:

- Normal MST
- MST, but deleting unnecessary leaves
- ???
- Win
