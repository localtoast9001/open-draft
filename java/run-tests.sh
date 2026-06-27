#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build/test-classes"

mkdir -p "${BUILD_DIR}"

mapfile -t JAVA_SOURCES < <(find "${SCRIPT_DIR}/src" "${SCRIPT_DIR}/test" -type f -name "*.java" | sort)
if [[ ${#JAVA_SOURCES[@]} -eq 0 ]]; then
  echo "No Java sources found under java/src or java/test."
  exit 0
fi

javac -d "${BUILD_DIR}" "${JAVA_SOURCES[@]}"

mapfile -t TEST_FILES < <(find "${SCRIPT_DIR}/test" -type f -name "*Test.java" | sort)
if [[ ${#TEST_FILES[@]} -eq 0 ]]; then
  echo "No Java test classes found under java/test."
  exit 0
fi

echo "Running Java test classes:"
printf '%s\n' "${TEST_FILES[@]}"

for test_file in "${TEST_FILES[@]}"; do
  test_class="${test_file#${SCRIPT_DIR}/test/}"
  test_class="${test_class//\//.}"
  test_class="${test_class%.java}"
  java -cp "${BUILD_DIR}" "${test_class}"
done
