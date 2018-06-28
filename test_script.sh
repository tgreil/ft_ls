color="\033[31m"
eoc="\033[0m"
touch mine ref
make
# test 1
echo $color "ls" $eoc
ls > ref
./ft_ls > mine
diff mine ref

rm mine ref
