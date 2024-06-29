package main

import "fmt"

func main() {
	fmt.Println("HELLO WORLD!")
	server := NewServer(Config{})
	server.Start()
}
