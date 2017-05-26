#!/usr/bin/python3
import os
import sys
import shutil
import subprocess
import re
import argparse
import importlib
import collections


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
        return ['oe_' + self.name + '.aml']

    def emit_disasm_name(self, style):
        if style == 'legacy':
            return self.name + '-aslminus'
        elif style == 'convert':
            return 'MAIN'
        else:
            return self.name + '-aslplus'

    def emit_disasm_dsl_name(self, style):
        return [self.emit_disasm_name(style) + '.dsl']

    def emit_disasm_style(self, style):
        if style == 'legacy':
            return ['-dl', '-p', self.emit_disasm_name(style)]
        else:
            return ['-d', '-p', self.emit_disasm_name(style)]

    def emit_aml_name(self, aml_kind):
        if aml_kind == 'normal_compile':
            return [self.name + '.aml']
        if aml_kind == 'oe':
            return ['oe_' + self.name + '.aml']
        elif aml_kind == 'convert':
            return ['MAIN.aml']
        elif aml_kind == 'disassemble_legacy':
            return [self.emit_disasm_name('legacy') + '.aml']
        else:
            return [self.emit_disasm_name('') + '.aml']

    def emit_compile_artifacts(self, compilation_mode):
        if compilation_mode == 'norm':
            fname = self.name
        elif compilation_mode == 'oe':
            fname = 'oe_' + self.name
        else:
            fname = self.emit_disasm_name(compilation_mode)
        return list(map(lambda x: fname + x,['.asm','.c','.h','.hex','.i','.lst','.map','.nap','.nsp','.offset.h','.src']))


class artifact_path_builder:
    def __init__(self):
        print ("current dir: " + os.getcwd())
        output = subprocess.check_output(['iasl','-v'])
        version = re.search('(?<=version )\w+', output.decode("utf-8")).group(0)
        self.test_directory_path = os.getcwd() + '/tmp/aml/' + version + '/'
        if not os.path.exists(self.test_directory_path):
            os.makedirs(self.test_directory_path)

        # set up aml directories for each mode if it does not exist

        for mode_name in ['nopt/32', 'nopt/64', 'opt/32', 'opt/64']:
            if not os.path.exists(self.test_directory_path + mode_name + '/'):
                os.makedirs(self.test_directory_path + mode_name + '/')

        # set up log files for compilation

        try:
            self.compiler_log = open(self.test_directory_path+'compile.txt', 'r')
        except FileNotFoundError:
            self.compiler_log = open(self.test_directory_path+'compile.txt', 'w')
        try:
            self.error_log = open(self.test_directory_path+'error.txt', 'r')
        except FileNotFoundError:
            self.error_log = open(self.test_directory_path+'error.txt', 'w')

    def get_aml_mode_path(self, mode):
        if mode == 'opt/32' or mode == 'opt/64' or mode == 'nopt/32' or mode == 'nopt/64':
            return self.test_directory_path + '/' + mode + '/'

    def copy_aml (self, aml_file, mode):
        index = aml_file.rfind("/")
        if index > -1:
            aml_fname = module_path[index:]
        else:
            aml_fname = aml_file
        shutil.copyfile(aml_file, self.get_aml_mode_path(mode) + aml_fname)


class command_builder:

    # constant flags

    common_flags = ['-cr','-vs']
    common_compile_flags = common_flags + ['-of','-l','-sc','-sa','-ic','-ta','-ts','-so','-lm','-ln','-ls','-li']
    common_disassemble_flags = ['-od']
    main_filename = ['MAIN.asl']
    asl_compiler = ['iasl']

    def __init__(self, path):
        module_path = path.replace('/','.')
        if not(module_path.endswith('.')):
            module_path += '.'
        index = module_path.find("aslts")
        if index > -1:
            module_path = module_path[index + len("aslts."):]
        self.testcase_config = importlib.import_module(module_path + 'testConfig')
        self.fname_gen = filename_generator(self.testcase_config.name)

        self.Command_and_artifact = collections.namedtuple('Command_and_artifact', ['command', 'artifact'])

    def mode_to_flags(self,mode):
        if mode == 'opt/32':
            return ['-r','1']
        elif mode == 'opt/64':
            return ['-r','2']
        elif mode == 'nopt/32':
            return ['-oa','-r','1']
        elif mode == 'nopt/64':
            return ['-oa','-r','2']
        else:
            return []

    def compile_common(self, mode):
        return self.asl_compiler + self.common_compile_flags + self.testcase_config.compile_flags + self.mode_to_flags(mode)

    def compile_with_mode(self, style, mode):
        compile_command = self.compile_common(mode)
        if style == 'oe':
            compile_command += ['-oE'] + ['-p'] + self.fname_gen.emit_aml_name('oe') + self.main_filename
            resulting_aml = self.fname_gen.emit_aml_name('oe')[0]
        elif style == 'norm':
            compile_command += ['-p'] + [self.fname_gen.name] + self.main_filename
            resulting_aml = self.fname_gen.emit_aml_name('normal_compile')[0]
        return self.Command_and_artifact(command = compile_command, artifact = resulting_aml)

    def compile_norm(self, mode):
        return self.compile_with_mode('norm', mode)

    def compile_oe(self, mode):
        return self.compile_with_mode('oe', mode)

    def recompile(self, mode, style):
        return self.compile_common(mode) + self.fname_gen.emit_disasm_dsl_name(style)

    def disassemble(self, style):
        return self.asl_compiler + self.common_disassemble_flags + ['-oe'] + self.fname_gen.emit_disasm_style(style) + self.fname_gen.emit_aml_name('oe')

    def convert(self):
        return self.asl_compiler + self.common_flags + ['-ca'] + self.main_filename

    def binary_compare(self, aml1, aml2):
        return ['acpibin'] + ['-a'] + self.fname_gen.emit_aml_name(aml1) + self.fname_gen.emit_aml_name(aml2)

    def cleanup(self, command):
        if command == 'compile_norm':
            compile_mode = 'norm'
        elif command == 'oe_compile':
            compile_mode = 'oe'
        elif command == 'recompile_legacy':
            compile_mode = 'legacy'
        elif command == 'recompile_plus':
            compile_mode = 'plus'
        else:
            compile_mode = ''
        return ['rm'] + ['-f'] + self.fname_gen.emit_compile_artifacts(compile_mode)

class aslts_builder:

    def __init__(self, test_module_path): # consume the config file
        self.commands = command_builder(test_module_path)
        self.artifacts = artifact_path_builder()

    def logged_call(self, command):
        subprocess.call(command, stdout = self.artifacts.compiler_log, stderr = self.artifacts.error_log)

    def compile_one_mode(self, mode):
        command_and_artifact = self.commands.compile_norm(mode)
        self.logged_call(['rm', command_and_artifact.artifact])
        self.logged_call(command_and_artifact.command)
        self.artifacts.copy_aml(command_and_artifact.artifact, mode)
        self.logged_call(self.commands.cleanup('compile_norm'))

    def compile_test(self):
        list(map(lambda x: self.compile_one_mode(x), ['opt/32', 'opt/64', 'nopt/32', 'nopt/64']))

    def disassembler_test_sequence(self, style):
        self.logged_call(self.commands.compile_oe(''))
        self.logged_call(self.commands.disassemble(style))
        self.logged_call(self.commands.recompile('', style))
        self.logged_call(self.commands.binary_compare('normal_compile', ''))

    def converter_test_sequence(self):
        self.logged_call(self.commands.convert())
        self.logged_call(self.commands.recompile('', 'convert'))
        self.logged_call(self.commands.binary_compare('normal_compile', 'convert'))


def main ():
    args = parse_args ()
    old_dir = os.getcwd()

    if os.path.basename(os.getcwd()) != 'aslts':
        os.chdir('aslts')
    builder = aslts_builder (args.path)
    os.chdir (args.path)

    builder.compile_test()
    #builder.disassembler_test_sequence('')
    #builder.converter_test_sequence()

    os.chdir (old_dir)


if __name__ == '__main__':
    main()
