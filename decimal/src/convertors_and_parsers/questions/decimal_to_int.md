To transform the binary value `00000000 00000000 00000000 00101010`, which is `42` in decimal, to `11111111 11111111 11111111 11010110`, which is `-42` in decimal, you perform a two's complement operation. This operation involves two main steps: bitwise negation (flipping the bits) and adding one.

Here's how you do it:

1. **Bitwise Negation (Flip All Bits)**:
   - Start with your initial value: 
     ```
     00000000 00000000 00000000 00101010  // +42
     ```
   - Flip all the bits to get the one's complement:
     ```
     11111111 11111111 11111111 11010101
     ```

2. **Add One**:
   - Add `1` to the one's complement to get the two's complement:
     ```
     11111111 11111111 11111111 11010101
   +                                    1
     -----------------------------------
     11111111 11111111 11111111 11010110  // -42
     ```

This result is the two's complement representation of `-42`.

### Implementation in C:

You can achieve this transformation programmatically using C as follows:

```c
#include <stdio.h>

int main() {
    int positive = 42;
    int negative = ~positive + 1;  // Compute the two's complement

    printf("Positive: %d, Negative: %d\n", positive, negative);
    return 0;
}
```

### Explanation:
- **`~positive`**: This operation flips all the bits of `positive` (bitwise negation).
- **Adding 1**: The addition of 1 completes the transition from one's complement to two's complement, effectively providing the negative of the original number.

By following these steps, you arrive at the correct representation of `-42` in two's complement form.   