#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

RUN_ID="$(date -u +%Y%m%dT%H%M%SZ)"
LOG_ROOT_DIR="${ROOT_DIR}/out/logs/net"
RUN_DIR="${LOG_ROOT_DIR}/${RUN_ID}"
RESULTS_DIR="${RUN_DIR}/test-results"
SUMMARY_FILE="${RUN_DIR}/dotnet-test.log"

mkdir -p "${RESULTS_DIR}"

echo "Run ID: ${RUN_ID}"
echo "Log root: ${LOG_ROOT_DIR}"
echo "Run output: ${RUN_DIR}"
echo "Results directory: ${RESULTS_DIR}"

set -o pipefail
dotnet test "${SCRIPT_DIR}/OpenDraft.slnx" \
  --results-directory "${RESULTS_DIR}" \
  --logger "trx" \
  --collect:"XPlat Code Coverage" \
  "$@" \
  -- DataCollectionRunSettings.DataCollectors.DataCollector.Configuration.Format=cobertura \
  | tee "${SUMMARY_FILE}"

COVERAGE_COUNT="$(find "${RESULTS_DIR}" -type f -name 'coverage.cobertura.xml' | wc -l | tr -d ' ')"
TRX_COUNT="$(find "${RESULTS_DIR}" -type f -name '*.trx' | wc -l | tr -d ' ')"

echo ""
echo "Artifacts summary:"
echo "- Test log: ${SUMMARY_FILE}"
echo "- TRX files: ${TRX_COUNT}"
echo "- Coverage files (Cobertura): ${COVERAGE_COUNT}"
echo ""
echo "Coverage file paths:"
find "${RESULTS_DIR}" -type f -name 'coverage.cobertura.xml' -print

echo ""
echo "Done."
