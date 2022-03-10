
# hash_table
I made this hash table in C as part of the [ioopm](https://github.com/IOOPM-UU/) course together with [ExOster](https://github.com/ExOster/).

## Known issues (TODO-list)
### LF
The load factor-resizing relies on a statically defined array of prime numbers. A solution to this would be a function which generates a prime number or something akin to one.

### ht_Remove
Whenever an element in the hash table is to be removed, but the element does not exist, this is handled in a pretty awful way. Needs fixing!

### Improved tests for ht_keys and ht_values
Supposedly, the keys and values functions have issues. Need to test this!

### Fix folder structure
Sort out this mess in src and make appropriate changes in the ```#include```s and the makefile.