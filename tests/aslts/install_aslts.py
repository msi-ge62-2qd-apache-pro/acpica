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


class filename_generator:
    space = ' ' # used for join within methods
    def __init__(self, name):
        self.name = name

    def emit_oe_filename(self):
        return 'oe_' + self.name + '.aml'

    def emit_disasm_name(self, style):
        if style == 'legacy':
            return self.name + '-aslminus'
        elif style == 'convert':
            return 'MAIN'
        else:
            return self.name + '-aslplus'

    def emit_disasm_style(self, style):
        if style == 'legacy':
            return self.space.join(['-dl -p', self.emit_disasm_name(style)])
        else:
            return self.space.join(['-d -p', self.emit_disasm_name(style)])

    def emit_aml_name(self, aml_kind):
        if aml_kind == 'normal_compile':
            return self.name + '.aml'
        elif aml_kind == 'convert':
            return 'MAIN.aml'
        elif aml_kind == 'disassemble_legacy':
            return self.emit_disasm_name('legacy') + '.aml'
        else:
            return self.emit_disasm_name('') + '.aml'


class command_builder:
    space = ' ' # used for join within methods
    common_flags = '-cr -vs'
    common_compile_flags = common_flags + ' -of -l -sc -sa -ic -ta -ts -so -lm -ln -ls -li'
    common_disassemble_flags = '-od'
    main_filename = 'MAIN.asl'

    def __init__(self, path):
        module_path = path.replace('/','.')
        if not(module_path.endswith('.')):
            module_path += '.'
        index = module_path.find("aslts")
        if index > -1:
            module_path = module_path[index + len("aslts."):]
        self.testcase_config = importlib.import_module(module_path + 'testConfig')
        self.fname_gen = filename_generator(self.testcase_config.name)

    def mode_to_flags(self,mode):
        if mode == 'opt/32':
            return '-r 1'
        elif mode == 'opt/64':
            return '-r 2'
        elif mode == 'nopt/32':
            return '-oa -r 1'
        elif mode == 'nopt/64':
            return '-oa -r 2'
        else:
            return ''

    def compile_common(self, mode):
        return self.space.join(['iasl', self.common_compile_flags, self.testcase_config.compile_flags, self.mode_to_flags(mode)])

    def compile_norm(self, mode):
        return self.space.join([self.compile_common(mode), self.main_filename])

    def compile_oe(self, mode):
        return self.space.join([self.compile_common(mode), '-oE', '-p', self.fname_gen.emit_oe_filename(), self.main_filename])

    def disassemble(self, style):
        return self.space.join(['iasl', self.common_disassemble_flags, '-oe', self.fname_gen.emit_disasm_style(style), self.fname_gen.emit_oe_filename()])

    def recompile(self, mode, style):
        return self.space.join([self.compile_common(mode), self.fname_gen.emit_disasm_name(style)+'.dsl'])

    def convert(self):
        return self.space.join(['iasl', self.common_flags, '-ca', self.main_filename])

    def binary_compare(self, test1, test2):
        return self.space.join(['acpibin -a', self.fname_gen.emit_aml_name(test1), self.fname_gen.emit_aml_name(test2)])


class aslts_builder:

    def __init__(self, test_module_path): # consume the config file
        self.commands = command_builder(test_module_path)

    def compile_test(self):
        os.system(self.commands.compile_norm(''))

    def disassembler_test_sequence(self, style):
        os.system(self.commands.compile_oe(''))
        os.system(self.commands.disassemble(style))
        os.system(self.commands.recompile('', style))
        os.system(self.commands.binary_compare('normal_compile', ''))

    def converter_test_sequence(self):
        os.system(self.commands.convert())
        os.system(self.commands.recompile('', 'convert'))
        os.system(self.commands.binary_compare('normal_compile', 'convert'))


def main ():
    args = parse_args ()
    print (args.path)
    builder = aslts_builder (args.path)
    os.chdir (args.path)
    builder.compile_test()
    builder.disassembler_test_sequence('')
    builder.converter_test_sequence()


if __name__ == '__main__':
    main()
