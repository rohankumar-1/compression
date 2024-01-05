
# Compression as Intelligence

**compression**: art of reducing # of bits needed to store/transmit data
- lossless data can be decompressed to its exact original value, i.e. no bits of information are lost
- lossy data discards "unimportant" data, so decompression is not an exact original value, but an approximation
    - what deems "important" info?


compression algorithms: goal is to find system that reduces the # of bits as much as possible
- two parts, a model and a coder
    - **model**: estimates the probability distribution of an alphabet (i.e. E is more common than Z, so E should have a shorter code)
    - **coder**: assigns codes to symbols following model's estimation of distribution
- model portion is the most important part, prediction of a distribution is an AI problem

> Optimal modeling has been proven **uncomputable**

**lossy compression**: consists of a transformation to seperate important and unimportant data, and then lossless compression of the important section
- transform is AI problem, trying to find what is important to humans or other target of compression

---

**Limits of Information Theory**: there are hard limits on lossless compression
1. **No universal compression** that can compress any input
    - not possible to compress random data or compress recursively
    - random data's symbol distribution will be uniform, and so there will be no model and coder that can minimize data
    - after some point, data will be compressed to a form that is random, and at this point, for the reason above, we cannot infinitely compress data
2. Given a model (distribution) of input data alphabet, the best coder will assign symbols with **probability $p$ using $\log_{2}{\frac{1}{p}}$**
    - these optimal coders are known, it is the model that is the issue
3. Data has a **universal but uncomputable probability distribution**
    - i.e. any string $x$ has a probability of about $2^{-\abs{M}}$ where $M$ is the shortest possible description of $x$ and $\abs{M}$ is the length of M (in bits)
    - there is no generalizable procedure for finding $M$ (or estimating)

**Universal Compression (lack thereof)**: proved by the **Counting Argument**
    - assume an algorithm exists that compresses all strings of $<=n$ bits, then there are exactly $2^{n}$ different binary strings of length $n$
    - a universal compressor would have to encode each input differently
        - if two inputs compressed to the same output, decompressor can't differentiate
    - however, there are only $2^{n}-1$ binary strings shorter than $n$ bits
    - so, if a compressor needs to compress a string to a smaller binary string (at least 1 bit shorter), there are much less options, and therefore not all strings can be compressed (due to problem of overlapping output)
    - every compressor must expand some of its input, but not by more than one symbol (i.e. any algorithm can have an extra bit to indicate rest of data is uncompressed)
    - extension of counting argument shows that the compressed output of any algorithm appears random to it, and therefore cannot be compressed again

**Bounded Coder**: there are limits to coders (ways to signify the model)
    - ex. assume goal is to compress digits of $\pi$, and therefore there are 10 possible symbols (each digit) 
    - model is that each digit occurs with equal probability (inf. # of digits)
    - consider three different binary codes:
        1. BCD (binary coded decimal): each digit takes 4 bits, 0 is 0000 and 9 is 1001 
            - if translating from ASCII, output is compressed by 50%, decompressor just splits data into 4-bit strings to read it
        2. Huffman: 0-5 take 3 bits, (take off first 0 of BCD), and then 6-9 takes 4 bits, therefore average bits per symbol is 3.4
            - decoder reads bits one at a time, and decodes a digit as soon as found in the Huffman Tree (basically look-up table)
            - **uniquely decodable because no code is a predix of any other code**
        3. Binary: each digit takes straight binary value, 0=0, 2=10, etc
            - not uniquely decodable, since 111 could be read as 3 1's in a row, or 7 (i.e. symbol codes have overlapping prefixes)
    - each coding has its merits, and can be optimized
    - consider Huffman, we can split data into groups of 2 digits, and then create Huffman Tree based on this, to get bit compression ratio of 3.3352
    - Shannon and Weaver (1949) shows that best coder is $\log_{2}{\frac{1}{p}}$ for a symbol with probability $p$
        - **expected entropy** of a RV X is its expected code length
            - suppose $X$ may have values $X_1, X_2, ...$, and each has a specific probability $p_i$
            - entropy of $X$ is $H(X)=E[\log_{2}{\frac{1}{p(X)}}]=\sum{p_i \log_{2}{\frac{1}{p_i}}}$ 
            - there is no smaller code that could be decoded ambiguosly than this
            - information content (entropy) of a set of strings is at most the sum of the information content of each individual string
            - if entropies are equal, then strings $X$ and $Y$ are independent, i.e. knowing one would give no information on other
            - conditional entropy $H(X|Y)$ is information content of X given we know Y, is $H(X)$ if we independent
            - if $X$ is a stringo of symbols, chain rule says that $p(X)$ can be expressed as product of the sequence of symbol predictions conditioned on previous symbols
        - entropy is a measure of uncertainty and a lower bound on expected compression
        - basically, entropy is the limit of compression
        - since entropy can only be calculated for a known probability distribution, and general models do not exist

**Uncomputable Models**: as given above, Shannon's coding theorem gives a hard limit on the best compression achieved, but this is given the model of uniformaly distributed, independent probabilities of each digit
    - instead, if an algorithm can recognize the digits of $pi$, and encode the entirety of the string as "the first million digits of pi", or as a program that calculates this value
    - counting argument says that most strings are compressible, but the strings we care about (text, images, software, etc) are compressible, since we can find shorter descriptions of the data (they have meaning)
    - **algorithmic probability**: defined as the fraction of random programs in some language L that output string $x$, where each program $M$ is weighted by $2^{-\abs{M}}$
        - this probability is dominated by the shortest program, and the length of this shortest program has a length that is called the **Kolmogorov Complexity** of x
    - probability depends on language L, but only by some constant
        - this constant is simply related to the size of a theoretical compiler between two languages
    - not proven to be a true universal prior probability, but accepted on empirical grounds
    - **minimum description length** choose the simplest hypothesis consistent with the training data
        - formalization of Occam's Raxor, applied to a wide range of machine learning algorithms
        - i.e. simplest explanation for data is probably the best predictor
    - best compression is achieved in finding encoding to the shortest program $M$ in some language $L$ that outputs string $x$, and the choice of $L$ becomes less important as string size grows
        - in this way, a program that can ouput $x$ is the descriptor of the essence of $x$
    - no procedure exists in any language to do this, nor is there one to find the minimum length needed to describe any program $x$
    - **testing for randomness**: any consistent formal system powerful enough to describe statements in arithmetic has at least one true statement that cannot be proven (an extension of Godel's first incompleteness theorem)
        - there is therefore, by extension, an infinite number of true but unprovable statements, i.e. there are only a finite number of true statements "x is random" that can be proven, out of the infinite possible strings
            - if there was a finite number of these statements, then we could describe a program as "the string x s.t. it is the first to be proven to ba a million bits long and random", which is a paradox with the fast that these description itself is smaller than a million bits long
    - **testing for maximum compression**: this is the same as testing whether a compressed string can be improved any further

**Compression as AI**: understanding of a sequence gives you the ability to predict it in the future, and therefore, random data has no meaning and predictability
- compression/prediction can be used to test understanding (i.e. if we can compress the data, we have some understanding of the essence of the data)
- **Turing Test**: a human communicates with two agents, one is another human and one is AI, if the human cannot judge correctly which is the machine 70% of the time after 10 minutes of interaction, the machine is said to be have intelligence
    - compressing transcripts such as those made in these communications requires the ability to compute a model of the form $p(A|Q)=p(QA)/p(Q)$ where Q is the context up to the current question and A is the answer/response
        - i.e. the ability to respond well is given as the ability to understand the context and possible answers
    - this issue requires vast real-world knowledge
- **Universal Intelligence**: proposed by Legg and Hutter, more general than Turing's definition
    - considering problem of reward-seeking agents in arbitrary environments described by random programs, an agent communicates with an environment through transmission of symbols
    - environment gives back a reward signal, and the goal of the agent is to maximize this accumulated reward
    - universal intelligence is defined as the expected reward over all possible environments, where the probability of each environment described a a program $M$ is algorithmic, proportional to $2^{-\abs{M}}$
    - Hutter proved that the optimal (uncomputable) solution is for the agent to guess that the distribution over M is dominated by the shortest program consistent with past observations for each input, and then act accordingly
        - again, a formal statement of Occam's razor

Summary: no universal compression, no recursive compression, no compression of random data
    - also, strings are mostly random, except for ones with meaning
    - compression is modeling + coding, coding is solved, modeling is not
    - key to compression is to understand the data you wish to compress


## Coding

The assignment of bit strings to symbols s.t. strings cna be decoded unambiguosly to recover original data. 

- **Static Coding**: coding is computed by the compressor and transmitted to the decompressor (as part of compressed data)
- **Dynamic Coding**: computed by compressor, prediodically updated, but not transmitted
    - decompressor reconstructs the code using exactly the same algorithm using the previously decoded data to estimate probabilities

**Huffman Coding**: calculates the optimal assignment over an alphabet of n symbols in O(nlogn) time. 
- most common symbols are given smallest bit string
- inefficient in practice because code lengths must be rounded to a whole number of bits
- if symbol probability is not a power of $\frac{1}{2}$, then the code assignment is less than optimal
    - since we need to express it is a bit string, we must round up to a next greatest number given the probability
    - inefficiency can be reduced by assigning probabilities to longer groups of symbols but only at the cost of an exponential increase in alphabet size (and therefore runtime)
- **Algorithm**: given an alphabet + probability for each symbol
    1. Construct a binary tree
        a. start with each symbol in its own tree
        b. join two trees with smallest probabilities
        c. continue until left with one binary tree
    2. Code is a description of its path from the root (0=left, 1=right)
        - in this way, the # of bits is the depth of that symbol in the tree
- Huffman is typically static, for speed, since compressor only needs to compute code once
    - transmitting Huffman table requires only sending the size of each symbol in bytes, since the compressor+decompressor can then assign codes by starting with the shortest symbols, counting up from 0 and appending a 0 bit whenever code gets longer
- complication of packing bits into bytes is that last byte has to be padded in such a way that it is not interpreted as a Huffman code
    - can do this by reserving code for end, such as full byte of 1111111

**Arithmetic Coding**: focusing on drawback of Huffman that code lengths must be whole number of bits
- let $P$ be a model s.t. $P(x)$ for a string x is the probability of that string, and $P(<x)$ is the sum of the probabilities of all strings lexicographically less than x
    - then, $P(\leq x)=P(<x)+P(x)$
    - arithmetic code for a string x is the shortest binary number y s.t. $P(<x) \leq y < P(\leq x)$
    - this can
    