#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from __future__ import print_function

import os, sys
import argparse, logging
import CppHeaderParser
from mako.template import Template
from mako.lookup import TemplateLookup

parser = argparse.ArgumentParser(
    description="SMOC Meta Object Compiler Generator")
parser.add_argument('input_file', metavar='INPUT_FILES')
parser.add_argument('-o', '--output', help='output file')
parser.add_argument('-t', '--template', help='template to generate code with')
args = parser.parse_args()

parsed_header = CppHeaderParser.CppHeader(args.input_file);
lookup = TemplateLookup(
    directories=os.path.abspath(os.path.dirname(args.input_file)));

gen_result = Template(
    "<%include file=\"" + os.path.basename(args.template) + "\"/>",
             lookup = lookup).render(source_include = os.path.basename(args.input_file),
                functions = parsed_header.functions,
                classes = parsed_header.classes,
                variables = parsed_header.variables,
                enums = parsed_header.enums)

with open(args.output, "w+") as output_file:
    output_file.write(gen_result)
