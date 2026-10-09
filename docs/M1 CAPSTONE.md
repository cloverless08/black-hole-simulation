# Capstone Project Ideas

## Project Idea 1: Real-Time Black Hole Renderer

My first—and preferred—idea for a capstone project this semester is a fairly complicated one: I want to make a CPU-based software renderer that accurately and visually represents a black hole in real time. The output should be a live window with a camera that can move in three dimensions, and it should include realistic representations of phenomena like accretion disks, gravitational lensing, and the Schwarzschild radius of the hole.

### 1. Algorithms

The program will use algorithms to calculate the color value for each pixel in a window based on real scientific equations and the generated data and objects in the simulation, such as the location and radius of the black hole, light rays, and the starfield.

### 2. UML Diagram

Naturally, my UML diagram will show the relevant flow of user input, visual output, and the calculations in between, cleanly illustrating the components of the program to a viewer.

### 3. Input and Output (I/O)

The program will utilize I/O in a few key ways. The user will interact with the program using the keyboard. The arrow keys will be used to move a camera around the black hole in three dimensions, allowing the user to fully interact with the simulation and view it from many interesting angles. Other key presses may also invoke useful program functions, like pause, exit, or "print."

The program will also use the console for several different kinds of output. Helpful system output lines, debug information, critical errors and warnings, and a compact representation of the on-screen data may be output to the terminal at various points during execution.

### 4. Variables

A large number of variables will be needed in this project for all sorts of data. Most notably, the camera's location and movement will be stored in formats such as pitch, yaw, and rotation. The data for the black hole itself will be held in variables, with relevant data points like radius, mass, coordinate location, and other properties stored.

The window resolution and behavior will be represented by immutable variables established at compile time. During the program loop, the RGBA and coordinate values (normalized or standard) for each pixel will need to be stored in variables so that they can be properly evaluated.

### 5. Arrays

Arrays play an essential and vital role in this program. The calculations for the pixel values will eventually write to a vector (technically an array, just resizable) that will act as the pixel buffer, storing the individual values before they are passed as a whole array to the window for the GPU to draw using the SDL2 library.

It is important to note that the full calculations and the resulting values will all be generated in pure C++. The GPU library will only be used to simplify and optimize the rendering of that data to the screen, which remains a fairly trivial part of the larger program.

### 6. File I/O

File I/O is trickier to implement due to the idealized nature of this project. However, it can be added in the form of a key that captures the current frame of the simulation and outputs it to an image file, essentially acting as a built-in screenshot function. This may also be utilized for other file formats if I have time.

### 7. Loops

The core part of the project will rely on a frame loop. This is where the calculations and read/write operations for the pixel buffer will take place, as the program needs to repeat the same kind of job for every pixel in every frame.

The main render loop will take the values of the camera position and data from the black hole and use formulas to determine what each pixel should look like to represent the simulation.

### 8. Interaction

Interaction mainly reiterates what I mentioned in the "Input and Output" section, but it stands alone in its own way.

The user will be able to move a 3D camera around the simulated scene, observe the visual simulation, and change real values that have an active and immediate effect on the simulation. These values may include the measurements of the black hole, simulation resolution, random number generator (RNG) seed, and performance settings.

### 9. Control Statements

Control statements will be used throughout the program to make decisions based on user input, simulation data, and calculated values.

For example, `if` statements can determine whether a ray of light has crossed the Schwarzschild radius, whether a pixel should display a star, the accretion disk, or the black hole itself, and whether the user has changed a simulation setting.

`switch` statements can also be used to handle different keyboard inputs and program modes, such as pausing the simulation, changing settings, taking a screenshot, or exiting the program.

These control structures will allow the program to respond dynamically to both the user and the results of its calculations.

---

## Project Idea 2: Lossless File Compression Algorithm

My second idea will act mainly as a fallback in case my first project ends up being out of my scope this semester. I plan on making a lossless and efficient file compression algorithm for any file type.

### 1. Algorithms

The compression and decompression processes will be based on algorithms that analyze the data in a file and represent it more efficiently.

I will investigate existing lossless compression techniques, such as Huffman coding, run-length encoding, or another appropriate algorithm, and implement the chosen method in C++. The program will need to determine how the original data can be represented using fewer bits and then reverse those calculations during decompression so that the original file can be recovered exactly.

### 2. UML Diagram

My UML diagram will show the major components of the compression program and how they interact with each other. This could include components for reading the original file, analyzing its data, generating the compressed representation, writing the compressed file, and performing the reverse process during decompression.

The diagram will help illustrate the overall structure and flow of the program before and during development.

### 3. Input and Output (I/O)

The primary input to the program will be a file selected by the user for compression or decompression. The program will read the contents of that file and process its data.

The output will be a new compressed file containing the encoded data and any information necessary to decompress it later. The program can also provide console output showing information such as the original file size, compressed file size, compression ratio, and whether the operation was successful.

### 4. Variables

The program will require variables to store many different types of information. These could include individual bytes or characters being processed, frequencies of different values within the file, the sizes of the original and compressed files, compression ratios, file paths, and data used by the compression algorithm.

If I use a tree-based algorithm such as Huffman coding, variables and objects will also be needed to represent nodes, frequencies, and relationships within the tree.

### 5. Arrays

Arrays will be important because the program will be working directly with large amounts of file data. The contents of the input file can be stored in an array or vector of bytes while they are being analyzed and compressed.

Arrays can also be used to store frequency information for different byte values and the encoded data produced by the compression algorithm. Using vectors will allow the program to efficiently store and manipulate variable amounts of data.

### 6. File I/O

File I/O will be one of the most important parts of this project. The program will need to open and read an existing file, process its contents, and then create and write a new compressed file.

The decompression portion will perform the reverse process by reading the compressed file and reconstructing the original data. I will also need to investigate how to store information about the compression method in the compressed file so that the program knows how to correctly decompress it.

### 7. Loops

Loops will be essential because the program will need to process potentially thousands or millions of pieces of data within a file.

For example, a loop could iterate through every byte in the input file to determine how frequently each value occurs. Additional loops will be used to encode the data, write the compressed data to a file, and process the data again during decompression.

The number of iterations will depend on the size of the file being processed.

### 8. Interaction

The user will interact with the program primarily through the console. They will be able to select whether they want to compress or decompress a file and provide the relevant file path or filename.

The program can then display the progress and results of the operation, including the original size, compressed size, and compression ratio. I may also allow the user to choose settings such as the compression algorithm or output filename if those features are practical within the scope of the project.

### 9. Control Statements

Control statements will allow the program to make decisions based on the data it is processing and the actions requested by the user.

For example, `if` statements can determine whether the user wants to compress or decompress a file, whether a file was successfully opened, or whether a particular byte or symbol meets a condition required by the compression algorithm.

`switch` statements could be used to handle different user-selected operations or program options. Control structures will also be important during decompression because the program must decide how to interpret each piece of encoded data and determine when the original file has been completely reconstructed.
