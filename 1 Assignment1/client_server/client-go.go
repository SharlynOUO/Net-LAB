/*****************************************************************************
 * client-go.go
 * Name:黄潇颖
 * NetId:2020201622
 *****************************************************************************/

package main

import (
	"fmt"
	"log"
	"net"
	"os"
)

const SEND_BUFFER_SIZE = 2048

const TCP = "tcp"

/* TODO: client()
 * Open socket and send message from stdin.
 */
func client(server_ip string, server_port string) {

	conn, err := net.Dial(TCP, server_ip+":"+server_port)
	if err != nil {
		log.Fatal("dial:", err)
	}
	defer conn.Close()

	buffer := make([]byte, SEND_BUFFER_SIZE)

	for {

		readbytes, _ := os.Stdin.Read(buffer)

		sendbytes, err := conn.Write(buffer[:readbytes]) // send
		if err != nil {
			fmt.Println("conn:", err)
			continue
		}
		//fmt.Println(readbytes, sendbytes)

		if sendbytes < readbytes {
			//partial sending
			res_buf := buffer[sendbytes:readbytes]
			for sendbytes < readbytes {
				res_send_bytes, res_err := conn.Write(res_buf)
				if res_err != nil {
					fmt.Println("res:", res_err)
					continue
				}
				sendbytes += res_send_bytes
			}
		}

		if readbytes == 0 {
			break
		}

	}

}

// Main parses command-line arguments and calls client function
func main() {
	if len(os.Args) != 3 {
		log.Fatal("Usage: ./client-go [server IP] [server port] < [message file]")
	}
	server_ip := os.Args[1]
	server_port := os.Args[2]
	client(server_ip, server_port)
}
