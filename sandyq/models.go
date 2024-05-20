package main

type TrackingInfo struct {
	Page         string `json:"page"`
	Agent        string `json:"agent"`
	Referrer     string `json:"referrer"`
	PreviousPage string `json:"previousPage"`
}

type TrackingPayload struct {
	SiteID       string       `json:"siteID"`
	TrackingData TrackingInfo `json:"trackingData"`
}

type ClickHouseTrackingModel struct {
	IP           string
	SiteID       string
	Page         string
	Agent        string
	Referrer     string
	PreviousPage string
}
