#!/usr/bin/env python

from common import OPERATOR_SETS
from jinja2 import Environment, FileSystemLoader, select_autoescape
import csv
import os

env = Environment(
    loader=FileSystemLoader("templates"),
    autoescape=select_autoescape(),
    trim_blocks=True,
    lstrip_blocks=True
)


def generate_table(data):
    template = env.get_template("opstats-table.tex")

    data_by_operator = {row['operator']: row for row in data}
    totals_by_state = {
        val: sum(int(row[val]) for row in data)
        for val in ["alive", "subsumed", "subsuming", "duplicated"]
    }
    return template.render(
        data=data_by_operator,
        opsets=OPERATOR_SETS,
        totals=totals_by_state
    )


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(
        prog=os.path.basename(__file__),
        description='Produces a LaTeX table with per-operator statistics'
    )
    parser.add_argument('stats_csv')
    parser.add_argument('-o', '--output', type=str, default='output.tex')
    args = parser.parse_args()

    with open(args.stats_csv) as f_csv:
        data = csv.DictReader(f_csv)
        with open(args.output, 'w') as f_tex:
            print(generate_table(list(data)), file=f_tex)
