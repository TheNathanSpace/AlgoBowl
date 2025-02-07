# AlgoBowl

Group members:

- Davita Bird (Verification)
- Josh Hilgartner (Input)
- Kai Hoshijo (Algorithm Implementation)
- Nathan Panzer (Algorithm Implementation)

## Usage

### Algorithm Implementation

Frankly I'm not an expert in getting C++ code to run on different systems. But you should be able to run it in CLion
like this:

1. Open `AlgoBowl` as a project in CLion.
2. When prompted by CLion, select `algo_impl/CMakeLists.txt` as your CMakeLists file.
3. Edit the run configurations to set the working directory to the `AlgoBowl` directory (
   e.g. `/home/nathan/CLionProjects/AlgoBowl`).
4. Run the project.

You'll be prompted for a graph input file, which should be placed in the `AlgoBowl/inputs` directory. Output files will
be in the `AlgoBowl/outputs` directory.
