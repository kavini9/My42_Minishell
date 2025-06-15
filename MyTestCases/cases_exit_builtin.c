$ bash
$ echo $SHLVL
3
$ exit 1234567891012345678901212
exit
bash: exit: 1234567891012345678901212: numeric argument required
$ echo $?
2
$ echo $SHLVL
2
$
2


$ bash
$ echo $SHLVL
3
$ exit 12 34
exit
bash: exit: too many arguments
$ echo $?
1
$ echo $SHLVL
3


$ bash
$ echo $SHLVL
3
$ exit 255 rt
exit
bash: exit: too many arguments
$ echo $?
1
$ echo $SHLVL
3


$ echo $SHLVL
3
$ exit qwwfw
exit
bash: exit: qwwfw: numeric argument required
$ echo $?
2
$ echo $SHLVL
2


$ bash
$ echo $SHLVL
3
$ exit a b
exit
bash: exit: a: numeric argument required
$ echo $?
2
$ echo $SHLVL
2


$ bash
$ echo $SHLVL
3
$ exit -1
exit
$ echo $?
255
$ echo $SHLVL
2


$ bash
$ echo $SHLVL
3
$ exit 256
exit
$ echo $?
0
$ echo $SHLVL
2