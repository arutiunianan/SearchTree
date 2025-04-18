import sys
import os
import re
import json
import matplotlib.pyplot as plt

def count_lines_in_tests(dir_path: str) -> dict[int, int]:
    pattern = re.compile(r'^test_input(\d+)\.txt$')
    line_counts: dict[int, int] = {}

    for fname in os.listdir(dir_path):
        m = pattern.match(fname)
        if not m:
            continue
        test_num = int(m.group(1))
        full_path = os.path.join(dir_path, fname)
        with open(full_path, 'r', encoding='utf-8') as f:
            cnt = sum(1 for _ in f)
        line_counts[test_num] = cnt

    return line_counts

if len(sys.argv) < 3:
    print("Usage:\n  python graph.py <json file> <tests dir> <output dir>")
    sys.exit(1)
elif len(sys.argv) == 3:
    BENCH_JSON = 'results_example.json'
    TEST_DIR   = sys.argv[1]
    OUTPUT_DIR = sys.argv[2]
else:
    BENCH_JSON = sys.argv[1]
    TEST_DIR   = sys.argv[2]
    OUTPUT_DIR = sys.argv[3]

with open(BENCH_JSON, 'r', encoding='utf-8') as f:
    data = json.load(f)

avl_times: dict[int, float] = {}
sset_times: dict[int, float] = {}
for bm in data['benchmarks']:
    tree_type, test_name, _ = bm['name'].split('/')
    test_num = int(test_name.replace('TEST', ''))
    real_time = bm['real_time']
    if tree_type == 'AVLTree':
        avl_times[test_num] = real_time
    elif tree_type == 'std::set':
        sset_times[test_num] = real_time

line_counts = count_lines_in_tests(TEST_DIR)

avl_points = sorted(
    (line_counts[num], time)
    for num, time in avl_times.items()
    if num in line_counts
)
set_points = sorted(
    (line_counts[num], time)
    for num, time in sset_times.items()
    if num in line_counts
)

x_avl, y_avl = zip(*avl_points) if avl_points else ([], [])
x_set,  y_set  = zip(*set_points) if set_points else ([], [])

plt.figure()
plt.plot(x_avl, y_avl, label='AVLTree')
plt.plot(x_set,  y_set,  label='std::set')
plt.xlabel('Number of elements')
plt.ylabel('Execution time, ns')
plt.title('Comparison of execution time')
plt.legend()
plt.tight_layout()
plt.savefig(OUTPUT_DIR + "/graph.png")
