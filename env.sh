#!/bin/bash

# Small hack to detect if script is running in interactive shell
if (( SECONDS == 0 )); then 
	echo -e "This script must be sourced in order to set environment variables.\nCall \`source $0\` instead."
fi

_projectpath="$(readlink -f $(dirname $0))"
[[ -d ${_projectpath}/.toolchain && -d ${_projectpath}/.fasmg ]] || echo "Error: directories .toolchain and/or .fasmg do not exist"
export CEDEV="${_projectpath}/.toolchain"
export PATH="${_projectpath}/.fasmg:${_projectpath}/.toolchain/bin:$PATH"
