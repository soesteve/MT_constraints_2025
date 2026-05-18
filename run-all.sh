#!/bin/bash

set -e

# Generates all the YAML fields from using Papadakis' algorithm
# to detect subsuming mutants.

if ! test -d .venv; then
  virtualenv .venv
fi
source .venv/bin/activate
pip install -r requirements.txt

VERSION=$1

if [ -z "$VERSION" ]; then
  echo "Usage: $0 <version>"
  exit 1
fi


for i in ${VERSION}_killed_*.csv; do
  python 01-subsumption.py "$i" --output "${i%.csv}-subsuming.yaml"
done

# Computes subsumption relationships across all tests
python 01-subsumption.py ${VERSION}_killed_*.csv --output ${VERSION}_killed_all.yaml

# Computes subsumption relationships across all tests while
# considering one of each set of duplicated mutants (30 samples)
mkdir -p sample-duplicated
for i in `seq -w 1 30`; do
  echo "Computing subsumed mutants with sampling - step $i"
  OUTPUT="sample-duplicated/$i-subsumed.yaml"
  python 01-subsumption.py ${VERSION}_killed_*.csv --sample-duplicated --output "$OUTPUT"
  python 02-operators.py "$OUTPUT" --output "sample-duplicated/$i-stats.csv"
done

# Computes operator statistics (across all tests)
python 02-operators.py ${VERSION}_killed_all.yaml --output ${VERSION}_operatorStats_noDups.csv

# Computes times each operator is part of the subsuming operators set
python 03-within-subsuming.py ${VERSION}_operatorStats_noDups.csv --output ${VERSION}_inSubsuming_noDups.csv
python 03-within-subsuming.py sample-duplicated/*-stats.csv --output ${VERSION}_inSubsuming_sampleDups.csv

# Produces per-operator stat table
python 04-opstats-table.py ${VERSION}_operatorStats_noDups.csv --output ${VERSION}_operatorStats_noDups.tex

# Produces table for number of times mutants are in the subsuming set
python 05-within-subsuming-table.py ${VERSION}_inSubsuming_sampleDups.csv --output ${VERSION}XS_inSubsuming_sampleDups.tex
