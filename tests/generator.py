import sys
import random
import bisect

def generate_test_files(test_filename, ans_test_filename, num_keys, num_queries, key_range):
    commands = []
    
    keys = random.sample(range(key_range[0], key_range[1]), num_keys)
    for key in keys:
        commands.append(f'k {key}')
    
    for i in range(num_queries):
        a = random.randint(key_range[0], key_range[1])
        b = random.randint(key_range[0], key_range[1])
        left, right = (a, b)
        commands.append(f'q {left} {right}')
    
    random.shuffle(commands)
    
    with open(test_filename, "w") as f:
        for cmd in commands:
            f.write(cmd + "\n")

    sorted_keys = []
    with open(ans_test_filename, "w") as ansf:
        for line in commands:
            parts = line.strip().split()
            op = parts[0]
            if op == 'k':
                key = int(parts[1])
                bisect.insort(sorted_keys, key)
            elif op == 'q':
                left = int(parts[1])
                right = int(parts[2])
                if left > right:
                    count = 0
                else:
                    left_index = bisect.bisect_left(sorted_keys, left)
                    right_index = bisect.bisect_right(sorted_keys, right)
                    count = right_index - left_index
                ansf.write(str(count) + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage:\n  python generator.py <number of test>")
        sys.exit(1)

    test_filename = "test_files/test_input" + sys.argv[1] + ".txt"
    test_ans_filename = "ans_files/test_output" + sys.argv[1] + ".txt"
    
    generate_test_files(test_filename, test_ans_filename, num_keys=random.randrange(0, 1000), 
                        num_queries=random.randrange(0, 500), key_range=(0, random.randrange(1, 10000)))