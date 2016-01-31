package client

import (
        "fmt"
        "net"
        "bufio"
       )

type Client struct {
    Id      uint64
    Name    string
    Conn    net.Conn
    Ch      chan string
}

func (c Client) ReadLinesInto(ch chan<- string) {
    bufc := bufio.NewReader(c.Conn)
    for {
        line, err := bufc.ReadString('\n')
        if err != nil {
            break
        }
        ch <- fmt.Sprintf("%s:%s", c.Name, line)
    }
}

