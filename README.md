## murmur
multi-user server-client chat program designed to run on a raspberry pi
## about
This is a personal project to build a C++ networked application which can handle simultaneous network requests from multiple users.
I'm making this from scratch based on an assignment which introduced networks and threads to me in my 3rd year of university.
This will be a from-scratch rewrite of that C program with more contemporary coding practices employed such as:

- Switching to C++ and fully utilizing the benefits over C (RAII, threading packages, std lib to replace byte and buffer concerns, ect.)
- Move peer-to-peer LAN model to a client-server ran over ethernet
- Persistent server running on a raspberry pi allowing users to connect when ever they want

## architecture
- server: multithreaded TCP, maintains a client list, recieves messages from all users and broadcasts messages to users, all input/output from server will be non-blocking to prevent slow users from holding up other clients
- client: connects to server. will work almost identically in terms of architecture to the peer-to-peer architecture

## status
developing step 1

## roadmap
- [ ] Single-threaded TCP echo server and client
- [ ] Multi-client support with thread-per-connection
- [ ] Broadcast logic across connected clients
- [ ] Thread-safe message queues
- [ ] Username support and join/leave notifications
- [ ] Deploy to Raspberry Pi under systemd
