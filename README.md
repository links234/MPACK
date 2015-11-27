# ![alt text][logo] MPACK

[![alt text][travis-ci-status]][travis-ci-link]
[![alt text][gitter-logo]][gitter-link]

MPACK is intended to be a cross-platform starting point for 2D games running on Windows, Linux and Android. Core engine is written in C++ and OpenGL/ES but there is also Java for Android specifics (Google Services) and bash for scripting. 

Full feature list can be found [here][1].

## Getting started

#### Linux

##### Setup
```bash
cd path/to/workspace
git clone https://github.com/links234/MPACK.git
cd MPACK
sudo sh scripts/config_linux.sh
```

##### Build
```bash
make -f "jni/Linux.mk"
```

##### Run
```bash
./game
```

## License

[Apache License 2.0][2]

[1]: FEATURES.md
[2]: http://www.apache.org/licenses/LICENSE-2.0

[logo]: logo30x30.png "MPACK"
[travis-ci-link]: https://travis-ci.org/links234/MPACK
[travis-ci-status]: https://travis-ci.org/links234/MPACK.svg?branch=master "Travis CI"
[gitter-link]: https://gitter.im/links234/MSuite?utm_source=share-link&utm_medium=link&utm_campaign=share-link
[gitter-logo]: https://img.shields.io/badge/GITTER-join%20chat-green.svg "Gitter Chat"



[![Join the chat at https://gitter.im/links234/MPACK](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/links234/MPACK?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)