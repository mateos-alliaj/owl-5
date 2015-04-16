![Logo](http://owl.dmtry.me/img/repository.png "Owl Framework")

# [Website](http://owl.dmtry.me/) :: [Documentation](http://docs.owl.dmtry.me/) :: [Vagrant](https://github.com/owl-framework/vagrant)

[![Latest Stable Version](http://img.shields.io/packagist/v/owl/owl.svg?style=flat)](https://packagist.org/packages/owl/owl)
[![Author](http://img.shields.io/badge/author-@ovr-blue.svg?style=flat-square)](https://twitter.com/ovrweb)
[![Build Status](https://img.shields.io/travis/owl-framework/owl/master.svg?style=flat-square)](https://travis-ci.org/owl-framework/owl)
[![Software License](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat-square)](LICENSE.md)

Owl is an extreme fast PHP framework powered by [Zephir](https://github.com/phalcon/zephir) language and delivered as C-extension.

*This is a development branch and We need to focus on the docs, tests, fixes and cleaning code, so we need your help ;)*

### System Requirements

To build it you need the following requirements:

* g++ >= 4.4/clang++ >= 3.x/vc++ 9
* gnu make 3.81 or later
* autoconf 2.31 or later
* automake 1.14 or later
* PHP development headers and tools

If you're using Ubuntu, you can install the required packages this way:

```bash
sudo apt-get update
sudo apt-get install git gcc make re2c php5 php5-json php5-dev libpcre3-dev
```

### Installation

You can build extension and install it like:

```bash
git clone https://github.com/owl-framework/owl.git
git submodule update --init
cd ext
./install
echo extension=owl.so > /etc/php5/fpm/conf.d/owl.ini
echo extension=owl.so > /etc/php5/cli/conf.d/owl.ini
```

Don't forget to restart your php-fpm:

```bash
sudo service php5-fpm restart
```

### Build Zephir code

To build the zep Source to C extension:
* [zephir](https://github.com/phalcon/zephir)

### Contributing

1. Fork the current repository by fork button.
2. Create a new branch for each feature or improvement. `git checkout -b my-branch`
3. Send a pull request from each feature branch to the master branch.

*Please do not send files from `/ext` directory, just those from the `/owl`.

### Components

- Annotations
- Cache
- Bridge
- Event
- Log
- Session
- Mvc
    * Controller
- Http
    * Request
    * Response
- Application

License
-------

This project is open-sourced software licensed under the MIT License. See the LICENSE file for more information.
