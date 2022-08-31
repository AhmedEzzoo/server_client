This is the description and the instruction for running the Car Realtime Monitoring designed by Ahmed Ezz as a Capstone Project in the Udacity C++ Nanodegree program in September 2021.

The project is built out of curiosity to visualize realtime Car monitorin system. this version is used in similar applications can contribute to watch and detect the overall condition of car, especially taking into account problems of roads.

Project Description – Car Realtime Monitoring System (MultiThreading Clients)
    The goal of the project is to track and display all Cars and trucks units operating at the current real time. The project suppose to receive data from embedded or controller is installed in vechile which going to be monitored to track realtime condition of speed, engine temperature and oil level and then controller pushes these data to this server to store and display it but for simulating purposes I made it as virtual client pushing data every 3 seconds.

    The monitored units include:   Random => Speed, Engine Temp. and Oil Temp

    According to simulation purpose, the virtual client API is passing data every 3 seconds to server, then server displays it in max 5 browser clients with websocket chat rooms with server.


Project Structure and Logic
    - Server.cpp is the file controlling the application. The application's logic is described below:

    - Set up Server via creating an instance of Server class with all required Attributes like IP and Port number of the server  (required by websocket API). 

    - Set up Client via creating an instance of Client class (required by websocket API) 
    with the IP of server and port no. of the server to connect with this server

    - Initiate infinit loop thread for Server to start up server first then start another infinit loop thread for Client to connect to Server. 

    - Now Server is waiting for connection from clients to handle it and make another infinit loop thread to get data from client after accepting the connection.

    - Server check the data if it receives data from client and guid the programe to excute the proper response for this data.

    - Application has 5 types of data handling 
        1- response to GET / Request from browser client.
        2- response to GET /chat websocket response from browser client .
        3- getting reading every 3 seconds from virtual client .
        4- publish the received data from virtual to all browser clients with real time reading received.
        5- handling the data which received when client closed or shuts down or something wrong happened with this certian client. 

    - user can press Enter Key on terminal in any time to shut down server and virtual client and release resources.


Expected Behavior :
    After the application is launched, Virtual Client will connect to server and Server will accept connection, So Client will start to push String of data every 3 seconds.
    User should open his browser (Chrome, Firefox, Opera) and type the IP(127.0.0.1) with port 80, So user could write it like (127.0.0.1:80) or write his device IP if he wants to access the server from another device in local network.
    User will be able to see the real time readings on the browser and also monitor these readings in Terminal 

Dependencies for Running Locally
    cmake >= 3.7

make >= 4.1 (Linux, Mac), 3.81 (Windows)
    Mac: install Xcode command line tools to get make
    Linux: make is installed by default on most Linux distros
    Windows: Click here for installation instructions

gcc/g++ >= 5.4
    Mac: same deal as make - install Xcode command line tools
    Linux: gcc / g++ is installed by default on most Linux distros
    Windows: recommend using MinGW

OpenSSL >= (general installation instructions)
    Mac
    Linux suppose to be installed by default
    Windows
C++ REST SDK, formerly known as Casablanca (GitHub page). The library requires installation of development files for OpenSSL. Depending on your machine, please read detailed installation instructions for:
    Mac
    Linux
    Windows


Build Instructions
    After installing project dependencies, please proceed to build:

    Make a build directory in the top level directory: mkdir build && cd build
    Compile -> Step 1: cmake .. (should you have hard times linking the OpenSSL library, please tell cmake where OpenSSL files are located on your machine. Make sure to do it prior to calling cmake ..

    Compile -> Step 2: make

    Run the application: ./Server


Udacity Capstone Project Requirements – Rubric Points Addressed
    Below is the description of how Udacity project requirements are fulfilled.

1. README (All Rubric Points REQUIRED)
    A README with instructions is included with the project
    Yes: README.md file included into the project root folder.
    The README indicates which project is chosen
    Yes: see section "Project Description" in the README.md file.
    The README includes information about each rubric point addressed
    Yes.

2. Compiling and Testing (All Rubric Points REQUIRED)
    The submission must compile and run
    Yes.

3. Loops, Functions, I/O
    The project demonstrates an understanding of C++ functions and control structures
    Yes.
    The project reads data from a file and process the data, or the program writes data to a file
    Yes & No: the project is designed to read and process data from html file and  stream send it via the HTTP request (see Server.h::47 and Server.cpp::29, 138).
    The project accepts user input and processes the input
    Yes.

4. Object Oriented Programming
    The project uses Object Oriented Programming techniques
    Yes: see Server.h, SocketConnection.h, SocketBinding.h, Socket.h, SocketListening.h, HttpMainPage.h as well as all respective .cpp files.

    Classes use appropriate access specifiers for class members
    Yes.

    Class constructors utilize member initialization lists
    Yes: please see e.g. constructor Socket::Socket() in Socket.cpp, constructor Server::Server() in Server.cpp and constructor SocketListening::SocketListening() in SocketListening.cpp.

   Classes abstract implementation details from their interfaces
   Yes.

   Classes encapsulate behavior
   Yes: e.g. MessagesExchange::Simulate() in MessagesExchange.h

    Classes follow an appropriate inheritance hierarchy
    Yes: SocketBinding, SocketListening classes are implemented in this project.

    Overloaded functions allow the same function to operate on different parameters
    NO
    
    Derived class functions override virtual base class functions
    Yes: Socket::network_connect in Socket.h

    Templates generalize functions in the project
    NO

5. Memory Management
    The project makes use of references in function declarations
    Yes: see e.g. in Server.h client_closed_or_problem(int &cli_sock);

    The project uses destructors appropriately
    Yes: see e.g. Client::~Client() in Client.cpp; using new-delete in one place =>Server::send_to_http_socket_data(std::string const buff_to_send, int &cli_sock) at Server.cpp::209 , the project uses smart pointers aswell.

    The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate
    Yes: see std::unique_ptr<SocketListening> sock_listen  in Server.h::63 and std::unique_ptr<HttpMainPage> serv_main_page in Server.h::66.

    The project follows the Rule of 5
    No: smart pointers are used instead.

    The project uses move semantics to move data, instead of copying it, where possible
    Yes: see Server::server_connection_handle () in Server.cpp::55

    The project uses smart pointers instead of raw pointers
    Yes & No: smart pointers are used in PublicTransport.h::20, PublicTransport.h::23, but simple raw pointers (neither malloc nor new) are used for learning purposes in Server.h::31, MessagesExchange.h

6. Concurrency
    The project uses multithreading
    Yes: a multithreading setup added to MessagesExchange::recv_data() in MessagesExchangecpp::15.
    
    A promise and future is used in the project
    No
    A mutex or lock_guard is used in the project
    Yes.
    A condition variable is used in the project
    No.