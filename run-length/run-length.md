
# Run-Length Encoding

Basically the easiest encoding, we seperate data (a string of characters) as runs of sequences that are stored as key-value pairs of the sequence and how many times it is iterated. This is clearly best used for data that has many repeated sequences.

Example:
"wwwwweeeeepp" -> "5w5e2p"

In my implementation this is done on ASCII data (text files), but this can also be applied to binary (runs are repeated bytes) or images (same as binary).

### Usage

To compile this file, go to the main directory and run `make rl`. Then, the executables rl_encode and rl_decode can be used.

`rl_encode <input> <output>` where input and output are the input and output filenames
`rl_decode <input> <output>` where input is the already encoded file and output is the "decompressed" file