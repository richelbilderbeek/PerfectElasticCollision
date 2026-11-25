#!/bin/bash
#
# Build the WebAssembly version of PerfectElasticCollision
# into docs/app, to be picked up by the Zensical website build.
#
# Requires Emscripten (em++).
#
# Usage, from the repository root:
#
#   ./wasm/build.sh
#
set -euo pipefail

out_dir="docs/app"
mkdir -p "${out_dir}"

em++ wasm/perfect_elastic_collision.cpp \
  -O2 \
  -std=c++14 -Wall -Wextra -Wshadow -pedantic -Werror \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=createPerfectElasticCollisionModule \
  -s ENVIRONMENT=web \
  -s "EXPORTED_FUNCTIONS=['_pec_collide','_pec_get_result']" \
  -s "EXPORTED_RUNTIME_METHODS=['cwrap']" \
  -o "${out_dir}/perfect_elastic_collision.js"

echo "Built ${out_dir}/perfect_elastic_collision.js and .wasm"
