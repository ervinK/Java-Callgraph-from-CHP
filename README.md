# Java-Callgraph-from-CHP
### Introducing

This project is created for extend the capability of the Call Hierarchy Printer.
Original project: https://github.com/pbadenski/call-hierarchy-printer .
CHP is for mapping hierarchy of method calls for a given method. As I mentioned, this program uses CHP for every single method in a project and reduce the possible redundancy from the ouput. 

### Usage

There is a `startcg.sh` file which leads the project. The bash-script file needs 3 parameters:
1. The root directory of the project
2. Path for folder of class files
3. Path for folder of src directory or that dir what is conatins the packages

**Example**
If there is a project and the directory hierarchy like: Test/bin/classes..... , Test/src/sourcefiles.....
You need to type:
`./startcg Test Test/bin Test/src`




