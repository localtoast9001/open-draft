#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

CHECKSTYLE_VERSION="10.17.0"
CHECKSTYLE_DIR="${ROOT_DIR}/out/tools/checkstyle"
CHECKSTYLE_JAR="${CHECKSTYLE_DIR}/checkstyle-${CHECKSTYLE_VERSION}-all.jar"
CHECKSTYLE_URL="https://github.com/checkstyle/checkstyle/releases/download/checkstyle-${CHECKSTYLE_VERSION}/checkstyle-${CHECKSTYLE_VERSION}-all.jar"
CHECKSTYLE_CONFIG="${SCRIPT_DIR}/config/checkstyle-sun.xml"

mkdir -p "${CHECKSTYLE_DIR}"

if [[ ! -f "${CHECKSTYLE_JAR}" ]]; then
  echo "Downloading Checkstyle ${CHECKSTYLE_VERSION}..."
  if command -v curl >/dev/null 2>&1; then
    curl -fsSL "${CHECKSTYLE_URL}" -o "${CHECKSTYLE_JAR}"
  elif command -v wget >/dev/null 2>&1; then
    wget -q "${CHECKSTYLE_URL}" -O "${CHECKSTYLE_JAR}"
  else
    echo "Error: neither curl nor wget is installed; cannot download Checkstyle." >&2
    exit 1
  fi
fi

mapfile -t JAVA_FILES < <(find "${SCRIPT_DIR}/src" "${SCRIPT_DIR}/test" -type f -name "*.java" | sort)

if [[ ${#JAVA_FILES[@]} -eq 0 ]]; then
  echo "No Java files found under java/src or java/test. Skipping Checkstyle."
  exit 0
fi

echo "Running Checkstyle (Sun style) on ${#JAVA_FILES[@]} Java file(s)..."
java -jar "${CHECKSTYLE_JAR}" -c "${CHECKSTYLE_CONFIG}" "${JAVA_FILES[@]}"
