# .Net Reference Implementation

.Net reference implementation and shared libraries.

## Prerequisites

- .NET SDK from `global.json`

## Build

```bash
cd net
dotnet restore
dotnet build
```

## Test With Coverage

Run all .NET tests and collect coverage:

```bash
./net/test.sh
```

Pass additional `dotnet test` arguments through the script:

```bash
./net/test.sh --filter "MessageTests"
```

## Output

Each run writes timestamped artifacts under:

```text
out/logs/net/<UTC timestamp>/
```

Artifacts include:

- `dotnet-test.log` (console output)
- `test-results/*.trx` (test result files)
- `test-results/**/coverage.cobertura.xml` (coverage files)