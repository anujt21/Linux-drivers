savedcmd_/home/prospero/Linux-drivers/1_hello/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/prospero/Linux-drivers/1_hello/"$$0) }' > /home/prospero/Linux-drivers/1_hello/hello.mod
