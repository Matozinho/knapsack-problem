# knapsack-problem

It solves the 0/1 knapsack problem with `greedy` (default) and `brute-force` strategies.

## Environment

you will need the [xmake](https://xmake.io/#/) to build and link all the libraries and gcc-12 or greater to run it.

## Runing

The repo already have the assets folder with possible inputs.

To **test** the code run

```
xmake && xmake r test
```

To run the **benchmark**

```bash
xmake && xmake r bench
```

To run **any arbitrary input file**

```bash
xmake && xmake r knapsack -f <path-to-file> -<b|g>
```

## Examples

```bash
xmake && xmake r knapsack -f assets/Mochila10.txt -b # will solve with brute force
```


```bash
xmake && xmake r knapsack -f assets/Mochila10.txt -b # will solve with greedy strategy
```
