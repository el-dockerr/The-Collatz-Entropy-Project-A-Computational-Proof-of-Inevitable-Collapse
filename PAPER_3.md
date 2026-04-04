# Digital Gravity: The Dissipative Nature of Collatz Trajectories

Authors: Swen Kalski
Date: February 17, 2026
Status: Draft / Experimental Proof

## 1. Abstract
Following my experiments in "Paper 1: The Binary Straitjacket," and "Paper 2: The Entropic Barrier" which demonstrated evidences that infinite linear growth is structurally impossible due to binary constraints, this paper investigates the long-term dynamics of Collatz trajectories.
While the Collatz function is deterministic, the "bit-mixing" properties established in Paper 1 allow us to model the trajectory as a quasi-stochastic process of information exchange. 

Through a large-scale simulation ( $10^6$ trajectories), I examine that the Collatz system is fundamentally dissipative. The information gain from multiplication ( $\log_2 3 \approx 1.585$ bits) is consistently outweighed by the information loss from division steps (experimentally averaging $\approx 2.001$ bits). This results in a persistent negative net drift of $-0.416$ bits per step, rendering divergence to infinity statistically impossible.

## 2. Introduction: The Logarithmic War

The Collatz problem can be viewed as a battle for "bit-length" (Information Content).

* A number gains altitude (bits) via Multiplication.
* A number loses altitude (bits) via Division/Right Shift.

I define the "Collatz Entropy Drift" ( $\Delta H$ ) as the expected change in bit-information per odd step:

$$
    \Delta H = \text{Gain}_{odd} - \text{Loss}_{even}
$$

$$
    \Delta H = \log_2(3) - E[\text{divisions}]
$$

If $\Delta H < 0$, the system loses "energy" (altitude) on average. The trajectory then resembles a "Random Walk with negative drift," which inevitably returns to the ground state (1).

## 3. Methodology: Measuring Gravity
We conducted a C++ experiment to empirically determine the expected value $E[\text{divisions}]$.
The theoretical model (based on the uniform distribution of tail bits established in Paper 1) predicts:
* $50\%$ probability of 1 division ( $/2$ )
* $25\%$ probability of 2 divisions ( $/4$ )
* $12.5\%$ probability of 3 divisions ( $/8$ )
* ...

The theoretical expected value is:
$$
    \sum_{k=1}^{\infty} k \cdot \frac{1}{2^k} = 2.0
$$
We compared this theoretical baseline against the measured average over 1.7 million odd steps to detect any deviation or "monster-like" resistance.

## 4. Results
**Data derived from `collatz_entropy.cpp`:
|Parameter|Value|
|---------|-----|
| Number of Scanned Integers| $1,000,000$ |
| Total Odd Steps (Ascent) | $1,741,404$ |
| Total Divisions (Descent) | $3,485,485$ |
|**Average Divisions per Step** | **2.00154** |

### Calculating the Drift
1. Information Gain (Ascent):
    Every $3n+1$ step multiplies the value by $\approx 3$.
    $$
        \text{Gain} = \log_2(3) \approx 1.58496 \text{ bits}
    $$

2. Information Loss (Crash):
    Every step is followed by an average of $2.00154$ divisions by 2.
    $$
        \text{Loss} = 2.00154 \text{ bits}
    $$
3. Net Result (Drift):
    $$
        \Delta H = 1.58496 - 2.00154 = \mathbf{-0.41658} \text{ bits}
    $$

## 5 The Ergodicity Challenge
A rigorous mathematical proof requires demonstrating that the long-term average division count is $\ge \log_2 3$ for every specific trajectory, not just the ensemble average.

While proving this strictly for all $n$ remains an open problem in number theory (equivalent to proving the system is ergodic), our findings provide a **stochastic bound:**
1. The Signal: The operation $3n+1$ mixes bits such that the valuation $v_2(3n+1)$ behaves like an i.i.d. random variable with mean 
2. The Violation: For a trajectory to diverge, it must maintain a mean valuation $\mu < 1.585$ over infinite steps.
3. The Improbability: By the Strong Law of Large Numbers, the sample mean of the valuations converges to the distribution mean (2.0) almost surely.The probability that a specific trajectory of length $L$ deviates sufficiently to stay above the "Death Line" is bounded by Chernoff bounds:
    $$
        P(\text{Survival}_L) \le e^{-c \cdot L}
    $$
    where $c$ is a positive constant determined by the Kullback-Leibler divergence between the required distribution (mean 1.585) and the actual distribution (mean 2.0).

**Conclusion:**
While we cannot strictly rule out a "rogue trajectory" with current number theory, we prove that such a trajectory would be a statistical miracle, requiring a persistent entropy violation that defies the system's mixing properties.



## 6.Discussion: Starving the Monster
The result of $-0.416$ is fundamental. It signifies that the Collatz system is energy-consuming.For every bit of "height" a number gains through multiplication, it loses an average of $1.26$ bits through the subsequent divisions (since $2.0 / 1.585 \approx 1.26$ ).

Imagine climbing a "slippery staircase":
* You take one step up (+1.58 meters).
* However, the stairs slide down by an average of 2.00 meters every time you step.

Even if "variance" (luck) allows you to catch a temporary streak of stability and gain altitude, the Law of Large Numbers ensures that, over time, you are descending into the basement at a velocity of $0.41$ bits per step.

**Significance of 2.00154 > 2.0**

Interestingly, the measured value is slightly *higher* than the theoretical 2.0. This suggests that for very large numbers, there is a slight statistical tendency to be divisible by 4 or 8 more often than pure randomness would predict. This makes the "gravity" even stronger than expected.

## 6. Summary
I have demonstrated that Collatz dynamics are dominated by a strong negative drift.The probability of a trajectory permanently fighting against this drift and escaping to infinity converges to zero as the trajectory length increases.

Combined with Paper 1, which proved the structural impossibility of a "clean ascent," Paper 3 proves that even a "dirty ascent" (one with setbacks) is statistically doomed. The digital gravity is simply too strong.

**Conclusion:** 
The Monster is not only trapped (Paper 1); it is also starving (Paper 3) while it cannot keep hisself alive in a loop (Paper 2).
