savedcmd_os_module.mod := printf '%s\n'   os_module.o | awk '!x[$$0]++ { print("./"$$0) }' > os_module.mod
