package message

var ChunkSize = 64 * 1024 * 1024

type Message struct {
    Data    []byte
    Length  uint32
}

func (msg *Message) Reserve() {
    msg.Data = make([]byte, ChunkSize)
}
