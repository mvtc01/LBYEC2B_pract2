from tests.runner import UnitExRunner, DataReader
import pytest
import os

current_name = os.path.basename(__file__).rsplit(".py",maxsplit=1)[0].split("test_",maxsplit=1)[1]
@pytest.fixture(scope="class")
def runner():
    runner = UnitExRunner(current_name, file_ext="cpp")
    runner.compile()
    return runner

reader = DataReader("."+current_name,file_ext="ec2a",encrypted=True)
@pytest.mark.parametrize("test_input,expected", reader.get_pair_stdin_stdout())
def test_yml(runner, test_input, expected):
    assert runner.run(test_input).strip().strip('\n') == expected
     
