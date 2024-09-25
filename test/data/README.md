# Data Directory

Store the data here that should be used as input files for the tests.
Large files (>50kb) should not be stored here, but rather fetched from a webserver.
Register each file (from external or internal storage) in the `datasources.cmake` file.

There are bash scripts that set up the test cases:
1. Simulate the input data `simulate_input.sh`. The data simulation uses [raptor_data_simulation](https://github.com/eaasna/raptor_data_simulation "data simulation source code") which has to be built from source. Also set the correct binary directory in the script.
2. Call the valik application and generate ground truth output files for testing with `create_output.sh`. The valik binaries have to be in PATH.
3. Register all the input and output files in the `datasources.cmake` file with `update_datasources.sh`.

Call bash script with e.g:
`./simulate_input.sh`
