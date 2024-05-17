package main

import (
	"log"
	"net/http"
)

func main() {
	http.HandleFunc("/track", HandleRequests)
	log.Fatal(http.ListenAndServe(":8080", nil))
}
