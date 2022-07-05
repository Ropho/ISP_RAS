# UDP/TCP SERVER/CLIENT 

## RUNNIN
    git clone https://github.com/Ropho/ISP_RAS/edit/main/TCP_UDP_SERV


    cd ./TCP_UDP_SERV/TCP (or UDP)


    run **make** in console


    run **.\main.exe server (or client)**

## Program enters either **server** regime or **client** regime based on what you specify in a command line.

### Server regime

Program is in a loop infinitely waiting for clients. When a client is connected it prints out the message.

### Client regime

Connects to a server and sends a simple message to test the work of the server.
