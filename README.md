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

Binaryfuck programs starts with an 1

### Brainfuck to Binaryfuck Coverter
	python3 BFconverter.py brainfuck_path binaryfuck_path

### Interpreter
After compiling, run:
 
	./binaryfuck source.bf [-m memory_size]

### Compiler

## Perfomance

mandelbrot.bf: 
	
	       82.03 real        80.31 user         0.30 sys