#! /bin/sh

## Il faut compiler le programme avant de lancer le benchmark
# make clean && make

if [ ! -f ./main ]
then
    echo "You must compile the programme (make) : file ./main do not exists."
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
    tmp=0
    for j in $(seq 1 $nb_exec);
    do
	## Récupération du temps d'exécution du i-ème tutte
	echo $(./main ../graphes/imdb.tlp.gz $i toto.tlp) >> "Ftmp.txt"
	add=$(echo $(cat "Ftmp.txt" | tail -n 1 | cut -d":" -f4))
	add=$(echo $add | cut -d" " -f1)
	tmp=$(echo "$tmp + $add" | bc)
    done

    tmp=$(echo "scale=4; $tmp / $nb_exec" | bc)
    tutte_version=$(echo $(cat "Ftmp.txt" | tail -n 1 | cut -d";" -f1))
    echo -n "${tutte_version}: "
    echo $tmp
done
echo
