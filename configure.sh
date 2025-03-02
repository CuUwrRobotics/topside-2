#!/usr/bin/env bash

cd lib/navigator-lib
cargo build
cd ../..
cmake -B build -G Ninja
