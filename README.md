# Embag: A really fast, simple bag file reader
This library reads [ROS](https://wiki.ros.org) [bag files](http://wiki.ros.org/Bags/Format/2.0) quickly without their [message descriptions](http://wiki.ros.org/msg) and without any ROS dependencies.  In fact, its only dependency is [lz4](https://github.com/lz4/lz4).

## Building
First, you'll need [Bazel](https://docs.bazel.build/versions/master/install-ubuntu.html#step-1-add-bazel-distribution-uri-as-a-package-source).   You'll also need to install the [lz4](https://github.com/lz4/lz4) dev package:

    sudo apt install liblz4-dev

To build, run:

    # Embag echo demo binary
    bazel build //embag_echo:embag_echo
    # Run with
    bazel-bin/embag_echo/embag_echo --bag /path/to/sweet.bag --topic /awesome/topic

    # Shared object file
    bazel build //lib:embag.so

    # Debian package
    bazel build //lib:embag-debian

    # Python Wheel (for example, you might use a specific installation of Python)
    PYTHON_BIN_PATH=/usr/local/bin/python3.7.5 bazel build //python:wheel
    
To test, run:

    # This will run both the C++ and Python tests against a small bag file
    bazel test test:* --test_output=all

## Usage
To use the C++ API:
```c++
Embag::View view{};
auto bag = std::make_shared<Embag::Bag>(filename);
view.addBag(bag);

for (const auto &message : view.getMessages({"/fun/topic", "/another/topic"})) {
  std::cout << message->timestamp.to_sec() << " : " << message->topic << std::endl;
  std::cout << message->data()["fun_array"][0]["fun_field"].as<std::string>() << std::endl;
}
```
There's also a Python API.  See the [python directory](https://github.com/embarktrucks/embag/tree/master/python) for details.

## Thank you...
This library was heavily influenced by:
- [bag_rdr: a zero-copy ROS bag parser library](https://github.com/starship-technologies/bag_rdr)
- [Java Bag Reader](https://github.com/swri-robotics/bag-reader-java)

## License (MIT)
Copyright 2020 Embark Trucks

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

