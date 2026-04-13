# Codexion

Master the race for resources before the deadline masters you.

Summary: Race against time in this thrilling concurrency challenge. Orchestrate multiple coders competing for limited USB dongles using POSIX threads, mutexes, and smart scheduling. Master resource synchronization before burnout strikes.

Version: 1.1

## Contents

1. Introduction
2. AI Instructions
3. Common Instructions
4. Overview
5. Global rules
6. Mandatory part
7. Readme Requirements
8. Submission and peer-evaluation

## Chapter I - Introduction

Computer programming (often simply called coding) is the process of designing and building executable software to accomplish specific computing tasks. It involves analysis, generating algorithms, profiling algorithms' accuracy and resource consumption, and implementing these algorithms in a chosen programming language.

Coding culture extends beyond the purely technical. It blends problem-solving, creativity, and collaboration in shared environments ranging from open-source communities to co-working spaces and hackathons. Within these hubs, coders not only write code but also debug, refactor, and share tools. Some resources are plentiful, while others, like specialized hardware dongles, are limited and must be shared carefully.

Modern software work is collaborative and concurrent. This simulation models coders in a shared space who need two rare USB dongles to compile quantum code. They must coordinate, avoid deadlocks, and prevent burnout.

## Chapter II - AI Instructions

### Context

During your learning journey, AI can assist with many tasks. Explore its capabilities, but use it critically. Whether it is code, documentation, ideas, or technical explanations, generated output can be incorrect or incomplete. Peer feedback helps avoid mistakes and blind spots.

### Main message

- Use AI to reduce repetitive or tedious tasks.
- Develop prompting skills (coding and non-coding) that will benefit your career.
- Learn how AI systems work to anticipate risks, biases, and ethical issues.
- Keep building technical and power skills with peers.
- Only use AI-generated content that you fully understand and can defend.

### Learner rules

- Explore AI tools and understand how they work to use them ethically and reduce bias.
- Reflect on your problem before prompting to write clearer and more relevant prompts.
- Systematically check, review, question, and test AI-generated output.
- Always seek peer review and do not rely only on self-validation.

### Phase outcomes

- Develop general-purpose and domain-specific prompting skills.
- Improve productivity through effective AI usage.
- Strengthen computational thinking, problem-solving, adaptability, and collaboration.

### Comments and examples

- Exams and evaluations require real understanding, not only working output.
- Explaining your reasoning with peers reveals gaps in understanding.
- AI often lacks local context and can produce generic responses.
- Peers provide alternative perspectives and a quality checkpoint.

Good practice:

I ask AI: "How do I test a sorting function?" It gives ideas. I try them, then review with a peer. We refine the approach together.

Bad practice:

I ask AI to write a whole function and copy-paste it. During peer-evaluation, I cannot explain it and fail the project.

Good practice:

I use AI to help design a parser, then walk through the logic with a peer. We find bugs and rewrite it together.

Bad practice:

I let Copilot generate a key part of my project. It compiles, but I cannot explain pipe handling during evaluation and fail.

## Chapter III - Common Instructions

- Your project must be written in C.
- Your project must follow the Norm. Bonus files/functions are included in norm check, and any norm error results in grade 0.
- Your functions must not quit unexpectedly (segmentation fault, bus error, double free, etc.), except undefined behavior.
- All heap-allocated memory must be properly freed. Memory leaks are not tolerated.
- If required by the subject, submit a Makefile compiling source files with flags `-Wall -Wextra -Werror` using `cc`.
- Your Makefile must not relink unnecessarily.
- Your Makefile must contain at least rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`.
- For bonuses, include a `bonus` rule in Makefile. Bonus code must be in `_bonus.c/.h` files unless otherwise specified.
- If `libft` is allowed, copy its sources and Makefile into a `libft` folder. Your project Makefile must build `libft` first, then your project.
- You are encouraged to create tests (not graded) for self-checking and defense.
- Submit to assigned Git repository. Only repository content is graded.

## Chapter IV - Overview

- One or more coders sit in a circular co-working hub.
- In the center, there is a shared Quantum Compiler.
- Coders alternate between compile, debug, and refactor.
- There are as many USB dongles as coders.
- Compiling requires two dongles simultaneously (left and right).
- After compiling, coder releases dongles, then debugs, then refactors.
- Simulation stops when a coder burns out or when completion criteria are met.
- Coders do not communicate directly.
- Coders do not know if another coder is close to burnout.
- Coders should avoid burnout.

## Chapter V - Global rules

Write one program complying with these rules:

- Global variables are forbidden.
- Program arguments (all mandatory):

`number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler`

- Argument meaning:

1. `number_of_coders`: number of coders and number of dongles.
2. `time_to_burnout` (ms): if coder does not start compiling within this time since simulation start or last compile start, coder burns out.
3. `time_to_compile` (ms): time spent compiling while holding two dongles.
4. `time_to_debug` (ms): time spent debugging.
5. `time_to_refactor` (ms): time spent refactoring before trying to compile again.
6. `number_of_compiles_required`: if all coders compiled at least this many times, simulation stops.
7. `dongle_cooldown` (ms): after release, dongle is unavailable until cooldown expires.
8. `scheduler`: arbitration policy, exactly one of `fifo` or `edf`.

- `fifo`: First In, First Out (earliest request served first).
- `edf`: Earliest Deadline First, deadline = `last_compile_start + time_to_burnout`.

- Coder IDs range from `1` to `number_of_coders`.
- Coder `1` sits next to coder `number_of_coders`.
- Coder `N` sits between `N - 1` and `N + 1`.
- Reject invalid input (negative values, non-integers, invalid scheduler).

### Logging rules

Any state change must be printed as:

- `timestamp_in_ms X has taken a dongle`
- `timestamp_in_ms X is compiling`
- `timestamp_in_ms X is debugging`
- `timestamp_in_ms X is refactoring`
- `timestamp_in_ms X burned out`

Replace `timestamp_in_ms` with current timestamp (ms), and `X` with coder ID.

- Messages must not interleave or mix.
- Burnout message must appear no more than 10 ms after actual burnout.

Example expected format:

```text
0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
402 2 has taken a dongle
403 2 has taken a dongle
403 2 is compiling
603 2 is debugging
803 2 is refactoring
1204 3 burned out
```

Precision note: burnout logs must be within 10 ms of actual burnout. Allow minimal tolerance due to hardware/OS scheduling.

Timing note: CPU usage time can reduce hardware impact, but `gettimeofday()` real-time measurement is acceptable and recommended for this project.

## Chapter VI - Mandatory part

| Field              | Value                                                                                                                                                                                                                                                                                                                                                               |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Program Name       | `codexion`                                                                                                                                                                                                                                                                                                                                                          |
| Files to Submit    | `Makefile`, `*.c`, `*.h` in `coders/`                                                                                                                                                                                                                                                                                                                               |
| Makefile           | `NAME`, `all`, `clean`, `fclean`, `re`                                                                                                                                                                                                                                                                                                                              |
| Arguments          | `number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler`                                                                                                                                                                                                                             |
| External Functions | `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`, `pthread_cond_init`, `pthread_cond_wait`, `pthread_cond_timedwait`, `pthread_cond_broadcast`, `pthread_cond_destroy`, `gettimeofday`, `usleep`, `write`, `malloc`, `free`, `printf`, `fprintf`, `strcmp`, `strlen`, `atoi`, `memset` |
| Libft authorized   | No                                                                                                                                                                                                                                                                                                                                                                  |
| Description        | Coders with threads and mutexes (C)                                                                                                                                                                                                                                                                                                                                 |

Specific mandatory rules:

- Each coder must be represented by a thread (`pthread_create`).
- There is one dongle between each pair of coders.
- If only one coder exists, only one dongle exists.
- Dongle state must be protected by mutex (`pthread_mutex_t`).
- Condition variable (`pthread_cond_t`) may be used for waiting queues.
- Dongle cooldown is mandatory: cannot be retaken before `dongle_cooldown` elapsed.
- Fair arbitration is mandatory according to `scheduler`.
- With `fifo`, serve by request arrival order.
- With `edf`, serve coder with earliest burnout deadline (`last_compile_start + time_to_burnout`).
- Program must guarantee liveness: coders should not starve under `edf` if parameters are feasible.
- Separate monitor thread must detect burnout precisely and stop simulation.
- Burnout log must be printed within 10 ms after actual burnout.
- Logging must be serialized (protect output with mutex).
- Simulation stops on first burnout or when all coders reached `number_of_compiles_required`.
- Code must compile with `-Wall -Wextra -Werror -pthread`.
- You must implement a priority queue (heap) for FIFO/EDF scheduling.
- All allocated memory must be freed (no leaks).

Example simulation run:

```text
0 1 has taken a dongle
2 1 has taken a dongle
2 1 is compiling
202 1 is debugging
402 1 is refactoring
405 2 has taken a dongle
406 2 has taken a dongle
406 2 is compiling
606 2 is debugging
806 2 is refactoring
900 3 has taken a dongle
902 3 has taken a dongle
902 3 is compiling
1102 3 is debugging
1302 3 is refactoring
1505 4 burned out
```

## Chapter VII - Readme Requirements

A `README.md` must exist at repository root and let unfamiliar readers quickly understand the project and how to run it.

`README.md` must include at least:

- First line italicized and exactly:

    `This project has been created as part of the 42 curriculum by <login1>[, <login2>[, <login3>[...]]].`

- A Description section (goal + overview).
- An Instructions section (compilation, installation, execution).
- A Resources section:
    - classic references (docs, articles, tutorials),
    - explanation of AI usage (which tasks and which parts of project).

Additional required sections for this project:

- Blocking cases handled:
    - deadlock prevention and Coffman conditions,
    - starvation prevention,
    - cooldown handling,
    - precise burnout detection,
    - log serialization.
- Thread synchronization mechanisms:
    - explain primitives used (`pthread_mutex_t`, `pthread_cond_t`, custom events),
    - describe coordination of shared resources (dongles, logging, monitor state),
    - include examples of race-condition prevention and thread-safe communication.

README must be written in English.

## Chapter VIII - Submission and peer-evaluation

- Submit assignment to your Git repository as usual.
- Only content inside repository is evaluated during defense.
- Double-check file names.

### Recode instructions

During evaluation, a brief modification may be requested:

- minor behavior change,
- a few lines to write/rewrite,
- easy-to-add feature.

This may not apply to every project, but you must be prepared if listed in evaluation guidelines.

Purpose: verify your actual understanding of a specific project part.

Modification can be done in any development environment and should be feasible within a few minutes unless a specific time frame is defined.

Examples:

- small update to a function or script,
- display change,
- data structure adjustment for new information.

Exact scope and target are defined by evaluation guidelines and may vary between evaluations.
