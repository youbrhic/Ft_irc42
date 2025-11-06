# ft_irc

A fully functional **IRC (Internet Relay Chat) server** implemented in **C++98**.  
This project is part of the **42 curriculum**, designed to help students understand **network programming**, **socket communication**, and **the IRC protocol** by implementing a real-world server.

---

## 🧠 Overview

`ft_irc` implements a simplified IRC server based on **RFC 1459** and **RFC 2812**.  
It allows multiple clients to connect, authenticate, join channels, and exchange messages — all in compliance with core IRC protocol behavior.

The project emphasizes:
- Event-driven architecture using **non-blocking sockets** and `poll()`
- Proper command parsing and client management
- Stable multi-client handling
- Clean, modular, and extensible C++ design

---

## ✨ Features

- ✅ Compliant with **RFC 1459 / RFC 2812**
- ✅ Multiple simultaneous client connections
- ✅ User and channel management
- ✅ Standard IRC commands:
  - `NICK`, `USER`, `PASS`, `JOIN`, `PART`, `PRIVMSG`, `NOTICE`, `QUIT`, `PING`, `PONG`
  - Channel commands: `TOPIC`, `MODE`, `INVITE`, `KICK`
- ✅ Operator privileges (with server password)
- ✅ Non-blocking I/O with `poll()`
- ✅ Graceful error handling and signal safety

---

## 🏗️ Project Structure


```
├── Makefile
├── README.md
├── bonus
│   ├── bot.cpp
│   └── main.cpp
├── commands
│   ├── INVITE.cpp
│   ├── JOIN.cpp
│   ├── KICK.cpp
│   ├── MODE.cpp
│   ├── NICK.cpp
│   ├── PASS.cpp
│   ├── PRIVMSG.cpp
│   ├── TOPIC.cpp
│   ├── USER.cpp
│   └── excevcmd.cpp
├── include
│   ├── Replies.hpp
│   ├── bot.hpp
│   ├── channel.hpp
│   ├── client.hpp
│   ├── data.hpp
│   └── server.hpp
└── src
    ├── channel.cpp
    ├── client.cpp
    ├── main.cpp
    └── server.cpp
```

---

## ⚙️ Installation

### 1. Clone the repository
```bash
git clone https://github.com/youbrhic/Ft_irc42
cd Ft_irc42
```
### 2. run the server
```
make
./ircserv <port> <password>
```

### 3. conntect to the server
```
nc <server_ipaddress> <port>
PASS <password>
NICK user42
USER user42 0 * :User Name
JOIN #general
PRIVMSG #general :Hello everyone!
```
