import os

def check_dir(origdir,projectdir=True):
    # If None, use directory of the file
    pathdir = ""
    if origdir:
        pathdir = origdir
    else:
        if projectdir:
            pathdir = os.path.join(os.path.dirname(os.path.abspath(__file__)),'..')
        else:
            pathdir = os.path.dirname(os.path.abspath(__file__))
    
    return pathdir

def validate_file_ext(filename, file_ext):
    return filename.rsplit("." + file_ext,1)[0] + "." + file_ext



def convert_to_string(arrays, sep='\n'):
    input_combined = str(arrays)
    if isinstance(arrays, list) or isinstance(arrays, dict) or isinstance(input, tuple):
        input_combined = sep.join([str(i) for i in arrays])
    return input_combined
