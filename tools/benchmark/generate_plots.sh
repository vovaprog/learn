#!/bin/bash

IMDIR="./plots"
TEMPDIR="./plots_temp"

if [ -d "$IMDIR" ]; then
  rm -r $IMDIR
fi
mkdir $IMDIR

if [ -d "$TEMPDIR" ]; then
  rm -r $TEMPDIR
fi
mkdir $TEMPDIR


DATAROOT="./build_release/benchmark_data"


function generate_maps {

    CURTEMP=$TEMPDIR/map_find
    mkdir $CURTEMP
    
    cp "$DATAROOT/map find/$1/std map.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/boost map.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/boost intrusive set.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/boost intrusive avl_set.txt" $CURTEMP
    
    python ./show_plot.py "$CURTEMP" "$IMDIR/map_find_${1}_tree.png"
    
    rm -r $CURTEMP
    
    
    
    CURTEMP="$TEMPDIR/map_find"
    mkdir "$CURTEMP"
    
    cp "$DATAROOT/map find/$1/boost unordered_map.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/boost unordered_map no hash.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/std unordered_map.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/std unordered_map no hash.txt" $CURTEMP
    
    python ./show_plot.py "$CURTEMP" "$IMDIR/map_find_${1}_hash.png"
    
    rm -r $CURTEMP
    
    
    
    CURTEMP="$TEMPDIR/map_find"
    mkdir $CURTEMP
    
    cp "$DATAROOT/map find/$1/boost flat_map.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/std deque.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/std vector.txt" $CURTEMP
    
    python ./show_plot.py "$CURTEMP" "$IMDIR/map_find_${1}_bin_search.png"
    
    rm -r $CURTEMP
    
    
    CURTEMP="$TEMPDIR/map_find"
    mkdir $CURTEMP
    
    cp "$DATAROOT/map find/$1/$2.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/$3.txt" $CURTEMP
    cp "$DATAROOT/map find/$1/$4.txt" $CURTEMP
    
    if [ ! -z "$5" ]
    then
        cp "$DATAROOT/map find/$1/$5.txt" $CURTEMP
    fi    
    
    python ./show_plot.py "$CURTEMP" "$IMDIR/map_find_${1}_compare.png"
    
    rm -r $CURTEMP
    
}


generate_maps 350 "std map" "std unordered_map" "std vector"

generate_maps 3500 "boost map" "std map" "std unordered_map" "std vector"

generate_maps 100000 "boost map" "std unordered_map" "std vector"

rm -r $TEMPDIR

exit 0


python ./show_plot_bar.py "$DATAROOT/arithmetic" $IMDIR/arithmetic.png


python ./show_plot.py "$DATAROOT/map find/350" $IMDIR/map_find_350.png

python ./show_plot.py "$DATAROOT/map find/3500" $IMDIR/map_find_3500.png

python ./show_plot.py "$DATAROOT/map find/100000" $IMDIR/map_find_100000.png



python ./show_plot.py "$DATAROOT/map insert/10000" $IMDIR/map_insert_10000.png


python ./show_plot.py "$DATAROOT/string map find/4/100" $IMDIR/string_map_04_100.png
python ./show_plot.py "$DATAROOT/string map find/4/1000" $IMDIR/string_map_04_1000.png
python ./show_plot.py "$DATAROOT/string map find/16/100" $IMDIR/string_map_16_100.png
python ./show_plot.py "$DATAROOT/string map find/16/1000" $IMDIR/string_map_16_1000.png


python ./show_plot.py "$DATAROOT/switch" $IMDIR/switch.png


