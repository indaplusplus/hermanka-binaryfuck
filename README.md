# Binaryfuck

Interpreter ~~and compiler~~ for binaryfuck.

| Binaryfuck | Brainfuck | Effect 
| :--------: | :-------: | :-----
| 000        | +         | Increment value at current pointer position
| 001        | -         | Decrement value at current pointer position
| 010        | >         | Move pointer one step to the right
| 011        | <         | Move pointer one step to the left
| 100        | .         | Output character on current pointer position
| 101        | ,         | Input character to current pointer position
| 110        | [         | Jump past matching ] if pointer value is 0
| 111        | ]         | Jump to matching [ if pointer value is not 0

Binaryfuck programs starts with an 1.

### Brainfuck to Binaryfuck Coverter
	python3 BFconverter.py brainfuck_path binaryfuck_path

### Interpreter
After compiling, run:
 
	./binaryfuck source.bf [-m memory_size]
	
Default memory size is 256 slots.

### Compiler

## Perfomance

### Interpreter
mandelbrot.bf: 
	
	81.09 real        79.66 user         0.26 sys
	     
On a better computer:

	35.81 user   0.00 system   0:35.82 elapsed  	
Optimized:

	33.39 real        32.09 user         0.14 sys	
