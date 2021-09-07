# Rubik's Cube Solver
This is a Rubik's Cube solver that uses Thistlewaite's algorithm to solve the cube and openCV to get input from a webcam.

# Thistlewaite's Algorithm
Thistlewaite's algorithm is an algorithm designed by Morwen B. Thistelwaite that allows a Rubik's Cube to be programatically solved in under 45 moves (with the average number of moves being around 30). The algorithm works by moving the cube from one group to another, with each group having less available moves, restricting the cube to fewer and fewer possibilities until it is solved. The current solver takes about 40 seconds to find a solution.

Cube Groups:

1) G0 = <L, R, F, B, U, D> is a group that contains any possible Rubik's cube state and allows all moves (18 in total). This group contains 4.33 x 10^19 positions so solving a cube using brute force from this state would take too long. To reduce the possible cube states we can move the cube to G1 by orienting all the edge facelets correctly. An edge facelet is said to be oriented if it can reached the solved state without front and back quarter turns.

2) G1 = <L, R, F2, B2, U, D> contains 2.11 x 10^16 possible positions and allows 14 moves in total (no F and B quarter turns as they affect edge orientation). In this phase we orient the corners and move the edges to the correct slice tp reach G2. A corner is oriented if the facelet is on the the solved face or the opposite face.

3) G2 = <L2, R2, F2, B2, U, D> contains 1.95 x 10^10 possibles positions and allows 10 moves moves (no more L and R quarter turns as they affect corner orientation. In this phase we move from G2 to G3 by moving the cube into 1 of the 96 permisible corner orbits to allow the cube to be half turn solvable.

4) G3 = <L2, R2, F2, B2, U2, D2> contains 6.63 x 10^5 permuations and allows only half turns (6 moves total). From this group we can reach the solved state G4 = Solved Cube.

Pattern Databases:

To get from one group to another the cube is masked for important facelets and then iteratively deepening depth first search (IDDFS) is used to search for the set of moves to reach the target state. However only using IDDFS is still not efficient enough so pruning tables are used as a heuristic to exit unfruitful searches early. The tables are generated before each phase at a certain depth and are then consulted during IDDFS. 

# Computer Vision For Input
To get input from the webcam openCV is used. The most difficult aspect of of getting input was differentiating between different colors in the images. To help with this the images are preprocessed by being blurred and converted to the HSV color space. HSV is used over RGB as it only has one channel (Hue channel) dedicated to color making it easier to adjust for different colors. However, different lighting condtions reflect different HSV values for each color. To get accurate HSV values data was collected for four different lighting conditions. 

<p align="center">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/dark.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/regular.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/bright.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/very_bright.png">
</p>


<p align="center">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/dark_HSV.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/regular_HSV.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/bright_HSV.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/very_bright_HSV.png">
</p>


<p align="center">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/dark_mask.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/regular_mask.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/bright_mask.png">
  <img width="230" height="230" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/very_bright_mask.png">
</p>

Rubik's cube in differnt lighting conditions. The first row contains the cube in RGB, the second contains the cube converted to the HSV color space and the third row shows the cube masked with the blue HSV color values ([90 140], [30 255], [20 255]).

Once all the HSV values were collected getting the cube faces was trivial as all that was required was cropping the facelets from input images from the webcam. From there the starting cube can be initialized and the moves can be drawn on the webcam stream to solve the cube.

# Demo
1) The starting cube is first initialized.

<p align="center">
  <img width="600" height="381" src="https://github.com/Hamoudi0427/Rubiks_solver/blob/master/Test_Demo/cube_init.gif">
</p>

2) The solution is the calculated using the algorithm described above.
