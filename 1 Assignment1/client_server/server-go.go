/*****************************************************************************
 * server-go.go
 * Name:黄潇颖
 * NetId:2020201622
 *****************************************************************************/

package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
)

const RECV_BUFFER_SIZE = 2048
const TCP = "tcp"

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 */
func server(server_port string) {

	buffer := make([]byte, RECV_BUFFER_SIZE)

	listen, li_err := net.Listen(TCP, "127.0.0.1:"+server_port)
	if li_err != nil {
		log.Fatal("listen:", li_err)
	}
	for {
		conn, err := listen.Accept() // 监听客户端的连接请求
		defer conn.Close()

		if err != nil {
			fmt.Println("Accept() failed, err: ", err)
			continue
		}
		revbytes, reverr := conn.Read(buffer)
		//fmt.Println(revbytes)

		for revbytes != 0 {

			if reverr != nil && reverr != io.EOF {

				fmt.Println("rev:", reverr)
				revbytes, reverr = conn.Read(buffer)
				continue
			}
			bufferwrite := buffer[:revbytes]

			writebytes, err := os.Stdout.Write(bufferwrite)
			if writebytes != revbytes || err != nil {
				fmt.Println("wirte")
				continue
			}

			revbytes, reverr = conn.Read(buffer)

		}
	}

}

// Main parses command-line arguments and calls server function
func main() {
	if len(os.Args) != 2 {
		log.Fatal("Usage: ./server-go [server port]")
	}
	server_port := os.Args[1]
	server(server_port)
}
