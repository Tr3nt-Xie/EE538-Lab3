# EE538 Lab 3

- Name: Fengmao Xie
- USC ID: 2834479349
- Email: fengmaox@usc.edu

## Program summary

- `matrix.cpp` (Q1): a `Matrix` class stores a private `int value[10][10]`. The constructor
  sets every element to zero. `read()` reads 100 integers in row order, `mat_add()` returns a
  new Matrix without changing either operand, and `write()` prints 10 rows with single spaces.
  `main()` reads A and B from `std::cin`, adds them, and writes the sum to `std::cout`.
- `people.cpp` (Q2 and Q3): the abstract `Person` class holds a private name and age, has const
  getters, a pure virtual `displayInfo()`, a virtual `introduce()`, and a public virtual
  destructor. `Student` and `Teacher` inherit publicly from Person, initialize the Person part
  and their own members in constructor initialization lists, and override both virtual
  functions. `main()` reads n records, creates one Student or Teacher per record, stores them
  in input order in a `std::vector<Person*>`, and makes one pass calling `displayInfo()` then
  `introduce()` through each pointer. Afterwards it deletes each object once through its
  `Person*`.

## Compile and run

```sh
g++ -std=c++17 -Wall -Wextra -pedantic matrix.cpp -o matrix
g++ -std=c++17 -Wall -Wextra -pedantic people.cpp -o people
./matrix < samples/matrix.in
./people < samples/people.in
```

Both programs compile without warnings, and their output matches `samples/matrix.out` and
`samples/people.out` exactly. I also tested:

- **matrix:** random values with negative entries, and adding a zero matrix.
- **people:** a single teacher with 1 year of experience (prints "1 years"), GPA 4 printed as
  4.0, IDs with leading zeros such as 007, and 1000 people (2000 output lines).
- **memory:** AddressSanitizer/UBSan and a leak check reported no errors or leaks.

## Non-working parts

None known.

## References

- Lab 3 description and public samples on Brightspace.
- cppreference.com for `std::fixed`, `std::setprecision`, and `override`.
- LLM assistance: Claude (Anthropic) helped draft and test the code and this README. I reviewed
  the code and the answers below.

## Q4 explanations

**1. Encapsulation in Matrix.** `value` is private, so code outside the class cannot read or
change the matrix directly. It can only use the public `read()`, `mat_add()`, and `write()`
methods, which control how the data is used. Access in C++ is checked per class, not per
object, so the member function `mat_add()` may read `other.value` of another Matrix. `main()`
is not a member of Matrix, so it cannot access `value` in any Matrix object.

**2. Private inheritance of Student.** If Student inherited privately, Person's public members
would become private members of Student. Unrelated `main()` code could then no longer call
`s.getName()`. `Person* p = &s;` would also fail to compile, because the conversion from
Student to its base Person is inaccessible outside Student. The "is-a" relationship would no
longer be visible to outside code.

**3. Abstract Person and non-virtual introduce().** `displayInfo()` is pure virtual, which makes
Person abstract, so `Person` objects cannot be created directly. A `Person*` can still point to
a concrete derived object such as a Student or Teacher. If `virtual` were removed from
`introduce()` and `override` from the derived declarations, the call would be bound statically
by the pointer's type. A `Person*` would then always call `Person::introduce()` and print
"I am a person. My name is <name>.".

**4. Construction/destruction order and the virtual destructor.** Creating a Student runs the
Person (base) constructor first, then the Student constructor body. Destruction runs in
reverse: the Student destructor, then the Person destructor. When a Student is deleted through
a `Person*`, the virtual destructor makes the call dispatch to `~Student()` first. Without it,
deleting through a base pointer is undefined behavior. In practice only `~Person()` would run,
so Student members such as the `studentID` string would not be destroyed properly.
