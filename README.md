# Anishka's Search tree

## What does it do?

This project is my implementation of an AVL tree, a height-balanced binary search tree!

## What is the working principle?

### Node addition algorithm

<ol>
 <li>Follow the search path until we are sure that the key is not in the tree.</li>
 <li>Adding a new node to the tree.</li>
 <li>We "step back" along the path of searching and checking at each node of the balance indicator. If necessary — balancing.</li>
</ol>

### Node removal algorithm
<ul>
 <li>If the node is a leaf:</li>
  <ol>
   <li> Deleting a node. </li>
  </ol>
 <li>Else if the node does not have a left(right) child:</li>
  <ol>
   <li> Replacing the node with its right (left) child. </li>
  </ol>
 <li>Else:</li>
  <ol>
   <li> Finding the rightmost node in the left subtree.  </li>
   <li> Moving this node to the place of the node being deleted. </li>
   <li> Deleting the necessary node. </li>
  </ol>
</ul>
After all the actions, if necessary, we do the balancing of the tree.

### Balancing

There are 4 types of rotations used for balancing:

<ul>
 <li> Small left rotation (the height difference of the L-subtree and the b-subtree is 2 and height C <= height R):

 <image src="https://upload.wikimedia.org/wikipedia/ru/b/bc/AVL_LR.GIF" width=300px></li>

 <li> Large left rotation (the height difference of the L-subtree and the b-subtree is 2 and the height of the c-subtree is > the height of R):

 <image src="https://upload.wikimedia.org/wikipedia/ru/1/16/AVL_BR.GIF" width=300px></li>

 <li> Small right rotation (the height difference of the R-subtree and the b-subtree is 2 and height C <= height L):

 <image src="https://upload.wikimedia.org/wikipedia/ru/e/e8/AVL_LL.GIF" width=300px></li>

 <li> Large right rotation (the height difference of the R-subtree and the b-subtree is 2 and the height of the c-subtree is > the height of L):

 <image src="https://upload.wikimedia.org/wikipedia/ru/7/74/AVL_BL.GIF" width=300px></li>


## How do I run the program?

```
cmake -S . -B build (-DBENCHMARK=ON)
```

To build a project:

```
cmake --build build
```

To run manual input and tests, respectively:

```
./build/matrix
ctest --output-on-failure --test-dir build
./build/tests/benchmark/benchmarkex
```

To run benchmark graphs that compare with std::set:

```
cmake --build build --target bench_graph
```

## What does the result of the program look like?

To solve this task:
<ul>
 <li> Keys(k) and requests(q) are received. </li>
 <li> Each request is a pair of two possible keys. It makes sense if the second one is greater than the first one, otherwise the answer is zero. </li>
 <li>For each query, you need to count the number of keys in the tree, such that they all lie strictly between its left and right borders, inclusive. </li>
</ul>

Program input data:

```
k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40
```

Program output data:

```
2 0 3
```

To check the speed of my tree, I used a test generator:

```
python generator.py <number of test>
```

And based on these tests, I got the following results, which I compared with std::set:

<image src="for_readme/graph.png" width=500px>

Yeeeeeeeee, I managed to do it faster than in the standard library.