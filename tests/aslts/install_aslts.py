#!/usr/bin/python3
import os
import argparse
import importlib


'''
    This script will take the following arguments:
    arg 1: directory name
    arg 2: options

    It will do the following actions:
    1) cd to the directory stated by arg 1
    2) consume the config file for that particular directory
    3) compile/disassemble/convert with flags from 2
'''


def parse_args ():
    parser = argparse.ArgumentParser(description='Install ASLTS by compiling it')
    parser.add_argument('-p', '--path', required=True,
        help='path of a directory containing a test case')
    parser.add_argument('-d', '--disasm', action='store_true',
        help='perform disassembler test sequence (binary comparisons)')
    args = parser.parse_args()
    return args


class aslts_builder:
    common_compile_flags = '-of -cr -vs -l -sc -sa -ic -ta -ts -so -lm -ln -ls -li '
    common_disassemble_flags = '-od '
    main_filename = 'MAIN.asl'
    compile_string = 'iasl ' + common_compile_flags
    compile_oe_string = compile_string + '-oe '

    def __init__(self, test_module_path): # consume the config file
        module_path = test_module_path.replace('/','.')
        if not(module_path.endswith('.')):
            module_path += '.'
        index = module_path.find("aslts")
        if index > -1:
            module_path = module_path[index + len("aslts."):]

        self.testcase_config = importlib.import_module(module_path + 'testConfig')
        self.compile_string += self.testcase_config.compile_flags + self.main_filename
        self.compile_oe_string += self.testcase_config.compile_flags + '-p oe_' + self.testcase_config.name + ' ' + self.main_filename


    def compile_test(self):
        os.system(self.compile_string)

    def compile_test_externs_inplace(self):
        os.system(self.compile_oe_string)

    def disassemble_test(self):
        os.system(self.disassemble_oe_string)
        pass

    def convert_test(self):
        os.system(self.convert_string)
        pass


def main ():
    args = parse_args ()
    print (args.path)
    builder = aslts_builder (args.path)
    os.chdir (args.path)
    builder.compile_test()
    builder.compile_test_externs_inplace()


if __name__ == '__main__':
    main()
