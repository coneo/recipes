package main

import (
        . "robot/connection"
        "log"
       )

var LoginServerAddr = "127.0.0.1:9999"

func main(){
    conn := NewTcpConn()
    err := conn.Connect(LoginServerAddr)
    if err != nil {
        log.Printf("connect login server error:%s", err)
        return
    }
    //注册关闭回调
    defer conn.Conn.Close()

    //发送登录信息到FL
    //conn.SendRawMsg()

    //接收处理FL
    conn.Recv()

    return
}
