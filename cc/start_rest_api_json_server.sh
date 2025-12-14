#!/bin/bash

cd app/example_rest_api_json_server

cmake -B build

cmake --build build

./build/example_rest_api_json_server