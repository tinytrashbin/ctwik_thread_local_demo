
This tiny examples proves how CTwik handles the changed thread_local variables.

We had:

```C++
thread_local S s{1};
```

that is being changed to:

```C++
thread_local S s{2};
```

CTwik-client recompiles all the functions where thread-local varible `s` is being used. Once the shared-lib is being patched, and those recompiled functions are called, the thread-local variable `s` will also be reconstructed for each thread.

The old instance of `s` will be left in zombi state as no function is going to refer to it after hot-patching the shared-lib. However, when the thread is terminated, the destructor will be called for both zombi thread-local `s`, as well the new one that was created after patching shared-lib.



## Run

`./run.sh`

## Output:

```
Thread-1, [i = 0]: s.x = S::S(1)
1
Thread-2, [i = 0]: s.x = S::S(1)
1
Thread-3, [i = 0]: s.x = S::S(1)
1
s.x = S::S(2)
2
Thread-1, [i = 1]: s.x = 1
Thread-2, [i = 1]: s.x = 1
Thread-3, [i = 1]: s.x = 1
Thread-1, [i = 2]: s.x = 1
Thread-2, [i = 2]: s.x = 1
Thread-3, [i = 2]: s.x = 1
Thread-1, [i = 3]: s.x = S::S(2)
2
Thread-2, [i = 3]: s.x = S::S(2)
2
Thread-3, [i = 3]: s.x = S::S(2)
2
Thread-1, [i = 4]: s.x = 2
Thread-2, [i = 4]: s.x = 2
Thread-3, [i = 4]: s.x = 2
Thread-1, [i = 5]: s.x = 2
Thread-2, [i = 5]: s.x = 2
Thread-3, [i = 5]: s.x = 2
~S::S(2)
~S::S(1)
~S::S(2)
~S::S(1)
~S::S(2)
~S::S(1)
~S::S(2)
```

