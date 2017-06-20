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

    common_compile_flags = ['-cr','-vs','-of']
    all_output_flags = ['-l','-sc','-sa','-ic','-ta','-ts','-so','-lm','-ln','-ls','-li']
    common_disassemble_flags = ['-od'] + ['-oe']
    main_filename = ['MAIN.asl']
    asl_compiler = ['iasl']

    mode_to_flags = {'opt/32':['-r','1'],'nopt/32':['-oa','-r','1'], 'opt/64':['-r','2'], 'nopt/64':['-oa','-r','2']}
    disasm_flag = {'asl':['-dl'], 'asl+':['-d']}

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

        ###
        # Various dictionaries used for compilation
        ###

        # Common compile flags -- these flags are common to any compilation that is done in this script
        self.compile_common = self.asl_compiler + self.common_compile_flags + self.testcase_config.compile_flags

        # this contains special compilation flags
        self.special_compilation_flags = {'compile_norm': self.all_output_flags,
                                          'compile_oe':['-oE'],
                                          'recompile':[],
                                          'compileConvert':[]}

        # these dictionaries contain file input names and file output prefixes for the commands
        self.input_file = {'mainAsl':['MAIN.asl'],
                           'mainDsl':['MAIN.dsl'],
                           'disasmDsl':[self.testcase_config.name + '-disasm.dsl'],
                           'disasmAml':[self.testcase_config.name + '-disasm.aml'],
                           'disasmOeAml':['oe-' + self.testcase_config.name + '.aml']}

        self.input_compile_file = {'compile_norm':self.input_file['mainAsl'],
                                   'compile_oe':self.input_file['mainAsl'],
                                   'recompile':self.input_file['disasmDsl']}

        prefix = ['-p']
        self.output_prefix = {'compile_norm':prefix + [self.testcase_config.name],
                              'compile_oe':prefix + ['oe-' + self.testcase_config.name],
                              'recompile':[],
                              'cv':[],
                              'disassemble':prefix + [self.testcase_config.name + '-disasm']}

        # these dictionaries contain resulting aml or dsl filenames
        self.aml_compilation_artifacts = {'compile_norm': self.output_prefix['compile_norm'][1] + '.aml',
                                          'compile_oe': self.output_prefix['compile_oe'][1] + '.aml',
                                          'recompile':'',
                                          'compileConvert':''}

        # the line below might be unnecessary. Leave this comment as a reminder that I can switch over to using a dictionary for this...
        # self.disassembly_artifacts = {'disassemble': self.output_prefix['disassemble'][1] + '.dsl'}

        # this dictionary contains resulting artifacts other than aml files
        self.other_compilation_artifacts = \
            {'compile_norm':list(map(lambda x: self.output_prefix['compile_norm'][0] + x,
                ['.asm','.c','.h','.hex','.i','.lst','.map','.nap','.nsp','.offset.h','.src'])),
             'compile_oe':[]}


    def compile_common(self, mode):
        return self.asl_compiler + self.common_compile_flags + self.testcase_config.compile_flags + self.mode_to_flags[mode]

    def compile_with_mode(self, style, bitmode):
        compile_command = self.compile_common + self.mode_to_flags[bitmode]
        compile_command += self.special_compilation_flags[style]
        compile_command += self.output_prefix[style] + self.input_compile_file[style]

        return self.Command_and_artifact(command = compile_command, artifact = self.aml_compilation_artifacts[style])

    def compile_norm(self, bitmode):
        return self.compile_with_mode('compile_norm', bitmode)

    def compile_oe(self, bitmode):
        return self.compile_with_mode('compile_oe', bitmode)

    def recompile(self, bitmode):
        return self.compile_with_mode('recompile', bitmode)

    def disassemble(self, style):
        return self.Command_and_artifact(
                   command = self.asl_compiler + self.common_disassemble_flags +
                       self.disasm_flag[style] + self.output_prefix['disassemble'] +
                       self.input_file['disasmOeAml'],
                   artifact = self.output_prefix['disassemble'][1] + '.dsl')

    def convert(self):
        return self.asl_compiler + self.common_flags + ['-ca'] + self.main_filename

    def binary_compare(self, aml1, aml2):
        return ['acpibin'] + ['-a'] + self.fname_gen.emit_aml_name(aml1) + self.fname_gen.emit_aml_name(aml2)

    def cleanup(self, style):
        files_to_remove = self.other_compilation_artifacts[style]
        if style != []:
            return ['rm'] + ['-f'] + files_to_remove
        else:
            return ['']

class aslts_builder:

    def __init__(self, test_module_path): # consume the config file
        self.commands = command_builder(test_module_path)
        self.artifacts = artifact_path_builder()

    def logged_call(self, command):
        return subprocess.call(command, stdout = self.artifacts.compiler_log, stderr = self.artifacts.error_log)

    def compile_one_mode(self, mode):
        command_and_artifact = self.commands.compile_norm(mode)
        self.logged_call(['rm', command_and_artifact.artifact])
        print ('    type: ' + mode, end=' ')
        self.logged_call(command_and_artifact.command)
        print('compile =>', end=' ')
        if os.path.exists(command_and_artifact.artifact):
            print('PASS')
        self.artifacts.copy_aml(command_and_artifact.artifact, mode)
        self.logged_call(self.commands.cleanup('compile_norm'))

    def compile_test(self):
        result = list(map(lambda x: self.compile_one_mode(x), ['opt/32', 'opt/64', 'nopt/32', 'nopt/64']))
        if all(value == None for value in result):
            print ('compilation test - PASS')
        else:
            print ('compilation test - FAIL')

    def disassembler_test_sequence(self, style):
        print('compile with externals')
        mode = 'nopt/64'
        command_and_artifact = self.commands.compile_oe(mode)
        self.logged_call(['rm', command_and_artifact.artifact])
        print ('    type: ' + mode, end=' ')
        self.logged_call(command_and_artifact.command)
        print('compile with externals =>', end=' ')
        if not(os.path.exists(command_and_artifact.artifact)):
            print('FAIL')
        self.logged_call(self.commands.cleanup('compile_oe'))

        command_and_artifact = self.commands.disassemble('asl+')
        self.logged_call(command_and_artifact.command)
        command_and_artifact = self.commands.recompile(mode)
        self.logged_call(command_and_artifact.command)


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
    builder.disassembler_test_sequence('')
    #builder.converter_test_sequence()

    os.chdir (old_dir)


if __name__ == '__main__':
    main()
