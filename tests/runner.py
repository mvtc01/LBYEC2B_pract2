import subprocess
import os
import yaml
import pickle
from assets.utilities import check_dir, convert_to_string
outputdir = 'bin'


class TestExerciseGenerator(object):
    def __init__(self):
        pass

    def create_test_file(self, ex_name):
        template = \
'''
from tests.runner import UnitExRunner, DataReader
import pytest

@pytest.fixture(scope="class")
def runner():
    runner = UnitExRunner("{}")
    runner.compile()
    return runner

reader = DataReader(".{}")
@pytest.mark.parametrize("test_input,expected", reader.get_pair_stdin_stdout())
def test_yml(runner, test_input, expected):
    assert runner.run(test_input).strip().strip("\n") == expected
'''.format(ex_name, ex_name)
        return template



class DataReader(object):
    def __init__(self, filename, pathdir=None, file_ext="yml", encrypted=True):
        if pathdir is None:
            pathdir = os.path.dirname(os.path.abspath(__file__))            

        self.pathdir = check_dir(pathdir,projectdir=False)

        self.full_input = os.path.join(self.pathdir,filename+"."+file_ext)

        self.isencrypted = encrypted

        self.read_file()
        


    def read_file(self):
        if self.isencrypted:
            with open(self.full_input, 'rb') as file:
                self.document = pickle.load(file)
        else:
            with open(self.full_input, 'r') as f:
                self.document = yaml.full_load(f)

    def check_valid_format(self):
        # TODO: check whether the yml file is valid format in all keys
        pass
    
    def _extract_value(self, document, key, require=False):
        result = None
        try:
            result = convert_to_string(document[key])
        except KeyError as e:
            if require:
                raise
            else:
                print("Test Case do not have stdin...")
        return result
        
    def get_pair_stdin_stdout(self):
        # If stdin is an array parse it into one big string
        test_pairs = []
        for number, run in self.document.items():
            input_values = self._extract_value(run, "stdin")
            expected_result = self._extract_value(run, "stdout", require=True)

            test_pairs.append((input_values,expected_result))
            
        return test_pairs


class UnitExRunner(object):
    '''
        This class wants to focus on one unit exercise
    '''
    opts = {
        'c': {'compiler': 'clang',
              'standard': 'c11'},
        'cpp': {'compiler': 'clang++',
              'standard': 'c++11'}
            }
    def __init__(self, filename, pathdir=None, file_ext="c", files=None):

        # Get current project directory
        self.pathdir = check_dir(pathdir)
        self.file_ext = file_ext     
        full_output_dir = os.path.join(self.pathdir,outputdir)

        if not os.path.exists(full_output_dir):
            print("Creating bin directory...")
            os.mkdir(full_output_dir)


        # full path
        self.full_input = os.path.join(self.pathdir,filename+"."+file_ext)
        self.full_output = os.path.join(full_output_dir,filename)

        if files is not None:
            self.full_input = [os.path.join(self.pathdir, "main."+ file_ext)]
            extrasrcfiles = [os.path.join(self.pathdir, extrafile + "." + file_ext) for extrafile in files]
            self.full_input = self.full_input + extrasrcfiles

    def isvalid_file(self, input):
        '''Check if the file full path is valid'''
        #TODO
        pass

    def compile(self):

        #TODO: check if clang exists
        cmd = [self.opts[self.file_ext]['compiler'],"-std="+self.opts[self.file_ext]['standard'],"-lm","-ggdb",self.full_input,"-o",self.full_output]
        print(cmd)
        subprocess.run(cmd)

        #TODO: Check if compilation is successful

        return 



    def run(self, inputs):
        '''Run the successfully compiled program'''
        err = ""        
        output = ""

        #If it is a list,dict,tuple, Combine the elements into one big string 
        input_combined = convert_to_string(inputs)

        proc = subprocess.Popen(self.full_output,stdout=subprocess.PIPE,stdin=subprocess.PIPE)

        output, err = proc.communicate(input=input_combined.encode('utf-8'))
        # output = subprocess.run("./"+file, shell=True, stdin=input_num, stdout=subprocess.PIPE).stdout.decode("utf-8")
        return output.decode()
    
    def compile_and_run(self, inputs):
        self.compile()
        return self.run(inputs)


    def test(self):
        self.compile()
        return self.run([2])


if __name__ == "__main__":

    ex1 = UnitExRunner("ex1")

    print(ex1.test())
