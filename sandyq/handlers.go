package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"

	"github.com/ClickHouse/clickhouse-go/v2"
)

type GetResponse struct {
	Message string `json:"message"`
	Body    string `json:"body"`
}
type PostResponse struct {
	Message string `json:"message"`
}

func HandleRequests(w http.ResponseWriter, r *http.Request) {
	enableCors(&w)
	switch r.Method {
	case http.MethodGet:
		handleGet(w, r)
	case http.MethodPost:
		handlePost(w, r)
	case http.MethodOptions:
		handleOptions(w, r)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func handleOptions(w http.ResponseWriter, _ *http.Request) {
	w.Header().Set("Allow", "GET, POST, OPTIONS")
	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
	w.Header().Set("Access-Control-Allow-Headers", "Content-Type")
	w.WriteHeader(http.StatusOK)
}

func handleGet(w http.ResponseWriter, _ *http.Request) {
	response := GetResponse{
		Message: "Hello, World! This is a GET request.",
		Body:    "TrackingInfoDB",
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)
}

func handlePost(w http.ResponseWriter, r *http.Request) {
	var data TrackingPayload
	if err := json.NewDecoder(r.Body).Decode(&data); err != nil {
		http.Error(w, "Failed to decode request body", http.StatusBadRequest)
		return
	}
	fmt.Printf("Received tracking info via POST: %+v", data)
	response := PostResponse{Message: "Received!"}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)

	dataToInsert := ClickHouseTrackingModel{
		IP:           getClientIP(r),
		SiteID:       data.SiteID,
		Page:         data.TrackingData.Page,
		Agent:        data.TrackingData.Agent,
		Referrer:     data.TrackingData.Referrer,
		PreviousPage: data.TrackingData.PreviousPage,
	}

	conn, err := clickhouse.Open(&clickhouse.Options{
		Addr: []string{"0.0.0.0:9000"},
		Auth: clickhouse.Auth{
			Database: "default",
			Username: "default",
			Password: "",
		},
		Debug: true,
	})
	if err != nil {
		log.Fatalf("Failed to connect to ClickHouse: %v", err)
	}
	defer conn.Close()

	// Insert the data
	insertIntoClickHouse(conn, dataToInsert)
}
