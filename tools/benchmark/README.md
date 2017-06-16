Benchmark
=========

map find
--------

Variable number of items is added to map (number of items stored in map is the value on X axis).
Then constant number of map searches is done. Number of microseconds that test takes is the value of Y axis.
Key is random uint64 value.

Comparison of tree, hash and binary search structures with up to 350 elements:

![map find](./plots/map_find_350_compare.png)

If map contains below 300 elements tree is the fastest.



Comparison of tree, hash and binary search structures with up to 3500 elements:

![map find](./plots/map_find_3500_compare.png)

If map contains more than 300 elements hash map is the fastest.
At about 1000 elements binary search vector becomes faster than std::map.
boost::map is much faster than binary search or std::map.


Comparison of tree, hash and binary search structures with up to 100000 elements:

![map find](./plots/map_find_100000_compare.png)

At about 40000 elements binary search becomes faster than tree.
Hash table is the fastest.



Compare different tree structures:

![map find](./plots/map_find_350_tree.png)

Compare different hash table structures:

![map find](./plots/map_find_350_hash.png)

Compare different flat array binary search structures:

![map find](./plots/map_find_350_bin_search.png)





