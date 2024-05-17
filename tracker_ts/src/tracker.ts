export interface TrackingData {
    page:           string;
    agent:          string;
    referrer:       string;
    previousPage:  string;
}

export interface TrackPayload {
    tracking:   TrackingData;
    site_id:    string;
}

export class Tracker {
    private siteID: string;
    private referrer: string;
    private agent: string;

    private URL: string;

    constructor(siteID: string, referrer: string, agent: string, URL: string) {
        this.siteID = siteID;
        this.referrer = referrer;
        this.agent = agent;

        this.URL = URL;
    }

    public buildTrackPayload(page: string, previousPage: string): TrackPayload {

        const trackingData: TrackingData = {
            page: page,
            previousPage: previousPage,
            agent: this.agent,
            referrer: this.referrer,
        };
        const payload: TrackPayload = {
            tracking: trackingData,
            site_id: this.siteID,
        };
        return payload;
    }

    public sendTrackingData(payload: TrackPayload): void {

        fetch(this.URL, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(payload)
        })
        .then(response => response.json())
        .then(data => console.log("Success:", data))
        .catch(error => console.error("Error:", error));
    }
}