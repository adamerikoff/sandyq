package main

import (
	"encoding/json"
	"fmt"
	"net/http"
)

type GetResponse struct {
	Message string         `json:"message"`
	Body    []TrackingInfo `json:"body"`
}
type PostResponse struct {
	Message string `json:"message"`
}

func handleGet(w http.ResponseWriter, _ *http.Request) {
	response := GetResponse{
		Message: "Hello, World! This is a GET request.",
		Body:    TrackingInfoDB,
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)
}

func handlePost(w http.ResponseWriter, r *http.Request) {
	var data TrackingInfo
	if err := json.NewDecoder(r.Body).Decode(&data); err != nil {
		http.Error(w, "Failed to decode request body", http.StatusBadRequest)
		return
	}
	fmt.Printf("Received tracking info via POST: %+v", data)
	response := PostResponse{Message: "Received tracking info via POST."}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)
}

func HandleRequests(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		handleGet(w, r)
	case http.MethodPost:
		handlePost(w, r)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}
