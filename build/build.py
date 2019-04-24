import os
import subprocess
import math

OPERATIONS_DONE = 0
operations = 0

class Color:
        ''' Defines some basic colors for printing '''
        CEND      = '\33[0m'
        CBLACK  = '\33[30m'
        CRED    = '\33[31m'
        CGREEN  = '\33[32m'
        CYELLOW = '\33[33m'
        CBLUE   = '\33[34m'
        CVIOLET = '\33[35m'
        CBEIGE  = '\33[36m'
        CWHITE  = '\33[37m'

def print_color(string, color):
        ''' Prints a colored string to the print() command stream '''
        print(color + string + Color.CEND)

def ToString(value):
        ''' General ToString method to convert any value (of any type) to string '''
        res = ""
        if isinstance(value, list):
                for element in value:
                        res += ToString(element) + " "
        if isinstance(value, str):
                res = value
        if isinstance(value, int):
                res = str(value)
        return res

def Command(command, warnings):
        ''' Processes the command given in parameter. If warnings is set to True then we check for warning messages.
            Returns the result : 0 if everything went ok, 1 if there was an error and 2 if there was a warning.  '''
        result = 0
        process = subprocess.Popen(command, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        (out, err) = process.communicate()
        err = err.decode()
        if err != "":
                if (warnings == True) and ("warning" in err):
                        print_color(err, Color.CYELLOW)
                        result = 2
                if (not "warning" in err):
                        print_color(err, Color.CRED)
                        result = 1
        return result

def count_op(file):
        f = open("project.build", "r")
        count = 0
        for line in f:
                if(line.startswith("b ")):
                        count += 1
        f.close()
        return count


def buildFile(type, fileIn, fileOut, config):
        global OPERATIONS_DONE
        ''' Compiles the file given as fileIn to fileOut, taking in account the type (current build section) and the configuration previously parsed.
            Returns None if the compilation fails or if the file is not to be linked, and returns the built .o file otherwise
         '''
        command = ""
        ret = None

        # Check if the parameters are correct (fileIn exists and the config has the correct parameters)
        if(not os.path.isfile(fileIn)):
                print_color("File does not exists", Color.CRED)
                return None
        if not("includes" in config and "build_options" in config and "bin_folder" in config):
                print_color("Config not correct, exiting ...", Color.CRED)
                exit()
        
        build_config = config[type + "_build"].split(" %")
        #Check if the build configuration is correct : there is at least one input file AND one output file
        if not (("INPUT" in build_config) or ("INPUTC" in build_config)):
                print_color("Config not correct, exiting.\nThere is no INPUT or INPUTC in build config for type " + type, Color.CRED)
                exit()
        if not ("OUTPUT" in build_config):
                print_color("Config not correct, exiting.\nThere is no OUTPUT build config for file " + type, Color.CRED)
                exit()

        #Parse each build configuration for the current file : append compiler, input, output, includes and options to command
        compiler = build_config[0]
        command = compiler
        i = 1
        while i < len(build_config):
                if build_config[i] == "INPUT":
                        command += " " + fileIn
                if build_config[i] == "INPUTC":
                        command += " -c " + fileIn
                if build_config[i] == "OUTPUT":
                        command += " -o " + config["bin_folder"] + fileOut
                if build_config[i] == "OPTIONS":
                        command += " " + config["build_options"]
                if build_config[i] == "INCLUDES":
                        command += " -I" + config["includes"]
                if build_config[i] == "ADDRET":
                        ret = config["bin_folder"] + fileOut
                i += 1
        OPERATIONS_DONE += 1
        print_color( "[" + ToString(OPERATIONS_DONE) + "/" + ToString(operations) + "] compiling " + fileIn + " into " + fileOut, Color.CGREEN)

        res = Command(command, True)
        if res == 1: ret = None
        return ret

operations = count_op("project.build") + 1

f = open("project.build", "r")
type = ""
config = {}
build_file = list()
clearOnTermination = False

#Parse every line of the build file
for line in f:
        line = line.replace('\n', '')

        # Config part of the build part
        if line.startswith("[config]"):
                type = "config"

        # New section of the source code
        elif line.startswith("["):
                array = line.split(" => ")
                array[0] = array[0].replace('[', '')
                array[0] = array[0].replace(']', '')
                print_color("\nbuilding " + array[0], Color.CBLUE)
                type = array[0]

        # Build every file included in the section 
        elif line != "" and not line.startswith("#"):
                if type == "config":
                        array = line.split("=")
                        config[array[0]] = array[1]
                        if array[0] == "bin_folder":
                                print_color("Creating build folder.", Color.CWHITE)
                                Command("mkdir -p " + array[1], False)
                        if array[0] == "delete_on_termination":
                                if array[1] == "True" :  clearOnTermination = True
                                if array[1] == "False" : clearOnTermination = False
                else:
                        array = line.split("b ")
                        array1 = array[1].split(" => ")
                        #Build the current file
                        res = buildFile(type, array1[0], array1[1], config)
                        if res != None: build_file.append(res)
f.close()

OPERATIONS_DONE += 1
command = "ld " + config["linker_options"] + " " + ToString(build_file) + " -o " + config["output_kernel"]
print_color("[" + ToString(OPERATIONS_DONE) + "/" + ToString(operations) + "] Linking all files\n", Color.CGREEN)
Command(command, False)

kerr_size = os.path.getsize(config["output_kernel"])
kerr_sect = math.ceil(kerr_size/512)
print("Kernel size = " + str(kerr_size) + " bytes => " + str(kerr_sect) + " sectors to read.")

command = "cat bin/boot0.bin bin/boot1.bin kernel.bin > " + config["main_output"]
print(command)
Command(command, False)

if clearOnTermination == True:
        Command("rm -rf bin/", False)
        Command("rm -rf " + config["output_kernel"], False)
        print("Cleared project")