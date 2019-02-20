# doors
Doors

![EO badge](https://www.elegantobjects.org/badge.svg)

[![CircleCI](https://circleci.com/gh/DronMDF/doors.svg?style=shield)](https://circleci.com/gh/DronMDF/doors)
[![CodeCov](https://codecov.io/gh/DronMDF/doors/branch/master/graph/badge.svg)](https://codecov.io/gh/DronMDF/doors)
[![PDD status](http://www.0pdd.com/svg?name=DronMDF/doors)](http://www.0pdd.com/p?name=DronMDF/doors)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/DronMDF/doors/blob/master/LICENSE)

# Building

```sh
$ conan install <path to zond> --build=missing
$ cmake -GNinja <path to zond>
$ ninja
$ ninja test
```
