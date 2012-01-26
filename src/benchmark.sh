#! /bin/sh

## Il faut compiler le programme avant de lancer le benchmark
# make clean && make

if [ ! -f ./benchmark ]
then
    echo "You must compile the programme (make) : file ./benchmark do not exists."
    exit 1
fi

if [ -f ./"Ftmp.txt" ]
then
    rm "Ftmp.txt"
fi

if [ $# != 1 ] 
then
    echo "Usage : ./benchmark.sh <nb_exec>"
    exit 1
fi

nb_exec=$1

echo ""
echo "The given time of execution for a tutte version is an average over $nb_exec executions"
echo ""

## Pour toutes les variantes de Tutte
for i in $(seq 0 4); 
do
    ## Moyenne sur 10 exection
    moy=0
    carre=0
    for j in $(seq 1 $nb_exec);
    do
	## Récupération du temps d'exécution du i-ème tutte
	# echo $(./benchmark ../graphes/imdb.tlp.gz $i) >> "Ftmp.txt"
	line=$(echo $(./benchmark ../graphes/imdb.tlp.gz $i))
	echo $line
	tutte_version=$(echo $line | tail -n 1 | cut -d";" -f1)
	add=$(echo $line | tail -n 1 | cut -d":" -f4)
	add=$(echo $add | cut -d" " -f1)
	# echo $add
	moy=$(echo "$moy + $add" | bc)
	carre=$(echo "$carre + ($add * $add)" | bc)
    done

    moy=$(echo "scale=4; $moy / $nb_exec" | bc)
    moy_carre=$(echo "scale=8; $carre / $nb_exec" | bc)
    ecart_type=$(echo "scale=8; sqrt($moy_carre - ($moy * $moy))" | bc)
    # tutte_version=$(echo $(cat "Ftmp.txt" | tail -n 1 | cut -d";" -f1))
    echo "${tutte_version}: "
    echo -n "moyenne : \t"
    echo $moy
    echo -n "écart type : \t"
    echo $ecart_type
done
echo
