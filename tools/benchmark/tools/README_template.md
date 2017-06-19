Benchmark
=========

c++ compiler: CXX_COMPILER
compiler flags: CPP_FLAGS
cpu: CPU_INFO
boost: BOOST_VERSION

map search
----------

Variable number of items is added to map (number of items stored in map is the value on X axis).
Then constant number of map searches is done. Number of microseconds that test takes is the value of Y axis.
Key is random uint64 value.

comparison of tree, hash table and binary search maps
-----------------------------------------------------

Comparison of tree, hash and binary search structures with up to 350 elements:

![map find](./plots/map_find_350_compare.png)


Comparison of tree, hash and binary search structures with up to 3500 elements:

![map find](./plots/map_find_3500_compare.png)


Comparison of tree, hash and binary search structures with up to 100000 elements:

![map find](./plots/map_find_100000_compare.png)


comparison of tree maps
-----------------------

Comparison of tree structures with up to 350 elements:

![map find](./plots/map_find_350_tree.png)

Comparison of tree structures with up to 3500 elements:

![map find](./plots/map_find_3500_tree.png)

Comparison of tree structures with up to 100000 elements:

![map find](./plots/map_find_100000_tree.png)


comparison of hash table maps
-----------------------------

Comparison of hash table structures with up to 350 elements:

![map find](./plots/map_find_350_hash.png)

Comparison of hash table structures with up to 3500 elements:

![map find](./plots/map_find_3500_hash.png)


Comparison of hash table structures with up to 100000 elements:

![map find](./plots/map_find_100000_hash.png)


comparison of binary search maps
--------------------------------

Comparison of binary search structures with up to 350 elements:

![map find](./plots/map_find_350_bin_search.png)

Comparison of binary search structures with up to 3500 elements:

![map find](./plots/map_find_3500_bin_search.png)

Comparison of binary search structures with up to 100000 elements:

![map find](./plots/map_find_100000_bin_search.png)
