# intern2
c++, 2023 Summer Intern Baidu Apollo Autonomous Driving Project at ISCAS, Beijing [[paper](https://drive.google.com/file/d/1QpBO1KFtsDsGNAb7DDbin5JoYx22LSGF/view) | [code](https://github.com/yanhao5103233729/intern2) | [video](https://youtu.be/3sck9b50zp4)]

See my [homepage](https://yanhao5103233729.github.io/edu/) for more details.

## Project Overview
This project involves the development of a path planning system using high-precision map data. The primary goal is to implement an efficient algorithm for path planning using protobuf for map data parsing. The system processes various data structures, including kd-trees, to facilitate effective map representation and route calculation.

## Objectives and Task Breakdown
**Goal**: To read high-precision map data and implement a path planning algorithm.

**Tasks and Outcomes**:
0. **Programming Languages**: Use C++(primary) and Python for implementation.

1. **Map Parsing**: Utilize protobuf for reading map files.
<img src="./img/outcomes1.png" alt="Example Image" width="50%">

2. **Data Structuring**: Design data structures to store map data post-parsing and construct kd-trees.
<img src="./img/outcomes2.png" alt="Example Image" width="50%">

3. **Map Visualization**: Attempt to display maps using graphical libraries.
<img src="./img/outcomes3.png" alt="Example Image" width="50%">

4. **Route Identification**: Identify roads and subsequent path points based on input coordinates.
<img src="./img/outcomes4.png" alt="Example Image" width="50%">


## Installation

### Prerequisites
- C++(primary) and Python environments
- [Ubuntu 20.04](https://www.releases.ubuntu.com/20.04/)
- [Protobuf library](https://github.com/protocolbuffers/protobuf/)

### Steps
1. Clone the repository
2. Navigate to the project directory
3. (Optional) Set up a virtual environment
4. Install the required dependencies

## Usage
1. Compile the C program: ```g++ -o read_basemap read_basemap.cc```
2. Run the compiled executable: ```./read_basemap```
3. Follow the on-screen instructions for map parsing, data structuring, map visualization, and route identification.

## Contributing
To contribute to this project:
1. Fork the repository.
2. Create a new branch for your features or fixes.
3. Commit your changes.
4. Push to your branch.
5. Create a pull request.

More details on contributions can be found in the GitHub guide on [creating a pull request](https://docs.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).

## License
This project is licensed under the [MIT License](LICENSE.md) - see the LICENSE file for details.
