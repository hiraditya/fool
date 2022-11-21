Optimizing this code:

- if else dead code
- peephole optimizations of expressions
- loop fusion
- arithmetic formulae to replace the entire loop
- why compiler isn't doing the expected

```cpp
#define STEP   256
#define ITERS  2048

int loop(int zero)
{
    int t = 0, i, iter;

    // Loop versioning - compare zero with step 

    for (iter = 0; iter < ITERS; ++iter)
    {
        for (i = zero; i < STEP; i += 1)
        {
            if (i < zero)
            {
              t += 3 + 3 * t;
            }
            else
            {
              t -= 1 - 5 * t;
            }
        }
    }

    return t;
}
```
