# Bridges

## Introduction

Bridges is an educational project to implement a Http/s server. This project is still in its very early stages of development. 

## Goals

* Deploy a website with the Bridges executable and a config file similar to Apache or Nginx.
* Provide a high level framework for creating websites via the Bridges API. 

Ideally, to create a very simple website with the API it would look something like this:

```c++
#include <bridges/server.h>

int main(void)
{
    using namespace bridges;

    Server server;

    server.set_root("/var/www1");

    server.route("/", GET, [](const Request& request, Response& resp){
        resp.set_content("index.html");
    })

    server.route("/update", GET|POST, [](const Request& request), Response& resp) {
        if(request.method() == GET)
        {
            resp.set_content("some_page.html");
        }
        else
        {
            std::string item = request.data["item"];
            int quantiy      = request.data["quantity"];

            // Do something with post parameters

        }
        resp.status_code( OK );
    }

    server.listen("localhost", 8000);
}
```

This sample code would deploy a server that will listen on `localhost:8000` whose document root is the `/var/www1` folder and the home page is 'index.html' with a '/update' post endpoint.

## Prerequsites

## Usage 

### Getting the source code and submodules

```bash
git clone https://github.com/AlexanderJDupree/Bridges.git
cd Bridges
git submodule update --init --recursive
```

### Building source code and execute unit tests
Requires [cmake](https://cmake.org/)

```bash
mkdir build
cd build && cmake ..
make install
```
The tests binary will be in bin/tests/
Bridges binary will be in bin/

## Contributing

All contributions are welcome: bug fixes, recommendations, issues, features.

Plase see the [issues](https://github.com/AlexanderJDupree/LinkedListsCPP/issues) before you submit a pull request or raise an issue to avoid duplication. 

To contribute to this repository:

- [Fork the project to your own GitHub profile](https://help.github.com/articles/fork-a-repo/)

- Download the project using git clone:
```
git clone git@github.com:<YOUR_USERNAME>/LinkedListsCPP.git
```
- Create a new branch with a descriptive name:
```
git checkout -b descriptive_branch_name
```
- Write some code, fix something, and add a test to prove that it works.

- Commit your code and push it to GitHub

- [Open a new pull request](https://help.github.com/articles/creating-a-pull-request/) and describe the changes you have made.

- We'll accept your changes after review.

Simple!

## What's in this Repo?

## Built With

* [googletest](https://github.com/google/googletest) - Unit test and mocking framework
* [cmake](https://cmake.org/) - Build system

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://raw.githubusercontent.com/AlexanderJDupree/Bridges/master/LICENSE) file for details

