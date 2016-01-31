package main

import (
        "robot/client"
        "fmt"
        "log"
        "net"
        "os"
       )

func main() {
    ln, err := net.Listen("tcp", ":6000")
    if err != nil {
        fmt.Println(err)
        os.Exit(1)
    }

    msgchan := make(chan string)
    addchan := make(chan client.Client)
    rmchan := make(chan client.Client)

    go handleMessages(msgchan, addchan, rmchan)

    for {
        conn, err := ln.Accept()
        if err != nil {
            fmt.Println(err)
            continue
        }

        go handleConnection(conn, msgchan, addchan, rmchan)
    }
}

func handleConnection(c net.Conn, msgchan chan<- string, addchan chan<- client.Client, rmchan chan<- client.Client) {

    defer c.Close()
    client := client.Client{
        Id: 1,
        Conn:   c,
        Ch:     make(chan string),
        Name: "testname",
    }

    //注册client
    addchan <- client
    defer func() {
        log.Printf("Connection from %v closed.\n", c.RemoteAddr())
    }()


    msgchan <- fmt.Sprintf("new user joined.\n")

    go client.ReadLinesInto(msgchan)
    fmt.Printf("Connection from %v closed.\n", c.RemoteAddr())
}

func handleMessages(msgchan <-chan string, addchan <-chan client.Client, rmchan <-chan client.Client) {
    clients := make(map[net.Conn]chan<- string)

    for {
        select {
        case msg := <- msgchan:
                 log.Printf("new message: %s", msg)
                 for _, ch := range clients {
                     go func(mch chan<- string) {
                         mch <- msg
                     }(ch)
                 }
        case client := <- addchan:
                     log.Printf("new client:%v\n", client.Conn)
                     clients[client.Conn] = client.Ch
        case client := <- rmchan:
                     log.Printf("client disconnect:%v\n", client.Conn)
                     delete(clients, client.Conn)
        }
    }
}
