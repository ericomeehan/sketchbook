#  Python Hashing Difficulty Formula

I have come up with the formula to determine the difficulty of hashing a block on my chain.  Each block needs to be hashed with a result less than 2^(512-difficulty).  The formula for the difficulty is this:

difficulty = 10 * sqrt(log10(size_in_bytes)) + 1

You can look at the resulting graph in the link below, basically you are looking for these things:

    ⁃    X represents the size of what you are hashing in bytes.
    ⁃    Y is the resulting difficulty.  
    ⁃    As X increases, Y continues to increase at an exponentially slower rate.
    ⁃    When calculating hashes, processing power requirements grow exponentially with changes in difficulty.

In the end, the interesting result is this: by the mathematical logic of our difficulty formula, we have a minimum possible data size of 1 byte, making  that our base unit of measurement for difficulty.  From there, small files are relatively easy to mine while large ones are reasonable but exponentially harder.  

All of this to say, I ran the experiment on my servers mining an imaginary block.  Here are some results:  At a difficulty of 10, the cpu took 6329 cycles over a period of 0.0631 seconds.

Entering 1GB into the difficulty formula results in a difficulty of exactly 31, which took 335954684 cpu cycles to hash over 11 minutes 16.8348 seconds on a much faster server.

Entering 1 TB into the difficulty formula results in a difficulty of 34.641 - which started hashing about an hour and a half ago.  I’ll keep you posted on the results.
