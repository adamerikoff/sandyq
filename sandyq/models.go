package main

type TrackingInfo struct {
	IP           string `json:"ip"`
	Page         string `json:"page"`
	Agent        string `json:"agent"`
	Referrer     string `json:"referrer"`
	PreviousPage string `json:"previousPage"`
}

var TrackingInfoDB = []TrackingInfo{
	{IP: "192.168.1.1", Page: "/home", Agent: "Mozilla/5.0", Referrer: "", PreviousPage: "/about"},
	{IP: "192.168.1.2", Page: "/about", Agent: "Chrome/75.0", Referrer: "http://referrer.com", PreviousPage: ""},
	{IP: "192.168.1.3", Page: "/contact", Agent: "Firefox/54.0", Referrer: "", PreviousPage: "/about"},
	{IP: "192.168.1.4", Page: "/products", Agent: "Safari/537.36", Referrer: "", PreviousPage: "/about"},
	{IP: "192.168.1.5", Page: "/services", Agent: "Internet Explorer/11.0", Referrer: "http://referrer.com", PreviousPage: ""},
	{IP: "192.168.1.6", Page: "/home", Agent: "Mozilla/5.0", Referrer: "", PreviousPage: "/contacts"},
	{IP: "192.168.1.7", Page: "/about", Agent: "Chrome/75.0", Referrer: "http://referrer.com", PreviousPage: ""},
	{IP: "192.168.1.8", Page: "/contact", Agent: "Firefox/54.0", Referrer: "", PreviousPage: "http://referrer.com"},
	{IP: "192.168.1.9", Page: "/products", Agent: "Safari/537.36", Referrer: "http://referrer.com", PreviousPage: ""},
	{IP: "192.168.1.10", Page: "/services", Agent: "Internet Explorer/11.0", Referrer: "", PreviousPage: "/home"},
}
