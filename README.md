# Java-Callgraph-from-CHP
### Introducing

JCGCHP is for create call graph for a java project.
The project is created for extend the capability of the Call Hierarchy Printer.
Original project: https://github.com/pbadenski/call-hierarchy-printer .
CHP is for mapping hierarchy of method calls for a given method. As I mentioned, this program uses CHP for every single method in a project and reduce the possible redundancy from the ouput. 

### Usage

There is a `startcg.sh` file which leads the project. The bash-script file needs 3 parameters:
1. The root directory of the project
2. Path for folder of class files
3. Path for folder of src directory or that dir what is conatins the packages

**Example**
If you want to analyze a project, just drag and drop its folder to this project's root.
So, there is a project and the directory hierarchy like: Test/bin/classes..... , Test/src/sourcefiles.....
You need to type:
`./startcg.sh Test Test/bin Test/src`

### Output
The output format is similar to the CHP's. But since it is a method **HIERARCHY** builder, to call it to every single method causes redundancy. Fortunately the subcalled methods are originally tabulated in the CHP, so the output of this project is filtered by this. The output is directed to the `output.txt` . 

### Test contents
This repository has an example folder `ExampleOutputs` and example projects. 




