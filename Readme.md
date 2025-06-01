# Reflire
Airline flight reservation system(Semester project).


# Build Instruction
## Linux

**Note**: Do ensure that raylib and mysqlclient(C-API) is installed beforehand. Instructions are available [here](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

**Note**: Also make sure that db user password is stored in `REFLIRE_DBPPASS` environment variable beforehand

```
$ git clone https://github.com/Justaus3r/Reflire.git
$ cd src
$ wget "https://raw.githubusercontent.com/raysan5/raylib/refs/heads/master/src/raylib.h"
$ cd ../
$ make
# for cleaning all the obj/build files
$ make clean
```

## Windows

Use ``make`` to build it. Have raylib installed beforehand. Also note that a patched version of raygui maybe required for this project, so do patch raygui if you are facing [#407](https://github.com/raysan5/raygui/issues/407). This Project also assumes that raylib is installed at ``C:\\raylib\\raylib\\src``, so change the path  in ``Makefile`` if its installed elsewhere.
```
$ make
$ ./builds/reflire
# for cleaning all the junk
$ make clean 
```

## Made by
Enrollment#1: 147
Enrollment#2: 128

## Credits:
- [mysql+++](https://github.com/daotrungkien/mysql-modern-cpp/)

## License
Licensed under MIT license.
