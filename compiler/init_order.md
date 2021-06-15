Is there a way to run a function/constructor before all the static initializers of a binary?

Use attribute constructor to specify the priority.

```c

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

int main() {

}
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
- One trick we can do is, have another constructor with 65536 priority, which is +1 than the lowest priority (65535). And measure the time delta this way.

Useful concepts in this area:
- .init_array
- .init or .ctors
- llvm.global_ctors section
- llvm source code CodeGenModule.cpp:EmitCtorList,AddGlobalCtor
- Linker script can also help put functions in the right section or init array.
- http://dbp-consulting.com/tutorials/debugging/linuxProgramStartup.html
- https://stackoverflow.com/questions/29502614/how-libc-start-mainplt-works
