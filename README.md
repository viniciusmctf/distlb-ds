# Data Structures for Load Balancing

### WorkObj

`WorkObj` contains information of each specific piece of Work in the system.

By standard, we provide Index (`sys_index`) and Load (`load`) information.

Operators of **greater** and **lesser** are used to order `WorkObj` based on their Load.

Operator **plus** is used to acquire the sum of load between two `WorkObj`.

Operator **equals** is used to compare `WorkObj` indexes.

### WorkGroup

**WIP**

### WorkMap

`WorkMap` is a class container for multiple `WorkObj`.

By standard, it will order `WorkObj`s by `load`, in order to remove them from the `Map`.

