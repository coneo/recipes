package connection

import (
        "net"
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
