package main

import (
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/", HandleRequests)
	log.Fatal(http.ListenAndServe(":10000", nil))
}
