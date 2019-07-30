# JSON Parser

JSON Parser written in C++ using rapidjson library.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

Since the files present are not in a proper JSON format, an opening and closing square bracket - [ ] has been added in the start and end of all the files respectively. This makes it easier for the library to parse the json files.

### Installing

The code has been written in Visual Studio 2019. Any IDE could be used, but all the configurations required will be explained with respect to Visual Studio.

The following configurations are required:

* Clone or download the rapidjson library from https://github.com/Tencent/rapidjson.
* Add the /include path of the rapidjson directory to "Include Directories" of the project. (Project -> Properties -> C/C++ -> Additional Include Directories.
* Download the json files from https://sites.google.com/view/jiazou-web/assignment?authuser=0
* Add the base path of the above files to the command line arguments to the project. (Project -> Properties -> Debugging -> Command Arguments)


## Outputs

Since the ouput for large and medium are pretty big, they have been added as results to the github repo along with the time taken to run each of them.

## Task 2

* Counters were used to find the answers to all the queries in a single pass.
* Used an input stream (from the rapidjson library) to load the entire json in memory.
* Tried to use the simdjson parser to leverage vectorized processing, but I'm still facing some issues with it, so I decided to go with rapidjson. I also tried using jconcpp library, but rapidjson worked much more efficiently for the bigger files.

## Task 3

System configuration:
* Number of cores: 4
* Size of Physical Memory: 8GB
* Type Of Disk: NVMe SSD
* OS: Win 10

I used the performance analyzer in Visual Studio to find the performance bottleneck and found that the program is I/O intensive and the most expensive operations were parsing the json and iterating over it.

