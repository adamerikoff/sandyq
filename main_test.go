package main

import (
	"fmt"
	"testing"
)

func TestDecodeData(t *testing.T) {
	data, err := decodeData("eyJ0cmFja2luZyI6eyJ0eXBlIjoiZXZlbnQiLCJldmVudCI6Ii8iLCJ1YSI6Ik1vemlsbGEvNS4wIChNYWNpbnRvc2g7IEludGVsIE1hYyBPUyBYIDEwLjE1OyBydjoxMjQuMCkgR2Vja28vMjAxMDAxMDEgRmlyZWZveC8xMjQuMCIsImNhdGVnb3J5IjoiUGFnZSB2aWV3cyIsInJlZmVycmVyIjoiIn0sInNpdGVfaWQiOiJ0ZW1wLXNpdGVpZCJ9")
	fmt.Print(data)
	if err != nil {
		t.Fatal(err)
	} else if data.SiteID != "temp-siteid" {
		t.Errorf("expected 'temp-siteid', got %s", data.SiteID)
	}
}
