color="\033[31m"
eoc="\033[0m"
touch mine ref
make
# test 1: simple test a vide ( default : ".")
echo $color "ls" $eoc
ls > ref
./ft_ls > mine
diff mine ref

#test 2: option t (trier par time)
echo $color "ls -t" $eoc
ls -t > ref
./ft_ls -t > mine
diff mine ref

#test 3: option t et r trier par time mais a l'envers
echo $color "ls -tr" $eoc
ls -tr > ref
./ft_ls -tr > mine
diff mine ref

#test 4: sans option avec un dossier en parametre
echo $color "ls srcs" $eoc
ls srcs > ref
./ft_ls srcs > mine
diff mine ref

#test 5: option a (invisible file)
echo $color "ls -a" $eoc
ls -a > ref
./ft_ls -a > mine
diff mine ref

#test 6: reversed a option
echo $color "ls -ar" $eoc
ls -ar > ref
./ft_ls -ar > mine
diff mine ref

#test 7: option R (open recursive folder)
#echo $color "ls -R" $eoc
#ls -R > ref
#./ft_ls -R > mine
#diff mine ref

#test 8: option R with reverse
#echo $color "ls -Rr" $eoc
#ls -Rr > ref
#./ft_ls -Rr > mine
#diff mine ref

#test 9: option l, print informations about files
#echo $color "ls -l" $eoc
#ls -l > ref
#./ft_ls -l > mine
#diff mine ref

rm mine ref