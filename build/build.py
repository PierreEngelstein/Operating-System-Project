import os
import subprocess
import math
def Command(command, warnings):
        ''' Processes the command given in parameter. If warnings is set to True then we check for warning messages.
            Returns the result : 0 if everything went ok, 1 if there was an error and 2 if there was a warning.  '''
        result = 0
        process = subprocess.Popen(command, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        (out, err) = process.communicate()
        err = err.decode()
        if err != "":
                if warnings == True:
                        if(not "warning" in err):
                                print("Error while compiling : \n" + err)
                                result = 1
                        else:
                                print("Compilation warning :\n" + err)
                                result = 2
                else:
                        print(err)
                        result = 1
        return result

def buildFile(type, fileIn, fileOut, config):
        ''' Compiles the file given as fileIn to fileOut, taking in account the type (current build section) and the configuration previously parsed.
            Returns None if the compilation fails or if the file is not to be linked, and returns the built .o file otherwise
         '''
        command = ""
        ret = None
        # Check if the parameters are correct (fileIn exists and the config has the correct parameters)
        if(not os.path.isfile(fileIn)):
                print("File does not exists")
                return None
        if not("includes" in config and "build_options" in config and "bin_folder" in config):
                print("Config not correct, exiting ...")
                exit()
        # Assembly file
        if(fileIn.endswith(".asm")):
                if(type == "arch_x86"):
                        command = "nasm -f bin " + fileIn + " -o " + config["bin_folder"] + fileOut
                else:
                        command = "nasm -f elf32 " + fileIn + " -o " + config["bin_folder"] + fileOut
                        ret = config["bin_folder"] + fileOut
        # C source code file
        if(fileIn.endswith(".c")):
                command = "gcc " + config["build_options"] + " -I" + config["includes"] + " -c " + fileIn + " -o " + config["bin_folder"] + fileOut
                ret = config["bin_folder"] + fileOut
        # Process the command
        print(command)
        res = Command(command, True)
        if res == 1: ret = None
        return ret

def ToString(value):
        ''' General ToString method to convert any value (of any type) to string '''
        res = ""
        if isinstance(value, list):
                for element in value:
                        res += ToString(element) + " "
        if isinstance(value, str):
                res = value
        return res

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
                print("\nbuilding " + array[0])
                type = array[0]
        # Build every file included in the section 
        elif line != "" and not line.startswith("#"):
                if type == "config":
                        array = line.split("=")
                        config[array[0]] = array[1]
                        if array[0] == "bin_folder":
                                print("Creating build folder.")
                                Command("mkdir -p " + array[1], False)
                        if array[0] == "delete_on_termination":
                                if array[1] == "True" :  clearOnTermination = True
                                if array[1] == "False" : clearOnTermination = False
                else:
                        array = line.split(" => ")
                        #Build the current file
                        res = buildFile(type, array[0], array[1], config)
                        if res != None: build_file.append(res)
f.close()

command = "ld " + config["linker_options"] + " " + ToString(build_file) + " -o " + config["output_kernel"]
print(command)
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