#!/bin/bash
#
# Deploys the Zensical website locally.
#
# Usage:
#
#   ./scripts/deploy_zensical_website_locally.sh

if [[ "$PWD" =~ scripts$ ]]; then
    echo "FATAL ERROR."
    echo "Please run the script from the project root. "
    echo "Present working director: $PWD"
    echo " "
    echo "Tip: like this"
    echo " "
    echo "  ./scripts/deploy_zensical_website_locally.sh"
    echo " "
    exit 42
fi

# Build the WebAssembly version for the Play page, if Emscripten is installed
if command -v em++ > /dev/null; then
  ./wasm/build.sh
else
  echo "em++ not found: the Play page will not work locally"
fi

zensical serve
