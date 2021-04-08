# Task: 
implement a container that stores a sequence of integers.

Initially, the container does not contain numbers (i.e. the sequence has zero length).
The container must support the following operations :
	
1. Insert element at position i. It is guaranteed that i <= size, i.e. the new element is inserted at the beginning, middle or end of the sequence, but not at any position beyond. When inserting, all old elements from the i-th position must be shifted to the right.

	Example :
	
	sequence :	1 2 3 4 5
	
	operation :	insert 0 at position 2
	
	result :	1 2 0 3 4 5

2.  Delete an element from position i. It is guaranteed that i < size, i.e. an existing element is deleted. Other old elements after the deleted one should be shifted to the left.

	Example :
	sequence :	1 2 3 4 5
	operation :	delete from position 2
	result :	1 2 4 5
  
3. Get the value of the element at position i (in two variants: as a constant reference or as a reference allowing to overwrite the value).

	4. Find out current size - size().

	5. Check for empty - empty().

	6. Clear - clear().

7. Calculate the sum on the range from l to r.
	Performance test :
  
	As performance tests of the resulting container will be a sequence of a random set of commands of the above types. The input data will have the following form :
		In the first line an integer N is the number of commands.
		In the next N lines of commands, each of which begins with an integer - operation numbers (numbered as in the description below). Additional numbers describing the arguments of the command may follow.
    
		For example :
			1 i x - insert number x at position i, don't output anything to the console
			2 i - delete number from position i, don't output anything to the console
			3 i x - assign value x to the number at i - that position, don't output anything to the console
			4 - display the size of the sequence on the console
			5 - print 1 if the sequence is empty, or 0 otherwise
			6 - clear the sequence, do not output anything to the console
			7 l r - print to the console the sum of numbers from l-th position to r-th position inclusive.
			Additionally there will be the command 0:
			0 i - print the number at the i-th position to the console
      
	The appearance of each command in the test sequence is equal probability, but it is guaranteed that the input data is correct (for example, we are not asked to remove a non-existent number).
  
  You need to optimize the average running time of the program.
Implementation:
	Before we implement any fast solution, I suggest making a couple of simple working variants, with which we can then compare our solution in terms of speed.
	For example, we can implement storing all sequence elements in std::vector or std::list.
