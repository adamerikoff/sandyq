interface TrackingData {
    type: "event" | "page";
    identity: string;
    ua: string;
    event: string;
    category: string;
    referrer: string;
}

interface TrackPayload {
    tracking: TrackingData;
    site_id: string;
}

class Tracker {
    url: string;
    
    constructor(url: string) {
        this.url = url;
    }

    track(event: string, category: string) {
        const payload: TrackPayload = {
            tracking: {
                type: "event",
                event: "temp-data",
                identity: "temp-data",
                ua: "temp-data",
                category: "temp-data",
                referrer: "temp-data",
            },
            site_id: "temp-site-id",
        };
        this.trackRequest(payload)
    }

    private trackRequest(payload: TrackPayload) {
        const json_payload = JSON.stringify(payload);
        const url_string = `${this.url}?data=${btoa(json_payload)}`
        const img = new Image();
        img.src = url_string;
    }
}

((window, document) => {
    window._tracker = new Tracker();
    console.log("tracker loaded!");
})(window, document);