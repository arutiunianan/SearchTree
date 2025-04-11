#!/usr/bin/env bash

red="\033[1;31m"
green="\033[1;32m"
usual="\033[0m"

TESTS_DIR=$1/test_files
ANS_DIR=$1/ans_files
TREE_BIN=$2
TESTS_NUM=$3

if [ -d "${TESTS_DIR}" ]; then
  echo -en "${green}[==========]${usual} Running ${TESTS_NUM} tests from 1 test suites.\n"
  echo -en "${green}[----------]${usual} Global test environment set-up.\n"
  FAILED_TESTS=()
  PASSED_TESTS_NUM=0
  echo -en "${green}[----------]${usual} ${TESTS_NUM} tests from Distance\n"

  for ((i = 1; i <= ${TESTS_NUM}; ++i))
  do
    echo -en "${green}[ RUN      ]${usual} Distance.Subtestv_${i}\n"

    TEST_FILE="${TESTS_DIR}/test_input${i}.txt"
    EXPECTED_FILE="${ANS_DIR}/test_output${i}.txt"

    OUTPUT="$(cat "$TEST_FILE" | "$TREE_BIN")"
    EXPECTED_OUTPUT="$(cat "$EXPECTED_FILE")"
    DIFF="$(diff <(echo "$OUTPUT") "$EXPECTED_FILE")"

    #if [ -n "$DIFF" ]; then
    if ! [ "$?" -eq 0 ]; then
      echo -en "Failure\n"
      echo -en "  Actual: ${OUTPUT}\n"
      echo -en "Expected: ${EXPECTED_OUTPUT}\n\n"
      echo -en "${red}[  FAILED  ]${usual} Distance.Subtestv_${i}\n"

      FAILED_TESTS_FILES+=("Distance.Subtestv_${i}")
    else
      echo -en "${green}[       OK ]${usual} Distance.Subtestv_${i}\n"
      ((PASSED_TESTS_NUM++))
    fi
  done

  echo -en "${green}[----------]${usual} Global test environment tear-down\n"
  echo -en "${green}[==========]${usual} ${TESTS_NUM} tests from 1 test suites ran.\n"
  echo -en "${green}[  PASSED  ]${usual} ${PASSED_TESTS_NUM} tests.\n"

  if [ ${#FAILED_TESTS_FILES[@]} -ne 0 ]; then
    echo -en "${red}[  FAILED  ]${usual} ${#FAILED_TESTS_FILES[@]} tests, listed below:\n"
      for test in "${FAILED_TESTS_FILES[@]}"; do
        echo -en "${red}[  FAILED  ]${usual} ${test}\n"
      done
    exit 1
  else
    exit 0
  fi
else
  echo -en "${red}Test directory does not exist${usual}\n"
  exit 1
fi