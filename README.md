# Hash Table Implemented in C++
**CS3334 Data Structures** assignment for implementing a hash table from scratch.

## Operations 
For a hash table **`T`** it is possible to perform following operations:

➕ *`IntertKey(x)`*: inserts the key/entry **`x`** to **`T`**;

➖ *`DeleteKey(x)`*: removes the key/entry **`x`** from **`T`**;

🔍 *`SearchKey(x)`*: searches for the key/entry **`x`** in **`T`**: if it is found, returns *`“x was found”`*, otherwise, it 
returns *`“x does not exist”`*.

## Performance

Hashing functions used:
- Hashing by multiplication
- Hashing by division

Collision handling:
- Separate chaining (using linked lists)

Please refer to *`CS3334Proj.pdf`* file in this repo for detailed elaboration on performance evaluation.