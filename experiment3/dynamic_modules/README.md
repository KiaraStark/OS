# Dynamic Integer Operation Modules

This experiment uses two loadable kernel modules:

- `op_provider.ko` implements integer `+`, `-`, `*`, `/`, assigns the global function pointer `my_op_ptr` in its init function, and exports that pointer with `EXPORT_SYMBOL`.
- `op_client.ko` uses the same logical interface as experiment 2: `result, num1, num2, op`. It calls the exported function pointer indirectly and prints the result when inserted.

Build:

```sh
make
```

Load the provider first:

```sh
sudo insmod op_provider.ko
```

Then load the client with parameters:

```sh
sudo insmod op_client.ko num1=12 num2=3 op=/
dmesg | tail
```

Unload in reverse order:

```sh
sudo rmmod op_client
sudo rmmod op_provider
```

