# The Collatz Entropy Project: A Computational Proof of Inevitable Collapse

> "Mathematics may not be ready for such problems." — Paul Erdős

> "Computer Science is." — This Repository / Swen Kalski

## 1. Overview
The Collatz Conjecture ( $3n+1$ ) has baffled mathematicians for decades. Traditional approaches often get lost in the chaotic behavior of individual trajectories. This project takes a fundamentally different approach: **Information Theory and Binary Mechanics.**

Instead of asking "Does it reach 1?", we ask: "Does the system gain or lose information over time?"

By analyzing the binary structure of the operations, we have demonstrated that the Collatz system is dissipative. It is an entropy-destroying process with a specific, measurable negative drift. Infinite growth is not just statistically unlikely; it is structurally impossible.

## 2. The Three Pillars of evidence
This repository contains three distinct layers of evidence that, when combined, hopefully, close the lid on the conjecture.

### Phase 1: The Binary Straitjacket (Structural Proof)
See: `PAPER_1.md` | Code: `collatz_straitjacket.cpp`

My experiments suggest that a "Monster" (a number that ascends infinitely without crashing) requires a specific binary structure: it must consist of an infinite sequence of trailing ones (...11111).

* The Mechanism: The operation $3n+1$ acts as a "bit-mixer." It forces random binary cliffs.
* The Limit: To survive $k$ steps without a major crash (division by 4 or more), a number must end in $k$ ones.
* The Contradiction: Since all natural numbers have a finite bit-length, no number can sustain an infinite ascent. The "straitjacket" eventually tightens, forcing a collapse.

### Phase 2: The Entropic Barrier
See: `PAPER_2.md` | Code: `collatz_loop_breaker.cpp`

I demonstrated that non-trivial closed cycles (loops) are statistically impossible because the system cannot conserve the "information energy" required to close a circle. What becomes a strong evidence.

* The Loop Condition: To form a closed loop, the information gained by multiplication ($3^k$) must exactly match the information lost by division ($2^m$). This requires a specific division ratio of $\log_2(3) \approx 1.585$ .
* The Drift Gap: Our experiments prove the system enforces a natural division ratio of $\approx 2.00$ . This creates a persistent "Energy Debt" of 0.415 bits per step.
* The Impossibility: The probability of a trajectory defying this drift to close a large loop decreases exponentially. For large $N$, the required deviation is statistically indistinguishable from zero ($> 1000\sigma$).

### Phase 3: Digital Gravity (Statistical Proof)
See: `PAPER_3.md` | Code: `collatz_entropy.cpp`

I measured the "thermodynamics" of the system over millions of trajectories.
* Ascent Gain: $\log_2(3) \approx 1.585$ bits of information.
* Descent Loss: Experimentally proven average of $\approx 2.00$ bits lost per step.
* Net Drift: $-0.415$ bits per step.

This might confirms that the system has "Digital Gravity." The house edge is approx. 20%. Any upward trajectory is merely a temporary fluctuation against a relentless downward pull.

### Phase 3: The Death Line (Visual Proof)
See: `collatz_gravity_well.png` | Code: `plot_gravity.py`

The image above visualizes the "Logarithmic War."
* The Y-Axis: Information content (Bits / $\log_2$ ).
* The Jagged Lines: Real numbers fighting for altitude.
* The Red Dashed Line: The calculated entropy drift ( $-0.415$ bits/step).

**Conclusion of Evidence:** No matter how high a number starts (even Mersenne numbers like $2^{50}-1$ ), it cannot escape the Entropy Decay Zone. The red line represents the speed of information destruction, which is mathematically faster than the speed of information creation in the $3n+1$ system.

## 3. Repository Structure
* `PAPER_1.md` - The structural proof regarding binary cliffs and Mersenne limitations.
* `PAPER_2.md` - The statistical proof regarding the negative entropy drift.
* `src/collatz_bit_mechanic.cpp` - Tool to analyze individual binary steps and carries.
* `src/collatz_entropy.cpp` - Tool to measure the 2.00 vs 1.585 drift ratio on massive datasets.
* `src/collatz_straitjacket.cpp` - The "Monster Hunter" algorithm.
* `scripts/plot_gravity.py` - Python script to generate the visualization.

## 4. How to Reproduce

### Prerequisites
* C++ Compiler (g++ or clang)
* Python 3 + Matplotlib (for visualization)

### Running the Entropy Analysis
```Bash
g++ -o collatz_entropy src/collatz_entropy.cpp
./collatz_entropy
# Output will confirm the -0.415 drift
```
### Generating the Death Line Graph
```Bash
pip install matplotlib numpy
python scripts/plot_gravity.py
```

## 5. Conclusion of the experiment (what might be a Proof)
The Collatz Conjecture is not a mystery of randomness; it is a predictable consequence of binary arithmetic.
* Structure: Infinite growth requires infinite bits (impossible).
* Statistics: The descent is stronger than the ascent ( $-0.415$ drift).
* Dynamics: Variance allows temporary peaks, but gravity guarantees the final collapse.

Authored by Swen Kalski 2026
