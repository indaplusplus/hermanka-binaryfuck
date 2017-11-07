import sys
import os

if len(sys.argv) != 3:
    print("Usage: python3", sys.argv[0], "brainfuck_path", "binaryfuck_path")
    sys.exit(0)

brainf = sys.argv[1]
binf = sys.argv[2]

output = ["1"]
for line in open(os.path.join(os.getcwd(), brainf), 'r'):
    for char in line:
        if char == '+':
            output.append("000")
        if char == '-':
            output.append("001")
        if char == '>':
            output.append("010")
        if char == '<':
            output.append("011")
        if char == '.':
            output.append("100")
        if char == ',':
            output.append("101")
        if char == '[':
            output.append("110")
        if char == ']':
            output.append("111")

with open(os.path.join(os.getcwd(), binf), 'w') as f:
    f.write("".join(output))
