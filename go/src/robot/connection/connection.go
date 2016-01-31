package connection

import (
        "net"
        "fmt"
       )

import (
        . "robot/message"
       )

type TcpConnection struct {
    Id      uint64
    Name    string
    Conn    net.Conn
    Ch      chan string
}

//新建一个tcp连接
func NewTcpConn() *TcpConnection {
    tcpconn := new(TcpConnection)

    return tcpconn
}

//连接指定host
func (conn *TcpConnection) Connect(host string) error {
    c, err := net.Dial("tcp", host)
    if err != nil {
        return err
    }
    conn.Conn = c
    return nil
}

//接收消息
func (conn *TcpConnection) Recv()(*Message, error) {
    msg := new(Message)
    msg.Reserve()
    _,err := conn.Conn.Read(msg.Data)
    if err != nil {
        fmt.Println("recv err:%s", err)
        return nil, err
    }
    return msg, nil
}

//发送消息 包括原始结构体和proto
func (conn *TcpConnection) Send(msg *Message) error {

    //对Message进行加密压缩，然后发送

    _,err := conn.Conn.Write(msg.Data)
    if err != nil {
        fmt.Println(err)
    }
    return nil
}
