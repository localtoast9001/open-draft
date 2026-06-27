# Java Reference Implementation

Java reference implementation and shared libs.

## Style Checking

Java style is enforced with Checkstyle using the built-in Sun checks.

Run style checks:

```bash
cmake -S java -B java/build
cmake --build java/build --target checkstyle
```

The checkstyle runner script is:

```bash
./java/run-checkstyle.sh
```
