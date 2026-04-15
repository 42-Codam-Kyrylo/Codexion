# Codexion Testing Suite

This document contains the test cases for the Codexion project, categorized by difficulty levels as per the evaluation requirements.

## 🟢 Level 1: Easy
**Focus:** Basic functionality, large-scale stability, and successful completion.
**Constraints:**
- Maximum 200 coders.
- Timing values must be $\ge$ 60ms.

| Test Case | Command | Expected Outcome |
| :--- | :--- | :--- |
| **Basic Success (Small)** | `./codexion 4 3000 200 200 200 5 0 fifo` | All 4 coders complete 5 compiles. No one burns out. |
| **Large Scale (200 Coders)** | `./codexion 200 5000 100 100 100 2 0 edf` | 200 threads run without crashing. All reach 2 compiles. |
| **No Cooldown Success** | `./codexion 10 2000 300 100 100 3 0 fifo` | Quick turnover, all coders finish their quota comfortably. |
| **High Debug/Refactor** | `./codexion 5 4000 200 1000 1000 2 50 edf` | Long non-critical phases. All coders finish. |

---

## 🟡 Level 2: Less Easy
**Focus:** Burnout logic, timing precision, and resource integrity.
**Goals:**
- Validate burnout edge cases.
- Verify logging and timing tolerances ($\le$ 10ms variance).
- Ensure no dongle duplication and correct state transitions.

| Test Case | Command | Expected Outcome |
| :--- | :--- | :--- |
| **Immediate Burnout** | `./codexion 3 100 500 100 100 5 0 fifo` | A coder burns out almost immediately because `time_to_burnout` < `time_to_compile`. |
| **Tight Success** | `./codexion 2 1000 400 100 100 2 0 edf` | Very tight window. Should succeed if scheduling is efficient. |
| **Timing Tolerance** | `./codexion 3 500 600 100 100 1 0 fifo` | Coder 1 takes dongles at ~0ms. Coder 2 should burn out at ~500ms. Verify log timestamp is 500-510ms. |
| **State Transitions** | `./codexion 2 2000 200 200 200 1 0 fifo` | Check logs for order: `taken a dongle` (x2) -> `is compiling` -> `is debugging` -> `is refactoring`. |
| **Dongle Integrity** | `./codexion 10 5000 500 100 100 5 0 fifo` | Check that at any time $T$, the number of coders "compiling" is $\le$ `number_of_coders / 2`. |

---

## 🔴 Level 3: Medium
**Focus:** Cooldown behavior, scheduler logic, and stress testing.
**Goals:**
- Verify cooldown behavior (gaps between dongle usage).
- Test scheduler differences (`edf` vs `fifo`).
- Validate refactoring timing and log serialization.

| Test Case | Command | Expected Outcome |
| :--- | :--- | :--- |
| **Cooldown Enforcement** | `./codexion 2 5000 500 100 100 2 1000 fifo` | Gap between "X released dongles" and "Y taken a dongle" (same dongle) must be $\ge$ 1000ms. |
| **FIFO vs EDF (Fairness)**| `./codexion 5 3000 600 100 100 2 0 [fifo/edf]` | Feasible test. Both schedulers should complete successfully. *Note: In this implementation, FIFO and EDF produce identical ordering because the interval between compiles is a constant (C+D+R).* |
| **Refactor Timing** | `./codexion 2 5000 200 200 1000 2 0 fifo` | Verify that the "is refactoring" phase actually lasts ~1000ms before the next cycle. |
| **Log Serialization** | `./codexion 100 5000 100 100 100 5 10 edf` | Under high concurrency, ensure no lines are garbled or merged. Each log should be distinct. |
| **Starvation Test** | `./codexion 3 2000 1000 100 100 5 0 fifo` | With 3 coders and only 3 dongles, only one can compile at a time. Verify others wait fairly. |

---

## 🛠 Validation Commands

### Memory Leaks
```bash
valgrind --leak-check=full --show-leak-kinds=all ./codexion 4 3000 200 200 200 2 0 fifo
```

### Data Races
```bash
valgrind --tool=helgrind ./codexion 4 3000 200 200 200 2 0 edf
```

### Performance Check (Stress)
```bash
time ./codexion 200 10000 60 60 60 10 0 edf
```
