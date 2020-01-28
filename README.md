# OOD-Design
Practice project with object oriented programming. Abstracting a concrete application about shipment logistics into classes with distinct responsibility.

S.O.L.I.D. design principles were used to maximize extendability, testability, and robustness despite change.
Used test automation framework Catch in a TDD manner to ensure program correctness. 

Below is a high level description of what each class expects and is responsible to output.

**ArgsParser**

Parses the command line input for a file name, where the data is coming from. 
Expected use: ./main shipmentStats.csv, or ./main -f shipmentStats.csv would check for whether that file exists in the directory. If it does, pass the name on to Reader. If not, report an error, and exit the program.

ArgsParser is helpful because, 
- if there were several different files containing similar shipmentStats.csv data, e.g. one for China -> Hong Kong -> USA -> Canada and another for, say, Vietnam -> Philippines -> Mexico -> Canada, it’d be convenient for the user to switch the file names to analyze different datasets.
- if a garbage name is entered by the user, the program can stop execution right away.

**Reader**

Program enters this stage, after having accepted a valid file name from ArgsParser.
The reader 
1. reads from file.
2. adapt the data into a format that the calculator expects. In the case of this assignment, I’m going to populate an 	array where each element of the array corresponds to a row- with auxiliary information to help with calculations.
3. in case of invalid rows, like a row with an empty cell, skip the row and move on to the next.
3. return this properly adapted data, in a format that’s easy for the calculator to work on.

**Calculator**

Program enters this stage, after having accepted the adapted data from Reader. 
1. The calculator performs the necessary calculations, using the data from reader.
2. The calculator should return the results in a predefined order/format, such that it’s easy for the Writer to work on. 

**Writer**

Program enters this stage, after having accepted results from Calculator, in a format that is efficient to access/work on. 

Writer is composed of **Formatter** rather than an __inheritance__ of Formatter. 
We choose composition over inheritance here because, in this context it doesn’t make sense to inherit. Formatter and writer are separate concepts! To inherit would imply there’s some base class that exhibits traits of both a Writer and a Formatter...
Instead, we write a Formatter separately; the Formatter:
	1. Take the results from calculator and organize them in Strings, that adhere to the final expected output.
	2. Return these strings that are in the right format to the Writer.
Once the Writer accepts these strings from Formatter, print the output using those strings.

