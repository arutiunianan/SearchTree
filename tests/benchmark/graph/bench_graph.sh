#!/usr/bin/env bash

BENCH_BIN=$1

${BENCH_BIN} --benchmark_out=results.json --benchmark_out_format=json
python3 graph.py results.json $2 $3