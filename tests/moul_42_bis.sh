#!/bin/sh

DEBUG=0
PIPE=pipe
OUT=out
SHELL_ORIG="42sh"
SHELL="./42sh.$$"
MKFIFO=`which mkfifo`
TAIL=`which tail`
TRACE="trace"

cp $SHELL_ORIG $SHELL

debug()
{
  if [ $DEBUG -eq 1 ]
  then
    echo $* 1>&2
  fi
}

launch_shell()
{
  $MKFIFO $PIPE
  cp $TAIL mytail 2>&1 >/dev/null
  (./mytail -f $PIPE 2>/dev/null | $SHELL 2>&1 > $OUT &) >/dev/null 2>/dev/null
}

kill_shell()
{
  if [ `pidof $SHELL | wc -l` -ne 0 ]
  then
    killall -9 $SHELL 2>&1 > /dev/null
  fi
  if [ `pidof mytail | wc -l` -ne 0 ]
  then
    killall mytail 2>&1 > /dev/null
  fi
  rm -f $PIPE $OUT 2>&1 > /dev/null
}

clean()
{
  rm -f $PIPE $OUT mytail 2>&1 > /dev/null
}

test01()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls" > $PIPE
  fi


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test02()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls -la" > $PIPE
  fi


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test03()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "/bin/ls -la" > $PIPE 
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test04()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmpx.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "/ls" > $PIPE
  fi


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmpx.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "KO "
  else
    echo -n "OK "
  fi

  rm -f tmpx.$$ 2>&1 > /dev/null
}

test05()
{
  kill_shell 2>&1 > /dev/null
  OLDPATH="$PATH"
  PATH=""
  launch_shell 2>&1 > /dev/null
  PATH="$OLDPATH"
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "/bin/ls" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test06()
{
  kill_shell 2>&1 > /dev/null
  OLDPATH=$PATH
  PATH="/bin"
  launch_shell 2>&1 > /dev/null
  PATH=$OLDPATH
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "/bin/ls" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test07()
{
  kill_shell 2>&1 > /dev/null
  OLDPATH=$PATH
  PATH=":/bin"
  launch_shell 2>&1 > /dev/null
  PATH=$OLDPATH
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "/bin/ls" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test08()
{
  kill_shell 2>&1 > /dev/null
  OLDPATH=$PATH
  PATH="/bin:"
  launch_shell 2>&1 > /dev/null
  PATH=$OLDPATH
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "/bin/ls" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test09()
{
  kill_shell 2>&1 > /dev/null
  OLDPATH=$PATH
  PATH="/bin:"
  launch_shell 2>&1 > /dev/null
  PATH=$OLDPATH
  touch "tmp.$$"
  cp /bin/ls myls

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "myls" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "KO "
  else
    echo -n "OK "
  fi

  rm -f mysl 2>&1 > /dev/null
  rm -f tmp.$$ 2>&1 > /dev/null
}

test10()
{
  kill_shell 2>&1 > /dev/null
  OLDPATH=$PATH
  PATH="/bin:"
  launch_shell 2>&1 > /dev/null
  PATH=$OLDPATH
  touch "tmp.$$"
  cp /bin/ls myls

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "./myls" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  cat $OUT | grep "tmp.$$" 2>&1 >/dev/null
  if [ $? -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test11()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  cp /bin/ls myls

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "setenv toto" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "setenv tata coucou" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "env" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "setenv titi abcd" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "unsetenv tata" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "env" > $PIPE
  fi


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tata" | grep "coucou" | wc -l`
  b=`cat $OUT | grep "titi" | grep "abcd" | wc -l`
  c=`cat $OUT | grep "toto" | wc -l`

  if [ $a -eq 1 -a $b -eq 1 -a $c -eq 2 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ myls 2>&1 > /dev/null
}

test12()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  cp /bin/ls myls

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "mkdir plopplop" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "cd plopplop" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "pwd" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "cd -" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "pwd" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "cd /" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls" > $PIPE
  fi


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "plopplop" | wc -l`
  b=`cat $OUT | grep "usr" | wc -l`

  if [ $a -eq 1 -a $b -eq 1 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -Rf plopplop 2>&1 > /dev/null
  rm -f tmp.$$ 2>&1 > /dev/null
}

test13()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  cp /bin/ls myls

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "exit 42" > $PIPE
  fi
  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`ps aux | grep mysh | grep -v grep | grep -v moul_ | wc -l`

  if [ $a -eq 0 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test14()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  cp /bin/ls myls

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "echo toto" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "echo $USER" > $PIPE
  fi
  sleep 0.2

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "toto" | wc -l`
  b=`cat $OUT | grep "$USER" | wc -l`

  if [ $a -eq 1 -a $b -eq 1 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test15()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  cp /bin/ls myls

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "setenv PATH /tmp" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "setenv PATH /bin" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls" > $PIPE
  fi
  sleep 0.2

  a=`pwd`
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "setenv PATH $a:/bin" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "cd /" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "myls" > $PIPE
  fi
  sleep 0.2
  
  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tmp.$$" | wc -l`
  b=`cat $OUT | grep "usr" | wc -l`

  if [ $a -eq 2 -a $b -eq 1 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
  rm -f myls 2>&1 > /dev/null
}

test16()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo " " > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo " ls -l" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls -l " > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo " ls -l " > $PIPE
  fi
  sleep 0.2


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tmp.$$" | wc -l`
  if [ $a -eq 3 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test17()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "	" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "	ls -l" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls -l	" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "	ls -l	" > $PIPE
  fi
  sleep 0.2


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tmp.$$" | wc -l`
  if [ $a -eq 3 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test18()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "   ls    -l    " > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "		ls		-l		" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls	-l" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo " 	 ls  	-l 	" > $PIPE
  fi
  sleep 0.2


  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tmp.$$" | wc -l`
  if [ $a -eq 4 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test19()
{
  cmd="$1"
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "$cmd" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tmp.$$" | wc -l`
  d=`date | cut -c-6`
  b=`cat $OUT | grep "$d" | wc -l`
  if [ $a -eq 1 -a $b -eq 1 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ 2>&1 > /dev/null
}

test20()
{
  cmd="$1"
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  touch "tmpx.$$"
  touch "tmpx1.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "$cmd" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tmp" | grep "$$" | wc -l`
  if [ $a -eq 2 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ tmpx.$$ tmpx1.$$ 2>&1 > /dev/null
}

test21()
{
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "" > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo " " > $PIPE
  fi
  sleep 0.2
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "ls | grep x | cat" > $PIPE
  fi
  sleep 0.2

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`ps aux | grep "$SHELL" | grep -v grep | grep -v moul_ | wc -l`
  if [ $a -eq 1 ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ tmpx.$$ tmpx1.$$ 2>&1 > /dev/null
}

test22()
{
  cmd="$1"
  redir="$2"
  result="$3"
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  touch "tmpx.$$"
  touch "tmpx1.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "$cmd" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $redir 2>/dev/null | grep "tmp" | grep "$$" | wc -l`
  if [ $a -eq $result ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ tmpx.$$ tmpx1.$$ $redir 2>&1 > /dev/null
}

test23()
{
  cmd="$1"
  result="$2"
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null
  touch "tmp.$$"
  touch "tmpx.$$"
  touch "tmpx1.$$"

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "$cmd" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $OUT | grep "tmp" | grep "$$" | wc -l`
  if [ $a -eq $result ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f tmp.$$ tmpx.$$ tmpx1.$$ 2>&1 > /dev/null
}

test24()
{
  cmd="$1"
  redir="$2"
  result="$3"
  kill_shell 2>&1 > /dev/null
  launch_shell 2>&1 > /dev/null

  # Envoi des commandes
  if [ `pidof $SHELL | wc -l` -eq 1 ]
  then
    echo "$cmd" > $PIPE
  fi

  # attente de l'execution des commandes
  sleep 0.5

  # Récuparation du résultat
  a=`cat $redir 2>/dev/null | wc -l`
  if [ $a -eq $result ]
  then
    echo -n "OK "
  else
    echo -n "KO "
  fi

  rm -f $redir 2>&1 > /dev/null
}


all_test()
{

echo -n "Simple exec : "
test01 # ls
test02 # ls -la
test03 # /bin/ls -la
test04 # /ls
echo ""

echo -n "Change the PATH : "
test05 # PATH="" - mysh - /bin/ls
test06 # PATH="/bin" - mysh - /bin/ls
test07 # PATH=":/bin" - mysh - /bin/ls
test08 # PATH="/bin:" - mysh - /bin/ls
test09 # PATH="/bin" - mysh - mysh
test10 # PATH="/bin" - mysh - ./mysh
echo ""

echo -n "Builtins : "
test11 # setenv et unsetenv
test12 # cd
test13 # exit
test14 # echo
echo ""

echo -n "Update PATH : "
test15 # ls - setenv PATH /plop - ls - setenv PATH /bin - ls
echo ""

echo -n "Space and tab char : "
test16 # espace
test17 # tabulation
test18 # on en mets un peu partout
echo ""

echo -n "Separator ';' : "
test19 "ls -l;date"
test19 "ls -l	;date"
test19 "ls -l;	date"
test19 "ls -l ;date"
test19 "ls -l; date"
test19 "ls -l 	 	; 	 	 	date"
test19 "	 ls	 -l	 ;	 date	 "
echo ""

echo -n "Simple pipe : "
test20 "ls -l|grep tmpx"
test20 "ls -l | grep tmpx"
test20 "   ls   -l   |    grep   tmpx"
echo ""

echo -n "Multi pipe : "
test20 "ls -l | cat -e | grep tmpx"
test20 "ls -l | grep tmpx | cat -e"
test20 "ls -l | cat | grep tmpx | cat | cat | grep tmp | cat | cat -e | cat"
echo ""

echo -n "Do you have Zombie ? : "
test21
echo ""

echo -n "Redirect char : "
test22 "ls -l > toto4125" "toto4125" "3"
test22 "ls -l>toto4126" "toto4126" "3"
test22 "> toto4127 ls" "toto4127" "3"
echo "xxtmpxx$$" > "toto4128"
test22 "ls -l >> toto4128" "toto4128" "4"
echo "xxtmpxx$$" > "toto4129"
test22 ">> toto4129 ls" "toto4129" "4"
ls /dev > "toto4130"
echo "xxtmpxx$$" >> "toto4130"
ls /dev >> "toto4130"
test23 "cat < toto4130" "1"
ls /dev > "toto4131"
echo "xxtmpxx$$" >> "toto4131"
ls /dev >> "toto4131"
test22 "cat < toto4131 > toto4132" "toto4132" "1"
rm -f toto4* 2>&1 > /dev/null
echo ""

echo -n "Redirect AND pipe : "
echo "plop" > "toto4200"
echo "bonjour" >> "toto4200"
echo "tmp" >> "toto4200"
echo "tmp2" >> "toto4200"
test24 "cat toto4200 | grep tm > toto4201" "toto4201" "2"
test24 "cat toto4200 | grep tm | cat | grep p2 > toto4202" "toto4202" "1"
test24 "cat < toto4200 | grep tm | cat | grep p2 > toto4203" "toto4203" "1"
test24 "cat toto4200 | grep tm > toto4204 ; cat < toto4200 | grep p >> toto4204" "toto4204" "5"
rm -f toto4* 2>&1 > /dev/null
echo ""
}

rm -f "$TRACE" 2>&1 > /dev/null
all_test | tee "$TRACE"
nb_ok=`cat "$TRACE" | tr " " "\n" | grep "OK" | wc -l`
nb_ko=`cat "$TRACE" | tr " " "\n" | grep "KO" | wc -l`
nb=`expr $nb_ok + $nb_ko`
result=`expr $nb_ok \* 100 / $nb`
if [ $result -le 6 ]
then
  result=0
fi
echo "Result : $result%"

kill_shell
clean
rm $SHELL
