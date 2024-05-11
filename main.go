package main

import (
	"encoding/base64"
	"encoding/json"
	"fmt"
	"net/http"
)

type TrackingData struct {
	Type      string `json:"type"`
	Identity  string `json:"identity"`
	UserAgent string `json:"ua"`
	Event     string `json:"event"`
	Category  string `json:"category"`
	Referrer  string `json:"referrer"`
}

type Tracking struct {
	SiteID string       `json:"side_id"`
	Action TrackingData `json:"tracking"`
}

func main() {
	http.HandleFunc("/track", track)
	fmt.Println("Server listening on port 9876")
	err := http.ListenAndServe(":9876", nil) // Use ListenAndServe directly
	if err != nil {
		panic(err) // Handle errors gracefully
	}
}

func track(w http.ResponseWriter, r *http.Request) {
	data := r.URL.Query().Get("data")
	fmt.Println("received", data)
	fmt.Fprintf(w, "Data received: %s\n", data) // Respond to the client
	decodedData, err := decodeData(data)
	if err != nil {
		// Handle decoding error (e.g., write error message to response)
		fmt.Fprintf(w, "Error decoding data: %v\n", err)
		return
	}

	// Process the decoded data (access decodedData.SiteID, decodedData.Action, etc.)
	fmt.Fprintf(w, "Data decoded successfully: %+v\n", decodedData.SiteID)
}

func decodeData(s string) (data Tracking, err error) {
	b, err := base64.StdEncoding.DecodeString(s)
	if err != nil {
		return data, fmt.Errorf("error decoding base64: %w", err)
	}
	err = json.Unmarshal(b, &data)
	if err != nil {
		return data, fmt.Errorf("error unmarshaling JSON: %w", err)
	}
	return data, nil
}
