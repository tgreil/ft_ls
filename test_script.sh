color="\033[31m"
eoc="\033[0m"
FILE_MINE="/tmp/mine"
FILE_REF="/tmp/ref"
touch $FILE_MINE $FILE_REF
make


# test 1: simple test a vide ( default : ".")
echo $color "ls" $eoc
ls > $FILE_REF
./ft_ls > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 2: option t (trier par time)
echo $color "ls -t" $eoc
ls -t > $FILE_REF
./ft_ls -t > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 3: option t et r trier par time mais a l'envers
echo $color "ls -tr" $eoc
ls -tr > $FILE_REF
./ft_ls -tr > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 4: sans option avec un dossier en parametre
echo $color "ls srcs" $eoc
ls srcs > $FILE_REF
./ft_ls srcs > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 5: option a (invisible file)
echo $color "ls -a" $eoc
ls -a > $FILE_REF
./ft_ls -a > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 6: reversed a option
echo $color "ls -ar" $eoc
ls -ar > $FILE_REF
./ft_ls -ar > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 7: option R (open recursive folder)
echo $color "ls -R libft" $eoc
ls -R libft > $FILE_REF
./ft_ls -R libft > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 8: option R with reverse
echo $color "ls -Rr" $eoc
ls -Rr > $FILE_REF
./ft_ls -Rr > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 9: option l, print informations about files
echo $color "ls -l srcs/" $eoc
ls -l srcs/ > $FILE_REF
./ft_ls -l srcs/ > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 10: Option R et a en meme temps, boucle inf potentiel
echo $color "ls -Ra" $eoc
ls -Ra > $FILE_REF
./ft_ls -Ra > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 11: toutes options depuis racine
echo $color "ls -lRrta ~/Desktop" $eoc
ls -lRrta ~/Desktop > $FILE_REF
./ft_ls -lRrta ~/Desktop > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 11: test avec plusieurs dossiers en parametre
echo $color "ls -lRrta srcs libft includes libft/srcs" $eoc
ls -lRrta srcs libft includes libft/srcs > $FILE_REF
./ft_ls -lRrta srcs libft includes libft/srcs > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 12: test avec fail de group and user
echo $color "ls -l /private/etc" $eoc
ls -l /private/etc > $FILE_REF
./ft_ls -l /private/etc > $FILE_MINE
diff $FILE_MINE $FILE_REF

#test 13: test de chr
echo $color "ls -l /dev" $eoc
ls -l /dev > $FILE_REF
./ft_ls -l /dev > $FILE_MINE
diff $FILE_MINE $FILE_REF

rm $FILE_MINE $FILE_REF
