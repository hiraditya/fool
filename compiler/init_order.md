Is there a way to run a function/constructor before all the static initializers of a binary?

Use attribute constructor to specify the priority.

```c

#include <cstdio>

struct test {
    test(int x) {
        printf("i am constructed! %d\n", x);
    }
};

test test1{1};

__attribute__((constructor(0))) void ctest() {
    printf("i am also constructed!\n");
}

__attribute__((init_priority(101))) test test2{2};

__attribute__((init_priority(101))) test test3{2};

__attribute__((constructor(65536))) void ctest1() {
    printf("i am also constructed later!\n");
}

int main() {
printf("i am constructed in main\n");
}

/** Output:
i am also constructed!
i am constructed! 2
i am constructed! 2
i am also constructed later!
i am constructed! 1
i am constructed in main
*/
```

Is main called immediately after the static initializers are done?
No. After static initializers, the entry point, which is `_start` for linux systems, is called.

How to measure overhead of static initializers then:
- Have a constructor with highest priotity, get the time from there.
- Call the timer from within the main.
- Take the time delta.
  - This does include the overhead of `_start` though.
  - To remove the overhead of `_start` we can define our own `_start` function. and use `-nostartfiles` compiler flag.
  - We can also remove `_start` by passing `--entry=my_start_function` to the compiler. This tells compiler to use `my_start_function` as entry point.
- One trick we can do is, have another constructor with 65536 priority, which is +1 than the lowest priority (65535). And measure the time delta this way. This approach is buggy as any constructor with a priority value is guaranteed to run **before** all constructors without a prority.

Useful concepts in this area:
- .init_array
- .init or .ctors
- llvm.global_ctors section
- llvm source code CodeGenModule.cpp:EmitCtorList,AddGlobalCtor
- Linker script can also help put functions in the right section or init array.
- http://dbp-consulting.com/tutorials/debugging/linuxProgramStartup.html
- https://stackoverflow.com/questions/29502614/how-libc-start-mainplt-works
