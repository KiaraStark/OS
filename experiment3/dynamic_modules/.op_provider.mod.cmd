savedcmd_op_provider.mod := printf '%s\n'   op_provider.o | awk '!x[$$0]++ { print("./"$$0) }' > op_provider.mod
