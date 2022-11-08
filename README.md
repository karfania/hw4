## HW 4

 - Name: Kourosh Arfania
 - Email: arfania@usc.edu

### Checkpoint 1 Notes

#### Compiling the Code:

- Enter docker container (`ch start csci104` -> `ch shell csci104`) or use Codio and navigate to `hw4/`

##### equal-paths-test
(1) Ensure you are in the `hw4` directory

(2) Run `make equal-paths-test` to compile and link all files for the balance checker

(3) Enter `./equal-paths-test` in your terminal to run the basic tests in `equal-paths-test.cpp`

(4) Run `valgrind --tool=memcheck --leak-check=yes ./equal-paths-test` to check for memory loss/leaks

`Note: run more intensive tests by navigating to hw4_tests/equalpaths_tests, run make equalpaths_tests, and execute with ./equalpaths_tests`

##### bst-test
(1) Ensure you are in the `hw4` directory

(2) Run `make bst-test` to compile and link all files for the implementation of the Binary Search Tree

(3) Enter `./bst-test` to create the executable `bst-test`

(4) Run the test by entering `./bst-test` in your terminal

(5) Enter `valgrind --tool=memcheck --leak-check=yes ./bst-test` to check for memory loss/leaks

`Note: run more intensive tests by navigating to hw4_tests/bst_tests, run make bsts_tests, and execute with ./bst_tests`