#! /bin/sh

## Il faut compiler le programme avant de lancer le benchmark
# make clean && make

if [ ! -f ./benchmark ]
then
    echo "You must compile the programme (make) : file ./benchmark do not exists."
    exit 1
fi

if [ $# != 2 ] 
then
    echo "Usage : ./benchmark.sh <graph_path> <nb_exec>"
    exit 1
fi

graph_path=$1
nb_exec=$2

echo "The order of execution of the different Tutte : "
echo "Tutte séquentiel asynchrone"
echo "Tutte séquentiel asynchrone 2"
echo "Tutte séquentiel asynchrone 2 (Vec2f)"
echo "Tutte séquentiel asynchrone 3" 
echo "Tutte parallèle synchrone"
echo "Tutte parallèle asynchrone"


echo ""
echo "The given time of execution for a tutte version is an average over $nb_exec executions"
echo ""

for g in $1*;
do
    ./benchmark $g $2 | tail -n 4
    echo "passe $g" >/dev/fd/2
done

# ## Pour toutes les variantes de Tutte
# for i in $(seq 0 4); 
# do
#     ## Moyenne sur 10 exection
#     moy=0
#     carre=0
#     for j in $(seq 1 $nb_exec);
#     do
# 	## Récupération du temps d'exécution du i-ème tutte
# 	# echo $(./benchmark ../graphes/imdb.tlp.gz $i) >> "Ftmp.txt"
# 	line=$(echo $(./benchmark ../graphes/imdb.tlp.gz $i))
# 	echo $line
# 	tutte_version=$(echo $line | tail -n 1 | cut -d";" -f1)
# 	add=$(echo $line | tail -n 1 | cut -d":" -f4)
# 	add=$(echo $add | cut -d" " -f1)
# 	# echo $add
# 	moy=$(echo "$moy + $add" | bc)
# 	carre=$(echo "$carre + ($add * $add)" | bc)
#     done

#     moy=$(echo "scale=4; $moy / $nb_exec" | bc)
#     moy_carre=$(echo "scale=8; $carre / $nb_exec" | bc)
#     ecart_type=$(echo "scale=8; sqrt($moy_carre - ($moy * $moy))" | bc)
#     # tutte_version=$(echo $(cat "Ftmp.txt" | tail -n 1 | cut -d";" -f1))
#     echo "${tutte_version}: "
#     echo -n "moyenne : \t"
#     echo $moy
#     echo -n "écart type : \t"
#     echo $ecart_type
# done
# echo
