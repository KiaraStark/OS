savedcmd_op_client.mod := printf '%s\n'   op_client.o | awk '!x[$$0]++ { print("./"$$0) }' > op_client.mod
