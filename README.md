# c-plugins
Plugin example in C/C++ using dlopen and dlsym (dynamic linking loader interface)

What you need
-------------

Install the next software.

`sudo apt-get install git gcc gdb cmake make`

Build
-----

Clone this repository.

`git clone https://github.com/gustavorv86/c-plugins`

Go to repository folder, make build directory and run cmake.

```
cd c-plugins
mkdir build
cd build
cmake ..
make
```

Run test examples
-----------------

Go to **build** directory and run the examples.

```
cd c-plugins/build
./dist/Debug/bin/plugin-launcher dist/Debug/lib/
```

