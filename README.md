# ccg

Code generation utility that integrates with CMake

## Overview

`ccg` generates files from [inja](https://github.com/pantor/inja) templates supplied with `json` data that are rendered during a CMake configure via a function `ccg_generate` with a and input files

## Getting Started

First, add the package to the `vcpkg.json` project manifest file:

```json
{
  "name": "myproject",
  "version": "0.0.1",
  "dependencies": [
    "ccg"
  ]
}
```

Then, add the package with `find_package(ccg CONFIG REQUIRED)` and call `ccg_generate` in CMake:

```cmake
cmake_minimum_required(VERSION 3.25)

project(
    my-example
    LANGUAGES CXX
)

find_package(ccg CONFIG REQUIRED)

ccg_generate(
    "${CMAKE_SOURCE_DIR}/input.json"
    "${CMAKE_SOURCE_DIR}/config.json"
)

add_executable(my-example)

set_target_properties(
    my-example
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_RQUIRED ON
)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

target_sources(my-example PRIVATE ${SOURCE_FILES})

target_compile_options(my-example PRIVATE "/std:c++20")

target_include_directories(my-example PRIVATE "${CMAKE_SOURCE_DIR}/src")
```

`ccg_generate` takes two parameters; paths to an input json file, and a config json file

### config.json

Specifies global configuration settings

```json
{
  "templates": "${sourceDir}/templates/"
}
```

- `templates` - supplies the path to the `inja` templates directory

### input.json

Specifies the input data that is used during generation

```json
{
  "out": "${sourceDir}/src/",
  "items": [
    {
      "name": "Verbosity",
      "outputs": [
        {
          "template": "enum.hpp.jinja",
          "output": "Verbosity.hpp"
        },
        {
          "template": "enum.cpp.jinja",
          "output": "Verbosity.cpp"
        }
      ],
      "data": {
        "description": "Represents the verbosity of logging output",
        "namespace": "example",
        "underlyingType": "int8_t",
        "default": "Normal",
        "includePath": "",
        "items": [
          {
            "name": "Quiet",
            "value": 0,
            "string": "Quite",
            "alts": [ "quite", "QUIET" ]
          },
          {
            "name": "Minimal",
            "value": 1,
            "string": "Minimal"
          },
          {
            "name": "Normal",
            "value": 2,
            "string": "Normal",
            "alts": [ "NORMAL", "normal" ]
          },
          {
            "name": "Detailed",
            "value": 3,
            "string": "Detailed"
          },
          {
            "name": "Diagnostic",
            "value": 4,
            "string": "Diagnostic"
          }
        ]
      }
    }
  ]
}
```

- `out` - supplies a base path for generated files
- `items` - array of data that is iterated
  - `name` - identifying name for the item. This value is added to the data available inside the template rendering
  - `outputs` - array of render targets to enable generating multiple files for each `item`
    - `template` - path to the `inja` template that is rendered. The path is relative to `config.templates` in the supplied configuration file
    - `output` - path of the rendered file. The path is relative to `out`, or can be specified with an absolute path using a [macro](#macro-substitutions)
  - `data` - general purpose bag of data passed to template rendering

## Macro Substitutions

Json files are able to use cmake macro substitutions in non-data fields

| Macro              | Description                            | Example                                           |
|--------------------|----------------------------------------|---------------------------------------------------|
| `${sourceDir}`     | Substitutes to `${CMAKE_SOURCE_DIR}`   | `"templates": "${sourceDir}/templates/"`          |
| `${binaryDir}`     | Substitutes to `${CMAKE_BINARY_DIR}`   | `"templates": "${sourceDir}/templates/"`          |